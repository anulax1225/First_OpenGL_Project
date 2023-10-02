#ifndef __SHADER_H__
#define __SHADER_H__

#include "../lib/glad/glad.h"

#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "../lib/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>

class Shader {
    public :
        //Shader id pointer
        unsigned int id;
        Shader() = delete;
        Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath);
        void Activate();
        //Uniform variable functions
        void SetMat4(std::string name, glm::mat4 val);
        void SetInt(std::string name, int val);
        void SetFloat(std::string name, float val);
    private :         
        //Utility functions
        std::string loadShaderSrc(const std::string path);
        GLuint compileShader(const std::string path, GLenum type);   
};
#endif