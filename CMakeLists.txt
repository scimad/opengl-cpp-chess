cmake_minimum_required(VERSION 3.16)
project(opengl-chess LANGUAGES C CXX)

add_executable(opengl-chess)
find_package(PkgConfig REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
pkg_check_modules(glfw3 REQUIRED IMPORTED_TARGET glfw3)

if(${OpenGL_FOUND})
    MESSAGE("[ZR]: OpenGL included at ${OPENGL_INCLUDE_DIR}")
    MESSAGE("[ZR]: OPENGL libraries = " ${OPENGL_LIBRARIES})
endif()

pkg_check_modules(glfw3 REQUIRED IMPORTED_TARGET glfw3)
if(${glfw3_FOUND})
    MESSAGE("[ZR]: PKGCOFIG = " ${PKG_CONFIG_EXECUTABLE})
    MESSAGE("[ZR]: GLFW3 libraries = " ${glfw3_LIBRARIES})
    MESSAGE("[ZR]: GLFW3 link libraries = " ${glfw3_LINK_LIBRARIES})
endif()

include_directories(src/
                    vendor/include
                    vendor/include/imgui/
                    ${OPENGL_INCLUDE_DIRS}
                    ${glfw3_INCLUDE_DIRS}
)                                 # ${GLEW_INCLUDE_DIRS}

target_sources(opengl-chess PRIVATE main.cpp 
    src/graphics/utils.cpp
    src/graphics/renderer.cpp
    src/graphics/vertex_buffer.cpp
    src/graphics/index_buffer.cpp
    src/graphics/vertex_array.cpp
    src/graphics/vertex_buffer_layout.cpp
    src/graphics/shader.cpp
    src/graphics/texture.cpp
    src/graphics/gui.cpp
    src/graphics/model.cpp

    src/chess/game.cpp
    src/chess/chess_piece.cpp
    src/chess/game_board.cpp

    vendor/src/ZR/core.cpp
    vendor/include/imgui/imgui.cpp
    vendor/include/imgui/imgui_demo.cpp
    vendor/include/imgui/imgui_draw.cpp
    vendor/include/imgui/imgui_tables.cpp
    vendor/include/imgui/imgui_widgets.cpp
    vendor/include/imgui/imgui_impl_glfw.cpp
    vendor/include/imgui/imgui_impl_opengl3.cpp
)
target_link_libraries(opengl-chess ${OPENGL_LIBRARIES} ${glfw3_LINK_LIBRARIES} GLEW ${CMAKE_DL_LIBS})                # ${GLEW_LINK_LIBRARIES}
