#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include <iostream>

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

int main() {

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

    //Const variables
    const int WIDTH = 1000;
    const int HEIGHT = 800;
    //Init of middleware
    glfwInit();
    //Defines the middleware for OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Middleware only defined for Apple
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //Creation of the window
    GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"First OpenGL window", NULL, NULL);
    //Verifing that the window was correctly created else ends the program
    if (window == NULL) {
        std::cout << "Could not open the window.\n";
        // if couldn't open the window terminate glfw window and ends the program
        glfwTerminate();
        return -1;
    }
    //Sets focus on the current window
    glfwMakeContextCurrent(window);
    //Initializes GLAD and verifies that it didn't fail
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD.\n";
        // if glad failed terminate glfw window and ends the program
        glfwTerminate();
        return -1; 
    }
    //Sets the size of the view port
    //The view port says to OpenGL how to render thing depending on the screen size
    glViewport( 0, 0, WIDTH, HEIGHT);
    //Sets behavior when window is resized
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
    //Main loop
    while(!glfwWindowShouldClose(window)) {
        //Swaps the image buffer for the next one
        glfwSwapBuffers(window);
        // Computing next frame while the last one is rendered
        glfwPollEvents();
    } 
    //Once finished termenate the window
    glfwTerminate();
    return 0;
}

//Resizes the view port when user changes the screen size
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}