#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Mouse.hpp"
#include "Keyboard.hpp"


class Screen {
    public:
        static unsigned int SRC_WIDTH;
        static unsigned int SRC_HEIGHT;
        static void FrameResizeCallback(GLFWwindow* window, int width, int height);

        Screen();

        bool Init(std::string name);
        void SetResponce();
        void Update();
        void NewFrame();
        bool ShouldClose();
        void Close();
    
    private:
        GLFWwindow* window;
};

#endif