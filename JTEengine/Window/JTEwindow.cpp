#include "pch.h"
#include "JTEwindow.h"


JTEwindow::JTEwindow(int width, int height, const char* title) {
	this->width = width;
	this->height = height;
	this->title = title;
}

void JTEwindow::create() {
	glfwInit();

	if (!glfwInit()) {
		std::cout << "GLFW not initialized" << std::endl;
	}

	window = glfwCreateWindow(this->width, this->height, this->title, 0, 0);

	if (window == 0) {
		std::cout << "Window not created" << std::endl;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
	glfwShowWindow(window);
}

void JTEwindow::update() {
	glfwPollEvents();
	glfwSwapBuffers(window);

}

void JTEwindow::clearBuffers() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void JTEwindow::changeColor(float red, float green, float blue, float alpha) {
	glClearColor(red, green, blue, alpha);
}

void JTEwindow::changeColor(float colors[4]) {
	glClearColor(colors[0], colors[1], colors[2], colors[3]);
}

void JTEwindow::changeColor(int red, int green, int blue, int alpha) {
	float normalizedRed = (float)red / 255;
	float normalizedGreen = (float)green / 255;
	float normalizedBlue = (float)blue / 255;
	float normalizedAlpha = (float)alpha / 255;
	
	glClearColor(normalizedRed, normalizedGreen, normalizedBlue, normalizedAlpha);
}

void JTEwindow::changeColor(int colors[4]) {
	float normalizedRed = (float)colors[0] / 255;
	float normalizedGreen = (float)colors[1] / 255;
	float normalizedBlue = (float)colors[2] / 255;
	float normalizedAlpha = (float)colors[3] / 255;

	glClearColor(normalizedRed, normalizedGreen, normalizedBlue, normalizedAlpha);
}

bool JTEwindow::close() {
	return glfwWindowShouldClose(window);
}

void JTEwindow::terminate() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

