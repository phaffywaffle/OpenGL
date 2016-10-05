#pragma once

#include "defines.h"
#include "Camera.h"
#include "Light.h"

#define KEY_W 0
#define KEY_A 1
#define KEY_S 2
#define KEY_D 3
#define KEY_E 4
#define KEY_Q 5
#define KEY_SPACE 6
#define KEY_UP 7
#define KEY_LEFT 8
#define KEY_DOWN 9
#define KEY_RIGHT 10
#define KEY_NUMPAD_0 11
#define KEY_NUMPAD_1 12

#define KEY_NUMPAD_4 13
#define KEY_NUMPAD_5 14
#define KEY_NUMPAD_6 15
#define KEY_NUMPAD_7 16
#define KEY_NUMPAD_8 17
#define KEY_NUMPAD_9 18

#define KEY_NUMPAD_UP KEY_NUMPAD_8
#define KEY_NUMPAD_LEFT KEY_NUMPAD_4
#define KEY_NUMPAD_DOWN KEY_NUMPAD_5
#define KEY_NUMPAD_RIGHT KEY_NUMPAD_6

#define KEYS_SIZE 19

internal uint32 keys[KEYS_SIZE];
internal bool key_was_pressed[KEYS_SIZE];

class 
Window
{
private:
	GLFWwindow* window;
public:
	Window(uint32, uint32, char*);
	~Window();
	// Necessary?
	GLFWwindow* getWindow();
	bool isOpen();
	void clear();
	void update(Camera*, Light*);
	void updateKeys(Camera*, Light*);
	void updateCursor(Camera*);
	void close();
};