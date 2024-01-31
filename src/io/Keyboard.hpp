#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Keyboard {
    public:
        //GLFW callback function
        static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        //Assesors
        static bool KeyDown(int key);
        static bool KeyWentUp(int key);
        static bool KeyWentDown(int key);

    private:
        //Keys state
        static bool keys[];
        static bool keysChanged[];
        //Assesor
        static bool keyChanged(int key);
};

#endif