#ifndef __SHADER_H__
#define __SHADER_H__

#include "../../lib/glad/glad.h"

#include "../../lib/glm/glm.hpp"
#include "../../lib/glm/gtc/matrix_transform.hpp"
#include "../../lib/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>

class Shader {
    public :
        //Shader id pointer
        unsigned int id;
        Shader();
        Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath);
        void Generate(const std::string vertexShaderPath, const std::string fragmentShaderPath);
        void Activate();
        void Cleanup();
        //Uniform variable functions
        void SetInt(const std::string name, int val);
        void SetBool(const std::string name, bool val);
        void SetFloat(const std::string name, float val);
        void Set3Float(const std::string name, float v1, float v2, float v3);
        void Set3Float(const std::string name, glm::vec3 v);
        void Set4Float(const std::string name, float v1, float v2, float v3, float v4);
        void Set4Float(const std::string name, glm::vec4 v);
        void SetMat3(const std::string name, glm::mat3 val);
        void SetMat4(const std::string name, glm::mat4 val);
    private :         
        //Utility functions
        std::string loadShaderSrc(const std::string path);
        GLuint compileShader(const std::string path, GLenum type);   
};
#endif