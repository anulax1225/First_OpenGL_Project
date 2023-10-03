#include "../lib/glad/glad.h"
#include <GLFW/glfw3.h>
#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "../lib/glm/gtc/type_ptr.hpp"
#include "../lib/stb_image/stb_image.h"

#include <iostream>
#include <string>

#include "Shader.hpp"
#include "io/Keyboard.hpp"
#include "io/Mouse.hpp"
#include "io/Joystick.hpp"
#include "io/Camera.hpp"

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

int WIDTH = 800;
int HEIGHT = 600;

float mixVal = 0.5f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Joystick mainJ = Joystick(0);

Camera camera = Camera(glm::vec3(0.0f,0.0f,3.0f));

int main() {

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
    //Other callbacks
    glfwSetKeyCallback(window, Keyboard::KeyboardCallback);
    glfwSetCursorPosCallback(window, Mouse::CursorPosCallback);
    glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
    glfwSetScrollCallback(window, Mouse::MouseWheelCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    Shader shader = Shader("assets/shaders/vertex_core.glsl", "assets/shaders/fragment_core.glsl");

    float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
    //Creating VAO(vertex array object), VBO(vertex buffer object), EBO(element buffer object)
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Binding VAO
    glBindVertexArray(VAO);

    //Binding VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Set attribute pointer
    //Indicates to the GPU how to segment and distribute the data in the VBO
    //(id, number of values, type of values, normelized: false, size of a unit, offset)
    //Cast to a void pointer on the offset for OpenGL
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); 

    //Creating texture reference
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    //Parameterising the last bound texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //Loading the image
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("assets/textures/salomon.jpeg", &width, &height, &nChannels, 0);

    if(data) {
        //Loads the image data in the last bound texture 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Could not load image" << std::endl;
    }
    
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    data = stbi_load("assets/textures/index.png", &width, &height, &nChannels, 0);

    if(data) {
        //Loads the image data in the last bound texture 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Could not load image" << std::endl;
    }

    stbi_image_free(data);

    shader.Activate();
    shader.SetInt("texture1", 0);
    shader.SetInt("texture2", 1);

    //Main loop
    while(!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;
        //Gives the background color
        glClearColor(0.1f,0.4f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);      
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);      
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f, 0.5f, 0.0f));
        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(camera.zoom), (float)WIDTH/(float)HEIGHT, 0.1f, 100.f);
        //Get basique user input to close the window
        ProcessInput(window);  
        shader.Activate();
        shader.SetFloat("mixVal", mixVal);
        //Update transforme matrix
        shader.SetMat4("model", model);
        shader.SetMat4("view", view);
        shader.SetMat4("projection", projection);
        //Draw shapes
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        //Swaps the image buffer for the next one
        glfwSwapBuffers(window);
        // Computing next frame while the last one is rendered
        glfwPollEvents();
    } 

    //Once finished termenate the window and delete the data from the GPU
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

//Resizes the view port when user changes the screen size
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    WIDTH = width;
    HEIGHT = height;
}

void ProcessInput(GLFWwindow* window) {
    if (Keyboard::KeyDown(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
    if (Keyboard::KeyDown(GLFW_KEY_W)) {
        camera.UpdateCameraPosition(CameraDirection::FORWARD, deltaTime);
    }
    if (Keyboard::KeyDown(GLFW_KEY_S)) {
        camera.UpdateCameraPosition(CameraDirection::BACKWARD, deltaTime);
    }
    if (Keyboard::KeyDown(GLFW_KEY_A)) {
        camera.UpdateCameraPosition(CameraDirection::LEFT, deltaTime);
    }
    if (Keyboard::KeyDown(GLFW_KEY_D)) {
        camera.UpdateCameraPosition(CameraDirection::RIGHT, deltaTime);
    }
    if (Keyboard::KeyDown(GLFW_KEY_LEFT_SHIFT)) {
        camera.UpdateCameraPosition(CameraDirection::DOWN, deltaTime);
    }
    if (Keyboard::KeyDown(GLFW_KEY_SPACE)) {
        camera.UpdateCameraPosition(CameraDirection::UP, deltaTime);
    }

    double dx = Mouse::GetDX(), dy = Mouse::GetDY();
    if (dx != 0 || dy != 0) {
        camera.UpdateCameraDirection(dx, dy);
    }

    double scrollDy = Mouse::GetScrollDY();
    if(scrollDy != 0) {
        camera.UpdateCameraZoom(scrollDy);
    }
} 