#include <GL/glew.h> // include GLEW and new version of GL on Windows
#define GLFW_DLL
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "Logger.h"
#include "Camera.h"
#include "old_code/BSpline_old.h"
#include "Cube.h"
#include "InputHandler.h"
#include "old_code/Mover_old.h"
#include "StepAheadAnimationChannel.h"
#include "RenderEngine.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "LinearPath.h"
#include "Path.h"
#include "Clock.h"
#include "gui/TimelineWindow.h"
#include "gui/WindowRenderEngine.h"
#include "Channel.h"
#include "Keyframe.h"

const float ROT_SPEED = 0.15f;
const float SCROLL_SENSITIVITY = 0.30f;
const int cursorMode = GLFW_CURSOR_NORMAL;
const int STANDARD_WINDOW_WIDTH = 1940;
const int STANDARD_WINDOW_HEIGHT = 1080;

char VERTEX_SHADER_FILENAME[] = "shaders/simple_shader.vert";
char FRAGMENT_SHADER_FILENAME[] = "shaders/simple_shader.frag";

// keep track of window size for things like the viewport and the mouse cursor
//int g_gl_width = 1940;
//int g_gl_height = 1080;


// global variables
RenderEngine* renderEngine;
Clock *sceneClock;
WindowRenderEngine *windows;
Channel *pickedChannel = nullptr;


// callback functions
void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
//    g_gl_width = width;
//    g_gl_height = height;
    renderEngine->onWindowSizeChange(width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(!ImGui::GetIO().WantCaptureMouse) {
        renderEngine->getEditorCamera().relativeMove(glm::vec3(0.0f, yoffset * SCROLL_SENSITIVITY, 0.0f));
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(ImGui::GetIO().WantCaptureMouse)
        return;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double currMousePosX, currMousePosY;
        glfwGetCursorPos(window, &currMousePosX, &currMousePosY);
        pickedChannel = renderEngine->pick(sceneClock->getFrameIndex(), currMousePosX, currMousePosY, window);
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // close screen when esc button is pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }

    // pause or play scene
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if(sceneClock->isRunning())
            sceneClock->pause();
        else
            sceneClock->start();
    }

    // jump back in time 1 or 10 frames
    if(key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        int frameJumpSize = 1;
        if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
            frameJumpSize = 10;
        sceneClock->setFrameIndex(sceneClock->getFrameIndex()-frameJumpSize);
    }

    // jump forward in time 1 or 10 frames
    if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        int frameJumpSize = 1;
        if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
            frameJumpSize = 10;
        sceneClock->setFrameIndex(sceneClock->getFrameIndex()+frameJumpSize);
    }
}


/**
 * Update the mFps-counter on top of a window
 * @param window
 */
void _update_fps_counter(GLFWwindow* window) {
    static double previous_seconds = glfwGetTime();
    static int frame_count;
    double current_seconds = glfwGetTime();
    double elapsed_seconds = current_seconds - previous_seconds;
    if (elapsed_seconds > 0.25) {
        previous_seconds = current_seconds;
        double fps = (double)frame_count / elapsed_seconds;
        char tmp[128];
        sprintf(tmp, "opengl @ mFps: %.2f", fps);
        glfwSetWindowTitle(window, tmp);
        frame_count = 0;
    }
    frame_count++;
}


/**
 * The main function
 */
