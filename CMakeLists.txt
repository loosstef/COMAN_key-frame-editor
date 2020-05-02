cmake_minimum_required(VERSION 3.15)
project(project)

set(CMAKE_CXX_STANDARD 14)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS})

configure_file(shaders/simple_shader.vert shaders/simple_shader.vert COPYONLY)
configure_file(shaders/simple_shader.frag shaders/simple_shader.frag COPYONLY)
#configure_file(shaders/color_picking_shader.vert shaders/color_picking_shader.vert COPYONLY)
#configure_file(shaders/color_picking_shader.frag shaders/color_picking_shader.frag COPYONLY)
configure_file(shaders/new_shader.vert shaders/new_shader.vert COPYONLY)
configure_file(shaders/new_shader.frag shaders/new_shader.frag COPYONLY)
file(COPY models DESTINATION .)
file(COPY base_models DESTINATION .)

add_executable(project main.cpp Logger.h Camera.cpp Camera.h old_code/Lights_DEPRECATED.cpp old_code/Lights_DEPRECATED.h old_code/BSpline_old.cpp
        old_code/BSpline_old.h old_code/Object_DEPRECATED.cpp old_code/Object_DEPRECATED.h old_code/Cube_DEPRECATED.cpp old_code/Cube_DEPRECATED.h
        InputHandler.cpp InputHandler.h old_code/Path_old.cpp old_code/Path_old.h old_code/Mover_old.cpp
        old_code/Mover_old.h old_code/Chrono_old.cpp old_code/Chrono_old.h CJoint.cpp CJoint.h CLink.cpp CLink.h
        CSkeleton.cpp CSkeleton.h vendor/imgui/imconfig.h vendor/imgui/imgui.cpp vendor/imgui/imgui.h
        vendor/imgui/imgui_demo.cpp vendor/imgui/imgui_draw.cpp vendor/imgui/imgui_impl_glfw.cpp
        vendor/imgui/imgui_impl_glfw.h vendor/imgui/imgui_impl_opengl3.cpp vendor/imgui/imgui_impl_opengl3.h
        vendor/imgui/imgui_internal.h vendor/imgui/imgui_widgets.cpp vendor/imgui/imstb_rectpack.h
        vendor/imgui/imstb_textedit.h vendor/imgui/imstb_truetype.h RenderEngine.cpp RenderEngine.h
        StepAheadAnimationChannel.cpp StepAheadAnimationChannel.h Path.cpp Path.h LinearPath.cpp
        LinearPath.h Clock.cpp Clock.h gui/TimelineWindow.cpp gui/TimelineWindow.h gui/WindowRenderEngine.cpp
        gui/WindowRenderEngine.h Channel.cpp Channel.h gui/EditSAAChannelWindow.cpp gui/EditSAAChannelWindow.h
        Keyframe.cpp Keyframe.h Orientation.cpp Orientation.h
        Mesh.cpp Mesh.h Model.cpp Model.h stb_image.h FFD.cpp FFD.h Picked.h LinInterp.cpp Shader.cpp Shader.h StandardShader.cpp StandardShader.h Mouse3D.cpp Mouse3D.h Scene.cpp Scene.h TransformStack.cpp TransformStack.h Picked.cpp gui/EditJointWindow.cpp gui/EditJointWindow.h)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

target_link_libraries(project glfw OpenGL::GL ${GLEW_LIBRARIES} ${ASSIMP_LIBRARIES})