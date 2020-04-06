cmake_minimum_required(VERSION 3.15)
project(project)

set(CMAKE_CXX_STANDARD 14)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS})

configure_file(shader.vert shader.vert COPYONLY)
configure_file(shader.frag shader.frag COPYONLY)
configure_file(simple_shader.vert simple_shader.vert COPYONLY)
configure_file(simple_shader.frag simple_shader.frag COPYONLY)
file(COPY models DESTINATION models)

add_executable(project main.cpp Logger.h Navigator.cpp Navigator.h Lights.cpp Lights.h BSpline.cpp BSpline.h Object.cpp Object.h Cube.cpp Cube.h InputHandler.cpp InputHandler.h Path.cpp Path.h Mover.cpp Mover.h Chrono.cpp Chrono.h CJoint.cpp CJoint.h CLink.cpp CLink.h CSkeleton.cpp CSkeleton.h
        vendor/imgui/imconfig.h vendor/imgui/imgui.cpp vendor/imgui/imgui.h vendor/imgui/imgui_demo.cpp vendor/imgui/imgui_draw.cpp vendor/imgui/imgui_impl_glfw.cpp vendor/imgui/imgui_impl_glfw.h vendor/imgui/imgui_impl_opengl3.cpp vendor/imgui/imgui_impl_opengl3.h vendor/imgui/imgui_internal.h vendor/imgui/imgui_widgets.cpp vendor/imgui/imstb_rectpack.h vendor/imgui/imstb_textedit.h vendor/imgui/imstb_truetype.h)

target_link_libraries(project glfw OpenGL::GL ${GLEW_LIBRARIES} ${ASSIMP_LIBRARIES})