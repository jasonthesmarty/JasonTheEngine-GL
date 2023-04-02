#include "pch.h"
#include "JTEshaders.h"
#include "../Standard/JTEstandard.h"

JTEstandard jstd;

JTEshaders::JTEshaders() {
	vertexShaderSourceSTD = jstd.getFileContents("..\\JasonTheEngine\\JTEengine\\Shaders\\vertex.glsl");
	fragmentShaderSourceSTD = jstd.getFileContents("..\\JasonTheEngine\\JTEengine\\Shaders\\fragment.glsl");
	
	vertexShaderSource = vertexShaderSourceSTD.c_str();
	fragmentShaderSource = fragmentShaderSourceSTD.c_str();
	
	// jstd.println(vertexShaderSource);
	// jstd.println(fragmentShaderSource);
}

JTEshaders::JTEshaders(std::string vertexShaderSourceFile, std::string fragmentShaderSourceFile) {
	vertexShaderSourceSTD = jstd.getFileContents(vertexShaderSourceFile.c_str());
	fragmentShaderSourceSTD = jstd.getFileContents(fragmentShaderSourceFile.c_str());

	vertexShaderSource = vertexShaderSourceSTD.c_str();
	fragmentShaderSource = fragmentShaderSourceSTD.c_str();

	// jstd.println(vertexShaderSource);
	// jstd.println(fragmentShaderSource);
}

void JTEshaders::create() {
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
}

void JTEshaders::start() {
	glUseProgram(shaderProgram);
}

void JTEshaders::stop() {
	glUseProgram(0);
}

void JTEshaders::terminate() {
	glDeleteProgram(shaderProgram);
}