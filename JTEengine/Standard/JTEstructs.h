#pragma once

#ifndef JTESTRUCTS_H
#define JTESTRUCTS_H

#include "pch.h"

namespace JTEstructs {
	
	struct Window {
		int width;
		int height;
		const char* title;
		GLFWwindow* window;
	};

	struct Shaders {
		std::string VertShaderSrcSTD;
		std::string FragShaderSrcSTD;
		const char* VertShaderSrcCC;
		const char* FragShaderSrcCC;

		GLuint vertShader;
		GLuint fragShader;
		GLuint shaderProgram;
	};

	struct Polygon_Square {
		int x;
		int y;
		int sideLength;
	};

}

#endif // !JTESTRUCTS_H



