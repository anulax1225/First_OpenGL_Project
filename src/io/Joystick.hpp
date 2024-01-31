#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// analog input	button values				//		PS		|		XBOX
#define JOYSTICK_BTN_DOWN 0				    //	X			|	A
#define JOYSTICK_BTN_LEFT 1				    //	Square		|	X
#define JOYSTICK_BTN_UP 2					//	Triangle	|	Y	
#define JOYSTICK_BTN_RIGHT 3				//	Circle		|	B
#define JOYSTICK_SHOULDER_LEFT 4			//	L1			|	LB
#define JOYSTICK_SHOULDER_RIGHT 5			//	R1			|	RB
#define JOYSTICK_TRIGGER_LEFT 6			    //	L2			|	LT
#define JOYSTICK_TRIGGER_RIGHT 7			//	R2			|	RT
#define JOYSTICK_SELECT 8					//	Share		|	Address
#define JOYSTICK_START 9					//	Options		|	Menu
#define JOYSTICK_LEFT_STICK 10				//	L3			|	LS
#define JOYSTICK_RIGHT_STICK 11			    //	R3			|	RS
#define JOYSTICK_HOME 12					//	Home		|	Home
#define JOYSTICK_CLICK 13					//	Touch pad	|	n/a
#define JOYSTICK_DPAD_UP 14				    //	Dpad up		|	Dpad up
#define JOYSTICK_DPAD_RIGHT 15				//	Dpad right	|	Dpad right
#define JOYSTICK_DPAD_DOWN 16				//	Dpad down	|	Dpad down
#define JOYSTICK_DPAD_LEFT 17				//	Dpad left	|	Dpad left

// axes
#define JOYSTICK_AXES_LEFT_STICK_X 0
#define JOYSTICK_AXES_LEFT_STICK_Y 1
#define JOYSTICK_AXES_RIGHT_STICK_X 2
#define JOYSTICK_AXES_LEFT_TRIGGER 3
#define JOYSTICK_AXES_RIGHT_TRIGGER 4
#define JOYSTICK_AXES_RIGHT_STICK_Y 5

class Joystick {
    public:
        Joystick() = delete;
        Joystick(int i);

        void Update();
        float AxesState(int axis);
        unsigned char ButtonState(int button);
        int GetAxesCount();
        int GetButtonCount();
        bool IsPresent();
        const char* GetName();

        static int GetId(int i);

    private:
        int present;
        int id;
        const char* name;

        int axesCount;
        const float* axes;

        int buttonCount;
        const unsigned char* buttons;
};

#endif