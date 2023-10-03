#include "Mouse.hpp"

double Mouse::x = 0;
double Mouse::y = 0;

double Mouse::lastX = 0;
double Mouse::lastY = 0;

double Mouse::dX = 0;
double Mouse::dY = 0;

double Mouse::scrollDX = 0;
double Mouse::scrollDY = 0;

bool Mouse::firstMouse;

bool Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::buttonsChanged[GLFW_MOUSE_BUTTON_LAST] = { 0 };

void Mouse::CursorPosCallback(GLFWwindow* window, double _x, double _y) {
    x = _x;
    y = -_y;

    if(firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }
    dX = x - lastX;
    dY = y -lastY;
    lastX = x;
    lastY = y;
}

void Mouse::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action != GLFW_RELEASE) {
        if(!buttons[button]) {
            buttons[button] = true;
        }
    } else {
        buttons[button] = false;
    }

    buttonsChanged[button] = action != GLFW_REPEAT;
}

void Mouse::MouseWheelCallback(GLFWwindow* window, double dx, double dy) {
    scrollDX = dx;
    scrollDY = dy;
} 

double Mouse::GetMouseX() {
    return x;
}

double Mouse::GetMouseY() {
    return y;
} 

double Mouse::GetDX() {
    double _dX = dX;
    dX = 0;
    return _dX;
}

double Mouse::GetDY() {
    double _dY = dY;
    dY = 0;
    return _dY;
}

double Mouse::GetScrollDX() {
    double _scrollDX = scrollDX;
    scrollDX = 0;
    return _scrollDX;
}

double Mouse::GetScrollDY() {
    double _scrollDY = scrollDY;
    scrollDY = 0;
    return _scrollDY;
} 

bool Mouse::Button(int button) {
    return buttons[button];
}

bool Mouse::ButtonWentUp(int button) {
    return !buttons[button] && buttonChanged(button);
}

bool Mouse::ButtonWentDown(int button) {
    return buttons[button] && buttonChanged(button);
}

bool Mouse::buttonChanged(int button) {
    bool ret = buttonsChanged[button];
    buttons[button] = false;
    return ret;
}
