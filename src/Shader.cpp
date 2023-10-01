#include "../include/Shader.hpp"


Shader::Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath){
    int success;
    char infoLog[512];

    GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);    
    glLinkProgram(id);

       //Catch error
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "Error when link sharder in a program : " << infoLog << std::endl; 
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() {
    glUseProgram(id);
}

std::string Shader::loadShaderSrc(std::string path) {
    std::ifstream file;
    std::stringstream buf;
    std::string shaderCode = "";

    file.open(path);
    if(file.is_open()) { 
        buf << file.rdbuf();
        shaderCode = buf.str();
    } else {
        std::cout << "Could not open file : " << path << std::endl;
    }
    file.close();

    return shaderCode;
}

GLuint Shader::compileShader(const std::string path, GLenum type) {
    int success;
    char infoLog[512];
    //Compile shader
    GLuint ret = glCreateShader(type);
    std::string shaderSrc = loadShaderSrc(path);
    const GLchar* shader = shaderSrc.c_str();
    glShaderSource(ret, 1, &shader, NULL);
    glCompileShader(ret);
    //Catch error
    glGetShaderiv(ret, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(ret, 512, NULL, infoLog);
        std::cout << "Error with fragment shader compilating : " << infoLog << std::endl; 
    }
    //References to the compiled shader
    return ret;
}

void Shader::SetMat4(std::string name, glm::mat4 val) {
     glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}