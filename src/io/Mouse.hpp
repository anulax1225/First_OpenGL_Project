#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "../../lib/glad/glad.h"
#include <GLFW/glfw3.h>

class Mouse {
    public:
        //GLFW callback function
        static void CursorPosCallback(GLFWwindow* window, double _x, double _y);
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void MouseWheelCallback(GLFWwindow* window, double dx, double dy);

        //Mouse position assesors
        static double GetMouseX();
        static double GetMouseY();

        //Mouse scroll assesors
        static double GetDX();
        static double GetDY();
        static double GetScrollDX();
        static double GetScrollDY();

        //Mouse buttons assesors
        static bool Button(int button);
        static bool ButtonWentUp(int button);
        static bool ButtonWentDown(int button);

    private:
        static double x;
        static double y;

        static double lastX;
        static double lastY;

        static double dX;
        static double dY;

        static double scrollDX;
        static double scrollDY;

        static bool firstMouse;

        static bool buttons[];
        static bool buttonsChanged[];

        static bool buttonChanged(int button);
};

#endif