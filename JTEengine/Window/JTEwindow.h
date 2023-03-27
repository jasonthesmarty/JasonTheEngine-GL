#pragma once

#ifndef JTEWINDOW_H
#define JTEWINDOW_H

#include "../Dependencies/GLAD/glad.h"
#include "../Dependencies/GLFW/glfw3.h"

#include "pch.h"

class JTEwindow {
private:
	GLFWwindow* window;

	int width, height;
	const char* title;

public:
	JTEwindow(int width, int height, const char* title);

	void create();
	void update();
	void clearBuffers();

	void changeColor(float red, float green, float blue, float alpha);
	void changeColor(float colors[4]);
	void changeColor(int red, int green, int blue, int alpha);
	void changeColor(int colors[4]);

	bool close();
	void terminate();

};

#endif //JTEWINDOW_H
