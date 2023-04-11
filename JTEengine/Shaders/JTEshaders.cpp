#include "pch.h"

#include "JTEshaders.h"
#include "../Standard/JTEstandard.h"

// Variables

JTEstandard jstd;

// Definitions

JTEshaders::JTEshaders() {
	shader.VertShaderSrcSTD = "";
	shader.FragShaderSrcSTD = "";


	shader.VertShaderSrcCC = 
	R"(
	#version 460

	layout (location = 0) in vec3 position;
	layout (location = 1) in vec3 color;

	out vec3 VertColor;

	void main() {
		gl_Position = vec4(position, 1.0);
		VertColor = color;
	}
	)";
	shader.FragShaderSrcCC = 
	R"(
	#version 460

	in vec3 VertColor;

	out vec4 FragColor;

	void main() {
		FragColor = vec4(VertColor, 1.0);
	}
	)";
	
	//jstd.println(shader.VertShaderSrcSTD);
	//jstd.println(shader.FragShaderSrcSTD);
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