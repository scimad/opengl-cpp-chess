#include "graphics/renderer.hpp"
#include "graphics/utils.hpp"

void GLClearError(){
    while (glGetError() != GL_NO_ERROR){};
}

bool GLIsErrorFree(const char* function, const char* file, int line){
    bool is_error_free = true;
    while (GLenum error = glGetError()){
        zr::log("OpenGL Error (code "
        + std::to_string(error) +  ") from: " + function + " " + file + ":" + std::to_string(line), zr::VERBOSITY_LEVEL::ERROR);
        is_error_free = false;
    }
    if (is_error_free == false){
        zr::log("OpenGL found some error!!!!!");
    }
    return is_error_free;
}

Color::Color(){zr::log("Hello");};
Color::Color(float r, float g, float b, float a):r(r),g(g),b(b),a(a){};

