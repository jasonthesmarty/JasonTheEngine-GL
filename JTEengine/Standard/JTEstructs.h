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

	struct Buffer_Obj {
		GLuint VAO;
		GLuint VBO;
		GLuint IBO;
		GLuint CBO;
	};

	struct Polygon_Square {
		int x;
		int y;
		int sideLength;
	};

	struct RGBA_val {
		float r;
		float g; 
		float b;
		float a;
	};

}

#endif // !JTESTRUCTS_H



