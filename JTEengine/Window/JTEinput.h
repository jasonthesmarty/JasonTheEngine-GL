#pragma once

#ifndef JTEINPUT_H
#define JTEINPUT_H

#include "../Dependencies/GLFW/glfw3.h"

#include "pch.h"

class JTEinput {
public:
	////////// Constructor //////////

	/*
	* @brief An empty constructor for the Input Class
	*/
	JTEinput();

	////////// Constructor //////////

	////////// Member Functions //////////

	/*
	* @brief Do not use in program
	* @brief This used to set the keyboard button callback in the Window Class
	*/
	static GLFWkeyfun keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
	
	/*
	* @brief Do not use in program
	* @brief This used to set the mouse button callback in the Window Class
	*/
	static GLFWmousebuttonfun mouse(GLFWwindow* window, int key, int action, int mods);
	
	/*
	* @brief Do not use in program
	* @brief This used to set the mouse position callback in the Window Class
	*/
	static GLFWcursorposfun position(GLFWwindow* window, double xPos, double yPos);


	/*
	* @brief Returns a boolean value if the keyboard button selected was pressed
	* 
	* @return true - If the keyboard button was pressed
	* @return false - If the keyboard button was not pressed
 	*/
	bool keyDown(int key);
	
	/*
	* @brief Returns a boolean value if the mouse button selected was pressed
	*
	* @return true - If the mouse button was pressed
	* @return false - If the mouse button was not pressed
	*/
	bool mouseButtonDown(int button);


	/*
	* @brief Returns the X position of the mouse
	* 
	* @return mouseX - Value of the X coordinate of the mouse
	*/
	double getMouseX();
	
	/*
	* @brief Returns the Y position of the mouse
	*
	* @return mouseY - Value of the Y coordinate of the mouse
	*/
	double getMouseY();

	////////// Member Functions //////////
};

#endif // ! JTEINPUT_H
