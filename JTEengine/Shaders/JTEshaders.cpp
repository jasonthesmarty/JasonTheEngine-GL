#include "pch.h"
#include "JTEshaders.h"
#include "../Standard/JTEstandard.h"

JTEstandard jstd;

JTEshaders::JTEshaders() {
	shader.VertShaderSrcSTD = jstd.getFileContents("..\\JasonTheEngine\\JTEengine\\Shaders\\vertex.glsl");
	shader.FragShaderSrcSTD = jstd.getFileContents("..\\JasonTheEngine\\JTEengine\\Shaders\\fragment.glsl");
	
	shader.VertShaderSrcCC = shader.VertShaderSrcSTD.c_str();
	shader.FragShaderSrcCC = shader.FragShaderSrcSTD.c_str();
	
	// jstd.println(vertexShaderSource);
	// jstd.println(fragmentShaderSource);
}

JTEshaders::JTEshaders(std::string vertexShaderSourceFile, std::string fragmentShaderSourceFile) {
	shader.VertShaderSrcSTD = jstd.getFileContents(vertexShaderSourceFile.c_str());
	shader.FragShaderSrcSTD = jstd.getFileContents(fragmentShaderSourceFile.c_str());

	shader.VertShaderSrcCC = shader.VertShaderSrcSTD.c_str();
	shader.FragShaderSrcCC = shader.FragShaderSrcSTD.c_str();

	// jstd.println(vertexShaderSource);
	// jstd.println(fragmentShaderSource);
}

void JTEshaders::create() {
	shader.vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader.vertShader, 1, &shader.VertShaderSrcCC, NULL);
	glCompileShader(shader.vertShader);

	shader.fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader.fragShader, 1, &shader.FragShaderSrcCC, NULL);
	glCompileShader(shader.fragShader);

	shader.shaderProgram = glCreateProgram();
	glAttachShader(shader.shaderProgram, shader.vertShader);
	glAttachShader(shader.shaderProgram, shader.fragShader);
	glLinkProgram(shader.shaderProgram);
}

void JTEshaders::start() {
	glUseProgram(shader.shaderProgram);
}

void JTEshaders::stop() {
	glUseProgram(0);
}

void JTEshaders::terminate() {
	glDeleteProgram(shader.shaderProgram);
}