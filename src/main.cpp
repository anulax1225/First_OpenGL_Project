#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

#include <iostream>
#include <string>

#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Material.hpp"
#include "graphics/models/Lamp.hpp"
#include "io/Keyboard.hpp"
#include "io/Mouse.hpp"
#include "io/Joystick.hpp"
#include "io/Camera.hpp"
#include "io/Screen.hpp"

void ProcessInput();

float mixVal = 0.5f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Screen screen = Screen();
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

    //Verifing that the window was correctly created else ends the program
    if (!screen.Init("OpenGL Engine")) {
        std::cout << "Could not open the window.\n";
        return -1;
    }

    //Initializes GLAD and verifies that it didn't fail
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD.\n";
        // if glad failed terminate glfw window and ends the program
        glfwTerminate();
        return -1; 
    }
    screen.SetResponce();

    glEnable(GL_DEPTH_TEST);

    Shader shader = Shader("assets/shaders/object.vs", "assets/shaders/object.fs");
    Shader lampShader = Shader("assets/shaders/object.vs", "assets/shaders/lamp.fs");
    Cube cube = Cube(glm::vec3(1.0f, 0.0f, 0.5f), glm::vec3(0.75f), Material::chrome);
    Lamp lamp = Lamp(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(-1.0f, -0.5f, -0.5f), glm::vec3(0.25f));
    cube.Init();
    cube.angle = 90.0f;
    lamp.Init();
    //Main loop
    while(!screen.ShouldClose()) {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;
        //Gives the background color
        screen.Update();

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(camera.GetZoom()), (float)Screen::SRC_WIDTH/(float)Screen::SRC_HEIGHT, 0.1f, 100.f);
        //Get basique user input to close the window
        ProcessInput();  
        shader.Activate();
        shader.Set3Float("light.position", lamp.position);
        shader.Set3Float("viewPos", camera.GetPosition());
        shader.Set3Float("light.ambient", lamp.ambient);
        shader.Set3Float("light.diffuse", lamp.diffuse);
        shader.Set3Float("light.specular", lamp.specular);
        //shader.SetFloat("mixVal", mixVal);
        //Update transforme matrix
        shader.SetMat4("view", view);
        shader.SetMat4("projection", projection);

        cube.Render(shader);
        
        lampShader.Activate();
        lampShader.SetMat4("view", view);
        lampShader.SetMat4("projection", projection);
        lamp.Render(lampShader);
        screen.NewFrame();
    } 

    //Once finished termenate the window and delete the data from the GPU
    cube.Cleanup();
    glfwTerminate();
    return 0;
}

void ProcessInput() {
    if (Keyboard::KeyDown(GLFW_KEY_ESCAPE)) {
        screen.Close();
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
        camera.SetZoom(scrollDy);
    }
} 