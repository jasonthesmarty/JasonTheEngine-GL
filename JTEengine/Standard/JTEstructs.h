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
		GLuint CBO;
	};

	struct Polygon_Square {
		int x;
		int y;
		int sideLength;
	};

	struct Image {
		int stb_width;
		int stb_height;
		int stb_channels;
		
		float w_multiplier;
		float h_multiplier;

		int x;
		int y;
		int width;
		int height;
		const char* filename;
	};

	struct RGBA_val {
		float r;
		float g; 
		float b;
		float a;
	};

	struct OriginalDimensions {
		int oWidth;
		int oHeight;
	};

}

#endif // !JTESTRUCTS_H



