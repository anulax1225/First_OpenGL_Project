#include "Model.hpp"

Model::Model() { }

void Model::Init() { }

void Model::Render(Shader shader) {
    for (Mesh mesh : this->meshes) {
        mesh.Render(shader);
    }
}   

void Model::Cleanup() {
    for (Mesh mesh : this->meshes) {
        mesh.Cleanup();
    }
}