int main() {
    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(STANDARD_WINDOW_WIDTH, STANDARD_WINDOW_HEIGHT, "Hello Triangle", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glShadeModel(GL_FLAT);
    glfwSetWindowSizeCallback(window, glfw_window_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // GLFW settings
    glfwSetInputMode(window, GLFW_CURSOR, cursorMode);
    if(cursorMode != GLFW_CURSOR_NORMAL) {
        glfwSetCursorPos(window, 0, 0);
    }

//    glEnable(GL_CULL_FACE); // cull face
//    glCullFace(GL_BACK); // cull back face
//    glFrontFace(GL_CW); // GL_CCW for counter clock-wise

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller valueParametric as "closer"


    // load shaders
//    GLuint vs = InputHandler::loadAndCompileShader(VERTEX_SHADER_FILENAME, GL_VERTEX_SHADER);
//    GLuint fs = InputHandler::loadAndCompileShader(FRAGMENT_SHADER_FILENAME, GL_FRAGMENT_SHADER);
//    GLuint shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, fs);
//    glAttachShader(shaderProgram, vs);
//    glLinkProgram(shaderProgram);

//    Camera nav;

//    Cube cube;
//    cube.loadToGPU();

//    const int bSplinePoints = 100;
//    BSpline_old bSpline(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f));
//    bSpline.add(glm::vec3(0.0f, 2.0f, 2.0f));
//    bSpline.add(glm::vec3(-2.0f, 1.0f, 2.0f));
//    bSpline.add(glm::vec3(2.0f, -2.0f, 0.0f));
//    bSpline.add(glm::vec3(0.0f, -3.0f, 0.0f));
//    bSpline.add(glm::vec3(0.0f, 0.0f, 0.0f));
//    bSpline.add(glm::vec3(0.0f, 0.0f, 0.0f));
//    bSpline.add(glm::vec3(0.0f, 0.0f, 0.0f));
//    bSpline.populatePointsVector(bSplinePoints);
//    bSpline.loadToGPU();

//    Mover_old mover(cube, bSpline);
//    bSpline.populateArcLengthTable(20);

//    glm::mat4 model = glm::mat4(1.0f);
//    glm::mat4 model2 = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
//    glm::mat4 view = nav.getViewMatrix();
//    glm::mat4 proj = glm::perspective(glm::radians(45.0f),  ((float)g_gl_width) / ((float)g_gl_height), NEAR_CLIPPING, FAR_CLIPPING);
//    glUseProgram(shaderProgram);
//    GLint uniProj = glGetUniformLocation(shaderProgram, "projectionMatrix");
//    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
//    GLint uniTrans = glGetUniformLocation(shaderProgram, "modelMatrix");
//    GLint uniView = glGetUniformLocation(shaderProgram, "viewMatrix");
    renderEngine = new RenderEngine();
    sceneClock = new Clock();
    windows = new WindowRenderEngine(sceneClock);
    InputHandler inputHandler(window, renderEngine);

//    mover.start();

    // imgui initialization
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();

    // INITIALIZING TEST DATA
    StepAheadAnimationChannel saaChannel;
    renderEngine->addSaaChannel(&saaChannel);
    Cube realCube;
    saaChannel.addObject_DEPRECATED(&realCube);
    realCube.loadToGPU();
    LinearPath realPath;
    saaChannel.setPath(&realPath);
    realPath.addKeyframe(Keyframe(100, glm::vec3(0.0f), glm::vec3(glm::pi<float>(), glm::half_pi<float>(), 0.0f)));
    realPath.addKeyframe(Keyframe(0));
    realPath.addKeyframe(Keyframe(500, glm::vec3(-0.5f)));
    // END OF INITIALIZATION OF DATA

    sceneClock->start();

    while(!glfwWindowShouldClose(window)) {
        _update_fps_counter(window);

        // loop init of imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int windowWidth, windowHeight;
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        // wipe the drawing surface clear
        glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // update and load view matrix
//        view = nav.getViewMatrix();
//        glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
        // draw objects
        //cube.draw(uniTrans);
//        mover.draw(uniTrans);
//        cube.draw(uniTrans, model2);
//        bSpline.draw(uniTrans);
        renderEngine->render(sceneClock->getFrameIndex());
        double currMousePosX, currMousePosY;
        glfwGetCursorPos(window, &currMousePosX, &currMousePosY);

//        renderEngine.getEditorCamera().move(InputHandler::readMoveButtons_DEPRECATED(window, MOVE_SPEED));

        // mouse input
//        if(cursorMode != GLFW_CURSOR_NORMAL) {
//            const float mouseSensitivity = 0.05f;
//            double mouseX, mouseY;
//            glfwGetCursorPos(window, &mouseX, &mouseY);
//            nav.rot(ROT_SPEED * (float)mouseX, ROT_SPEED * (float)mouseY);
//            glfwSetCursorPos(window, 0, 0); //reset the mouse, so it doesn't go out of the window
//        }

        // put the stuff we've been drawing onto the display

        // imgui windowing
        windows->render(pickedChannel);
//        ImGui::ShowDemoWindow();


        // imgui rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGui::EndFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();

        // update other events like input handling
        inputHandler.handleMouse();
    }

    // close imgui context
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    // close GL context and any other GLFW resources
    glfwTerminate();
    return 0;
}
