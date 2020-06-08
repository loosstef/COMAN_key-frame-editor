cmake_minimum_required(VERSION 3.15)
project(project)

set(CMAKE_CXX_STANDARD 17)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS})

configure_file(shaders/standard.vert shaders/standard.vert COPYONLY)
configure_file(shaders/standard.frag shaders/standard.frag COPYONLY)
configure_file(shaders/skybox.vert shaders/skybox.vert COPYONLY)
configure_file(shaders/skybox.frag shaders/skybox.frag COPYONLY)
file(COPY models DESTINATION .)
file(COPY base_models DESTINATION .)

add_executable(
        project main.cpp Logger.h Camera.cpp Camera.h  InputHandler.cpp InputHandler.h  CJoint.cpp CJoint.h
        CLink.cpp CLink.h CSkeleton.cpp CSkeleton.h  RenderEngine.cpp RenderEngine.h
        StepAheadAnimationChannel.cpp StepAheadAnimationChannel.h Path.cpp Path.h LinearPath.cpp
        LinearPath.h Clock.cpp Clock.h gui/TimelineWindow.cpp gui/TimelineWindow.h gui/WindowRenderEngine.cpp
        gui/WindowRenderEngine.h Channel.cpp Channel.h gui/EditSAAChannelWindow.cpp gui/EditSAAChannelWindow.h
        Keyframe.cpp Keyframe.h Orientation.cpp Orientation.h  jsonCast.h jsonCast.cpp
        Mesh.cpp Mesh.h Model.cpp Model.h stb_image.h FFD.cpp FFD.h Picked.h LinInterp.cpp Shader.cpp Shader.h
        StandardShader.cpp StandardShader.h Mouse3D.cpp Mouse3D.h Scene.cpp Scene.h TransformStack.cpp TransformStack.h
        Picked.cpp gui/EditJointWindow.cpp gui/EditJointWindow.h LSystem.cpp LSystem.h Plant.cpp Plant.h
        Branch.cpp Branch.h ParticleSystem.cpp ParticleSystem.h Particle.cpp Particle.h Explosion.cpp Explosion.h
        SkyBox.cpp SkyBox.h BSpline.cpp BSpline.h  BSplinePath.cpp BSplinePath.h
        gui/RenderEngineWindow.cpp gui/RenderEngineWindow.h  gui/MainMenuBar.cpp gui/MainMenuBar.h
        gui/SceneWindow.cpp gui/SceneWindow.h

        vendor/imgui/imconfig.h vendor/imgui/imgui.cpp vendor/imgui/imgui.h
        vendor/imgui/imgui_demo.cpp vendor/imgui/imgui_draw.cpp vendor/imgui/imgui_impl_glfw.cpp
        vendor/imgui/imgui_impl_glfw.h vendor/imgui/imgui_impl_opengl3.cpp vendor/imgui/imgui_impl_opengl3.h
        vendor/imgui/imgui_internal.h vendor/imgui/imgui_widgets.cpp vendor/imgui/imstb_rectpack.h
        vendor/imgui/imstb_textedit.h vendor/imgui/imstb_truetype.h
        vendor/nlohmann/json.hpp
        )


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

target_link_libraries(project glfw OpenGL::GL ${GLEW_LIBRARIES} ${ASSIMP_LIBRARIES})