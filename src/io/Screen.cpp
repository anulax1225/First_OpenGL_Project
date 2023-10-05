#include "Screen.hpp"

unsigned int Screen::SRC_WIDTH = 1500;
unsigned int Screen::SRC_HEIGHT = 1000;

void Screen::FrameResizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    Screen::SRC_WIDTH = width;
    Screen::SRC_HEIGHT = height;
}

Screen::Screen() {
    this->window = nullptr;
}

bool Screen::Init(std::string windowName) {
    this->window = glfwCreateWindow(Screen::SRC_WIDTH, Screen::SRC_HEIGHT, windowName.c_str(), NULL, NULL);
    if (!this->window) {
        // if couldn't open the window terminate glfw window and ends the program
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(this->window);
    return true;
}

void Screen::SetResponce() {

    glViewport(0, 0, Screen::SRC_WIDTH, Screen::SRC_HEIGHT);
    
    glfwSetFramebufferSizeCallback(this->window, Screen::FrameResizeCallback);
    glfwSetKeyCallback(this->window, Keyboard::KeyboardCallback);
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetMouseButtonCallback(this->window, Mouse::MouseButtonCallback);
    glfwSetScrollCallback(this->window, Mouse::MouseWheelCallback);
    glfwSetCursorPosCallback(this->window, Mouse::CursorPosCallback);
}

void Screen::Update() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::NewFrame() {
    //Swaps the image buffer for the next one
    glfwSwapBuffers(this->window);
    // Computing next frame while the last one is rendered
    glfwPollEvents();
}

bool Screen::ShouldClose() {
    return glfwWindowShouldClose(this->window);
}

void Screen::Close() {
    glfwSetWindowShouldClose(this->window, true);
}