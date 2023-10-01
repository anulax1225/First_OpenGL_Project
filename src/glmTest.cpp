#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "../lib/glm/gtc/type_ptr.hpp"
#include "../include/glmTest.hpp"
#include <iostream>

void glmTest() {
    //Test of GLM
    //Instansiating a vector 4D
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    //Instansiating an identity matrix
    /*
        Identity matrix 
        ---------
        |1|0|0|0|
        |0|1|0|0|
        |0|0|1|0|
        |0|0|0|1|
        ---------
    */
    glm::mat4 trans = glm::mat4(1.0f);
    //Making it a translation rotation and scale matrix
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    //Loging result
    std::cout << "x : " << vec.x << std::endl << "y : " << vec.y << std::endl << "z : " << vec.z << std::endl; 
    //Translating the vector with the translation matrix
    vec = trans * vec;
    std::cout << "x : " << vec.x << std::endl << "y : " << vec.y << std::endl << "z : " << vec.z << std::endl; 

}