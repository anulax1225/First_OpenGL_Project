#ifndef __MODEL_H__
#define __MODEL_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Mesh.hpp"

class Model {
public: 
    std::vector<Mesh> meshes;

    Model();

    void Init();
    void Render(Shader shader);
    void Cleanup();
};

#endif