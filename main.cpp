#include <GL/glew.h> // include GLEW and new version of GL on Windows
#define GLFW_DLL
#include <GLFW/glfw3.h> // GLFW helper library
#include <string>
#include "InputHandler.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "gui/WindowRenderEngine.h"
#include "Camera.h"
#include "Scene.h"
#include "Mouse3D.h"
#include "BSpline.h"

// constants
const float SCROLL_SENSITIVITY = 0.30f;
const int cursorMode = GLFW_CURSOR_NORMAL;
const int STANDARD_WINDOW_WIDTH = 1940;
const int STANDARD_WINDOW_HEIGHT = 1080;

// global variables
Scene scene;
Mouse3D mouse3D;
WindowRenderEngine *windows;


// resize callback
void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
    scene.renderEngine().onWindowSizeChange(width, height);
}

// mouse-scroll callback
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(!ImGui::GetIO().WantCaptureMouse) {
        scene.renderEngine().editorCamera().relativeMove(glm::vec3(0.0f, 0.0f, -yoffset * SCROLL_SENSITIVITY));
    }
}

// mouse-button click callback
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(ImGui::GetIO().WantCaptureMouse)
        return;
    mouse3D.mouse_button_callback(window, button, action, mods, scene);
}

// keyboard-key down callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // close screen when esc button is pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }
    // pause or play scene
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if(scene.clock()->isRunning())
            scene.clock()->pause();
        else
            scene.clock()->start();
    }
    // jump back in time 1 or 10 frames
    if(key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        int frameJumpSize = 1;
        if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
            frameJumpSize = 10;
        scene.clock()->setFrameIndex(scene.clock()->getFrameIndex() - frameJumpSize);
    }
    // jump forward in time 1 or 10 frames
    if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        int frameJumpSize = 1;
        if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
            frameJumpSize = 10;
        scene.clock()->setFrameIndex(scene.clock()->getFrameIndex() + frameJumpSize);
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
    // glfw init
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_SAMPLES, 4);
    // create glfw window
    GLFWwindow* window = glfwCreateWindow(STANDARD_WINDOW_WIDTH, STANDARD_WINDOW_HEIGHT, "Project Of Stef Loos", NULL, NULL);
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
    // culling settings
    glEnable(GL_CULL_FACE); // cull face
    glCullFace(GL_BACK); // cull back face
    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller valueParametric as "closer"
    // init global variables
    scene.init();
    windows = new WindowRenderEngine(scene);
    InputHandler inputHandler(window, &scene.renderEngine());
    // dear imgui initialization
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // %%% ADD VIRTUAL CAMERA CODE
    // %%% uncomment to add a virtual camera
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Camera cam1(scene.renderEngine().getWindowWidth(), scene.renderEngine().getWindowHeight(), "cam1");
    BSplinePath bSplinePath;
    std::vector<glm::vec3> otherKnots;
    otherKnots.emplace_back(3.0, 2.0, -3.0);
    BSpline bSpline(glm::vec3(2.0f), otherKnots, glm::vec3(-2.0, 2.0, -2.0));
    bSpline.populateArcLengthTable(100);
    bSplinePath.add(&bSpline, std::pair<int, int>(0, 600));
    bSplinePath.add(glm::vec3(-35.0f, 45.0f, 0.0f), 0);
    bSplinePath.add(glm::vec3(-35.0f, 135.0f, 0.0f), 300);
    bSplinePath.add(glm::vec3(-35.0f, 225.0f, 0.0f), 600);
    cam1.setPath(&bSplinePath);
    scene.add(&cam1);
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // %%% END OF CODE TO ADD VIRTUAL CAMERA
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    // start the scene
    scene.clock()->start();

    // render-loop
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
        // update all objects in scene for new frame-index
        scene.update();
        // render the scene
        scene.renderEngine().render(scene, mouse3D.picked);
        // dear imgui windowing system calls
        windows->render(mouse3D.picked);
        // call 3D Mouse, for drawing FFD control points and stuff
        double currMousePosX, currMousePosY;
        glfwGetCursorPos(window, &currMousePosX, &currMousePosY);
        mouse3D.loop(scene, currMousePosX, currMousePosY);
        // dear imgui rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGui::EndFrame();
        // glfw end of loop
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
