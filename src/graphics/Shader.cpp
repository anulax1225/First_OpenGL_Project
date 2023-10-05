#include "Shader.hpp"

Shader::Shader() {}

Shader::Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath) { 
    this->Generate(vertexShaderPath, fragmentShaderPath);
}

void Shader::Generate(const std::string vertexShaderPath, const std::string fragmentShaderPath) {
    int success;
    char infoLog[512];

    //Compiling the shaders 
    GLuint vertexShader = this->compileShader(vertexShaderPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = this->compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    //Creating a shader program
    this->id = glCreateProgram();
    //Attaching shaders refs to the shaderProgram and linking them
    glAttachShader(this->id, vertexShader);
    glAttachShader(this->id, fragmentShader);    
    glLinkProgram(this->id);

    //Catch error
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(this->id, 512, NULL, infoLog);
        std::cout << "Error when link sharder in a program : " << infoLog << std::endl; 
    }
    //Deleting shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() {
    //Sets focus on this shader
    glUseProgram(this->id);
}

GLuint Shader::compileShader(const std::string path, GLenum type) {
    int success;
    char infoLog[512];
    //Compile shader
    GLuint ret = glCreateShader(type);
    std::string shaderSrc = this->loadShaderSrc(path);
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

void Shader::Cleanup() {
    glDeleteProgram(this->id);
}

void Shader::SetInt(const std::string name, int val) {
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), val);
}

void Shader::SetBool(const std::string name, bool value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::SetFloat(const std::string name, float val) {
    glUniform1f(glGetUniformLocation(this->id, name.c_str()), val);
}

void Shader::Set3Float(const std::string name, float v1, float v2, float v3) {
    glUniform3f(glGetUniformLocation(id, name.c_str()), v1, v2, v3);
}

void Shader::Set3Float(const std::string name, glm::vec3 v) {
    this->Set3Float(name, v.x, v.y, v.z);
}

void Shader::Set4Float(const std::string name, float v1, float v2, float v3, float v4) {
    glUniform4f(glGetUniformLocation(id, name.c_str()), v1, v2, v3, v4);
}

void Shader::SetMat3(const std::string name, glm::mat3 val) {
     glUniformMatrix3fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::SetMat4(const std::string name, glm::mat4 val) {
     glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}