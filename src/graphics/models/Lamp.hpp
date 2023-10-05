#ifndef __LAMP_H__
#define __LAMP_H__

#include "Cube.hpp"

class Lamp : public Cube {
    public:
        glm::vec3 lightColor;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        Lamp(glm::vec3 lightColor, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 pos, glm::vec3 size)
        : Cube(pos, size, Material::white_plastic) {
            this->lightColor = lightColor;
            this->ambient = ambient;
            this->diffuse = diffuse;
            this->specular = specular;
        }

        void Render(Shader shader) {
            shader.Set3Float("lightColor", lightColor);
            Cube::Render(shader);
        }
};

#endif