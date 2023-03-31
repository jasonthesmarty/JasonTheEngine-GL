#include "pch.h"
#include "JTEinput.h"

double mouseX, mouseY;

bool keys[GLFW_KEY_LAST];
bool buttons[GLFW_MOUSE_BUTTON_LAST];

JTEinput::JTEinput() {}

GLFWkeyfun JTEinput::keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
	keys[key] = action != GLFW_RELEASE;
	return GLFWkeyfun();
}

GLFWmousebuttonfun JTEinput::mouse(GLFWwindow* window, int key, int action, int mods) {
	buttons[key] = action != GLFW_RELEASE;
	return GLFWmousebuttonfun();
}

GLFWcursorposfun JTEinput::position(GLFWwindow* window, double xPos, double yPos) {
	mouseX = xPos;
	mouseY = yPos;
	return GLFWcursorposfun();
}

bool JTEinput::keyDown(int key) {
	return keys[key];
}

bool JTEinput::mouseButtonDown(int button) {
	return buttons[button];
}

double JTEinput::getMouseX() {
	return mouseX;
}

double JTEinput::getMouseY() {
	return mouseY;
}