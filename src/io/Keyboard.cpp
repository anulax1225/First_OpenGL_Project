#include "Keyboard.hpp"

bool Keyboard::keys[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysChanged[GLFW_KEY_LAST] = { 0 };

void Keyboard::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //If the button is pressed or down then key is true
    if (action != GLFW_RELEASE) {
        //Preventing key down to frequente
        if(!keys[key]) {
            keys[key] = true;
        }
    } else {
        keys[key] = false;
    }
    //If the button is not down then keyChanged is true
    keysChanged[key] = action != GLFW_REPEAT;
}

bool Keyboard::KeyDown(int key) {
    return keys[key];
}

bool Keyboard::KeyWentUp(int key) {
    return !keys[key] && keyChanged(key);
}

bool Keyboard::KeyWentDown(int key) {
    return keys[key] && keyChanged(key);
}

bool Keyboard::keyChanged(int key) {
    bool ret = keysChanged[key];
    keysChanged[key] = false;
    return ret;
}