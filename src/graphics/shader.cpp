#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include "shader.hpp"
#include "renderer.hpp"

#include <ZR/core.hpp>

enum class ShaderType{
    NONE = -1, VERTEX = 0, FRAGMENT = 1
};

Shader::Shader(const std::string& filename):shader_filename(filename), rendererID(0){
    ShaderProgramSource source = parseShader(shader_filename);
    rendererID = createShader(source.vertexSource, source.fragmentSource);
};

Shader::~Shader(){
    GLCALL(glDeleteProgram(rendererID));
};

void Shader::bind() const {
    //Binding a shader
    GLCALL(glUseProgram(rendererID));

};

void Shader::unbind(){
    //Unbinding a shader
    GLCALL(glUseProgram(0));
};

void Shader::setUniform1f(const std::string& uni_name, float value){
    int location = getUniformLocation(uni_name);
    GLCALL(glUniform1f(location, value));
};

void Shader::setUniform1i(const std::string& uni_name, int value){
    int location = getUniformLocation(uni_name);
    GLCALL(glUniform1i(location, value));
};

void Shader::setUniformMat4f(const std::string& uni_name, const glm::mat4& matrix){
    int location = getUniformLocation(uni_name);
    GLCALL(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
};

void Shader::setUniform4f(const std::string& uni_name, float v0, float v1, float v2, float v3){
    int location = getUniformLocation(uni_name);
    GLCALL(glUniform4f(location, v0, v1, v2, v3));
};

int Shader::getUniformLocation(const std::string& uni_name){
    if (uniformrLocationCache.find(uni_name) != uniformrLocationCache.end()){
        return uniformrLocationCache[uni_name];
    }
    GLCALL(int location = glGetUniformLocation(rendererID, uni_name.c_str()));
    if (location == -1){
        zr::log("Uniform: " + uni_name + " doesn't exist.",zr::VERBOSITY_LEVEL::WARNING);
    }
    uniformrLocationCache[uni_name] = location;
    return location;
};

ShaderProgramSource Shader::parseShader(const std::string& file){
    std::ifstream stream(file);
    std::string line;
    std::stringstream ss[2];
    ShaderType shader_type = ShaderType::NONE;
    while (getline(stream, line)){
        if (line.find("#shader") != std::string::npos){
            if (line.find("vertex") != std::string::npos){
                shader_type = ShaderType::VERTEX;
            }else if (line.find("fragment") != std::string::npos){
                shader_type = ShaderType::FRAGMENT;
            }
        }else{
            ss[(int) shader_type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}

GLuint Shader::createShader(const std::string& vert_shader, const std::string& frag_shader){
    GLuint program_handle = glCreateProgram();
    GLuint vs_handle = compileShader(GL_VERTEX_SHADER, vert_shader);
    GLuint fs_handle = compileShader(GL_FRAGMENT_SHADER, frag_shader);

    glAttachShader(program_handle, vs_handle);
    glAttachShader(program_handle, fs_handle);
    glLinkProgram(program_handle);
    glValidateProgram(program_handle);

    glDeleteShader(vs_handle);
    glDeleteShader(fs_handle);
    zr::log("Created shader program: " + std::to_string(program_handle));
    return program_handle;
}

unsigned int Shader::compileShader(GLenum shader_type, const std::string& shader_program){
    GLuint shader_handle = glCreateShader(shader_type);
    const char* shader_src = shader_program.c_str();
    glShaderSource(shader_handle, 1, &shader_src, NULL);
    glCompileShader(shader_handle);

    GLint result;
    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE){
        zr::log(std::string("Failed to compile ") + (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment") + " shader.", zr::VERBOSITY_LEVEL::ERROR);
        int length;
        glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &length);
        char* err_msg = (char*) alloca(length * sizeof(char));    //Dynamic size char array allocation on stack using alloca()
        glGetShaderInfoLog(shader_handle, length, &length, err_msg);
        zr::log(std::string(err_msg), zr::VERBOSITY_LEVEL::ERROR);
    }
    return shader_handle;
}



