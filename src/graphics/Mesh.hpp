#ifndef __MESH_H__
#define __MESH_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "Shader.hpp"
#include "Texture.hpp"

typedef struct Vertex {
    glm::vec3 position;
    glm::vec3 normal; 
    glm::vec2 textCoord;

    static std::vector<Vertex> GenList(float* vertices, int noVertices);

} Vertex;

class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        unsigned int VAO;
        std::vector<Texture> textures;

        Mesh();
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

        void Render(Shader shader);
        void Cleanup();

    private: 
        unsigned int VBO, EBO;

        void setup();
}; 

#endif