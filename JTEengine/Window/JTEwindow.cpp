#include "pch.h"

#include "JTEwindow.h"
#include "JTEinput.h"

// Definitions

JTEwindow::JTEwindow(int width, int height, const char* title) {
	win.width = width;
	win.height = height;
	win.title = title;

	this->frames = 0;
}

void JTEwindow::create() {
	glfwInit();

	if (!glfwInit()) {
		std::cout << "GLFW not initialized" << std::endl;
	}

	win.window = glfwCreateWindow(win.width, win.height, win.title, 0, 0);

	glfwSetKeyCallback(win.window, (GLFWkeyfun)JTEinput().keyboard);
	glfwSetMouseButtonCallback(win.window, (GLFWmousebuttonfun)JTEinput().mouse);
	glfwSetCursorPosCallback(win.window, (GLFWcursorposfun)JTEinput().position);

	if (win.window == 0) {
		std::cout << "Window not created" << std::endl;
	}

	glfwMakeContextCurrent(win.window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(0);
	glfwShowWindow(win.window);
}

void JTEwindow::update() {
	glfwPollEvents();
	glfwSwapBuffers(win.window);

	int width, height;
	glfwGetWindowSize(win.window, &width, &height);
	glViewport(0, 0, width, height);
}

void JTEwindow::vSync(bool ON_or_OFF) {
	if (ON_or_OFF) {
		glfwSwapInterval(1);
	}
	else {
		glfwSwapInterval(0);
	}
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
	return glfwWindowShouldClose(win.window);
}

void JTEwindow::terminate() {
	glfwDestroyWindow(win.window);
	glfwTerminate();
}

int JTEwindow::getWidth() {
	return win.width;
}

int JTEwindow::getHeight() {
	return win.height;
}

const char* JTEwindow::getTitle() {
	return win.title;
}

void JTEwindow::getWindowDimensions(int* width, int* height) {
	glfwGetWindowSize(win.window, width, height);
}

int JTEwindow::getTimeElapsed() {
	return (int)round(glfwGetTime());
}

std::array<int, 4> JTEwindow::getTimeElapsedFormatted() {
	std::array<int, 4> time = { 0, 0, 0, 0 };

	if ((int)round(glfwGetTime()) >= elapsedSeconds + 1) {
		Seconds++;
		elapsedSeconds = (int)round(glfwGetTime());
	}

	if (Seconds >= 60) {
		Seconds = 0;
		Minutes++;
	}
	else if (Minutes >= 60) {
		Minutes = 0;
		Hours++;
	}
	else if (Hours >= 60) {
		Hours = 0;
		Days++;
	}

	time[0] = Seconds;
	time[1] = Minutes;
	time[2] = Hours;
	time[3] = Days;

	return time;
}

void JTEwindow::clock(float* fps, float* milliseconds) {
	frames++;

	currentTime = glfwGetTime();
	double deltaTime = currentTime - previousTime;

	if (deltaTime >= 1.0 / 30.0) {
		*fps = (1.0f / deltaTime) * frames;
	
		*milliseconds = (deltaTime / frames) * 1000;

		previousTime = currentTime;
		currentTime = glfwGetTime();
		frames = 0;
	}
}

void JTEwindow::memUsage(long int* memUse) {
	HANDLE process = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS_EX memory;

	GetProcessMemoryInfo(process, reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&memory), sizeof(memory));

	*memUse = memory.WorkingSetSize;
}
