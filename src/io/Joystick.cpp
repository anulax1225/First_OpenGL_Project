#include "Joystick.hpp"

Joystick::Joystick(int  i) {
    this->id = Joystick::GetId(i); 
    this->Update();
}

void Joystick::Update() {
    if ((this->present = glfwJoystickPresent(this->id))) {
        this->name = glfwGetJoystickName(this->id);
        this->axes = glfwGetJoystickAxes(this->id, &this->axesCount);
        this->buttons = glfwGetJoystickButtons(this->id, &this->buttonCount);
    }
}

float Joystick::AxesState(int axis) {
    return this->present ? axes[axis] : 0.0f;
}

unsigned char Joystick::ButtonState(int button) {
    return this->present ? buttons[button] : GLFW_RELEASE;
}

int Joystick::GetAxesCount() {
    return this->axesCount;
}

int Joystick::GetButtonCount() {
    return this->buttonCount;
}

bool Joystick::IsPresent() {
    return this->present;
}

const char* Joystick::GetName() {
    return this->name;
}

int Joystick::GetId(int i) {
    return GLFW_JOYSTICK_1 + i;
}