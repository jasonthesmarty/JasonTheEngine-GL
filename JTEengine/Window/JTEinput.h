#pragma once

#ifndef JTEINPUT_H
#define JTEINPUT_H

#include "../Dependencies/GLFW/glfw3.h"

#include "pch.h"

class JTEinput {
public:
	JTEinput();

	static GLFWkeyfun keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
	static GLFWmousebuttonfun mouse(GLFWwindow* window, int key, int action, int mods);
	static GLFWcursorposfun position(GLFWwindow* window, double xPos, double yPos);

	bool keyDown(int key);
	bool mouseButtonDown(int button);

	double getMouseX();
	double getMouseY();

};

#endif // ! JTEINPUT_H
