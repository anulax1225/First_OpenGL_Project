#include "Mesh.hpp"

std::vector<Vertex> Vertex::GenList(float* vertices, int noVertices) {
    std::vector<Vertex> ret = std::vector<Vertex>(noVertices);

    int stride = sizeof(Vertex) / sizeof(float);

    for (int i = 0;  i < noVertices; i++) {
        ret[i].position = glm::vec3(
            vertices[i*stride+0],
            vertices[i*stride+1],
            vertices[i*stride+2]
        );
        ret[i].normal = glm::vec3(
            vertices[i*stride+3],
            vertices[i*stride+4],
            vertices[i*stride+5]
        );
        ret[i].textCoord = glm::vec2(
            vertices[i*stride+6],
            vertices[i*stride+7]
        );
    } 
    return ret;
}

Mesh::Mesh() { }

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->setup();
}

void Mesh::Render(Shader shader) {
    for(unsigned int i = 0; i < textures.size(); i++) {
        shader.SetInt(textures[i].name ,textures[i].id);
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i].Bind();
    }
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(0);
}

void Mesh::Cleanup() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

void Mesh::setup() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

    //Set attribute pointer
    //Indicates to the GPU how to segment and distribute the data in the VBO
    //(id, number of values, type of values, normelized: false, size of a unit, offset)
    //Cast to a void pointer on the offset for OpenGL
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));
    glEnableVertexAttribArray(0);
    //Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
    glEnableVertexAttribArray(1);
    //texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, textCoord)));
    glEnableVertexAttribArray(2); 
}
