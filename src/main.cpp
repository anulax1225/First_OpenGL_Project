#include "../lib/glad/glad.h"
#include <GLFW/glfw3.h>
#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "../lib/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <string>

#include "../include/Shader.hpp"


void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);
std::string loadShaderSrc(std::string path);

int main() {

    //Const variables
    const int WIDTH = 800;
    const int HEIGHT = 600;

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

    Shader shader = Shader("assets/shaders/vertex_core.glsl", "assets/shaders/fragment_core.glsl");

    // Creating a array of vertices to create a square from them
    float vertices[] = {
        0.5f, 0.5f, 0.0f, //top right
        -0.5f, 0.5f, 0.0f, // top left
        -0.5f, -0.5f, 0.0f,  //bottum left
         0.5f, -0.5f, 0.0f, // bottum right
    };
    //Indices to draw the triangle from the vertices
    unsigned int indices[] = {
        0, 1, 2, //first triangle
        2, 3, 0, //second triangle
    };
    // float vertices[] = {
    //     //position          color
    //    -0.25f, -0.5f, 0.0f, 1.0f, 1.0f, 0.5f,
    //     0.15f, 0.0f, 0.0f, 0.5f, 1.0f, 0.75f,
    //     0.0f, 0.5f, 0.0f, 0.6f, 1.0f, 0.2f,
    //     0.5f, -0.4f, 0.0f, 1.0f, 0.2f, 1.0f,
    // };
    // unsigned int indices[] = {
    //     0, 1, 2,
    //     3, 2, 1,
    // };

    //Creating VAO(vertex array object), VBO(vertex buffer object), EBO(element buffer object)
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Binding VAO
    glBindVertexArray(VAO);

    //Binding VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Set attribute pointer
    //Indicates to the GPU how to distribute the data
    //Weird cast to a void pointer for OpenGL
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    //Set up the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glm::mat4 transform = glm::mat4(1.0f);
    

    //Main loop
    while(!glfwWindowShouldClose(window)) {
        //Gives the background color
        glClearColor(0.1f,0.4f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);        

        //Update transforme matrix
        transform = glm::rotate(transform, glm::radians((float)glfwGetTime()/50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.Activate();
        shader.SetMat4("transform", transform);
        //Get basique user input to close the window
        ProcessInput(window);    
        //Draw shapes
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        //Swaps the image buffer for the next one
        glfwSwapBuffers(window);
        // Computing next frame while the last one is rendered
        glfwPollEvents();
    } 

    //Once finished termenate the window and delete the data from the GPU
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

//Resizes the view port when user changes the screen size
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}