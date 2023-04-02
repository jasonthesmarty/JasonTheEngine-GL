#pragma once

#ifndef JTEWINDOW_H
#define JTEWINDOW_H

#include "../Dependencies/GLAD/glad.h"
#include "../Dependencies/GLFW/glfw3.h"

#include "../Standard/JTEstructs.h"

#include "pch.h"

class JTEwindow {
private:
	JTEstructs::Window win;

public:
	////////// Constructor //////////

	/*
	* @brief Initialize the width, height, and title of the window
	* 
	* @param width - Sets the window width
	* @param height - Sets the window height
	* @param title - Sets the window title
	*/
	JTEwindow(int width, int height, const char* title);

	////////// Constructor //////////

	////////// Member Functions //////////

	/*
	* @brief Creates the window
	*/
	void create();

	/* 
	* @brief Updates the window
	*/
	void update();

	/*
	* @brief Clears the color and depth buffer (via glClear())
	*/
	void clearBuffers();


	/*
	* @brief Changes the background color of the window.
	* 
	* @param red - Sets the red value (OpenGL Normalized Values, 0.0f - 1.0f)
	* @param green - Sets the green value (OpenGL Normalized Values, 0.0f - 1.0f)
	* @param blue - Sets the blue value (OpenGL Normalized Values, 0.0f - 1.0f)
	* @param alpha - Sets the alpha value (OpenGL Normalized Values, 0.0f - 1.0f)
 	*/
	void changeColor(float red, float green, float blue, float alpha);
	
	/*
	* @brief Changes the background color of the window.
	* 
	* @param colors - Sets the red, green, blue, and alpha values (OpenGL Normalized Values, 0.0f - 1.0f)
	*/
	void changeColor(float colors[4]);
	
	/*
	* @brief Changes the background color of the window.
	*
	* @param red - Sets the red value (Pixel Values, 0 - 255)
	* @param green - Sets the green value (Pixel Values, 0 - 255)
	* @param blue - Sets the blue value (Pixel Values, 0 - 255)
	* @param alpha - Sets the alpha value (Pixel Values, 0 - 255)
	*/
	void changeColor(int red, int green, int blue, int alpha);
	
	/*
	* @brief Changes the background color of the window.
	*
	* @param colors - Sets the red, green, blue, and alpha values (Pixel Values, 0 - 255)
	*/
	void changeColor(int colors[4]);


	/*
	* @brief Returns a boolean value depending on the closing state of the window
	*
	* @return true - If the window is closing
	* @return false - If the window is not closing
	*/
	bool close();

	/*
	* @brief Terminates the window and its resources
	*/
	void terminate();

	////////// Member Functions //////////
};

#endif // ! JTEWINDOW_H
