#pragma once

#ifndef JTESHADERS_H
#define JTESHADERS_H

#include "../Standard/JTEstructs.h"

#include "pch.h"

class JTEshaders {
private:
	JTEstructs::Shaders shader;

public:
	////////// Constructors //////////

	/*
	* @brief Loads the default vertex and fragment shader
	*/
	JTEshaders();

	/*
	* @brief Loads a custom vertex and fragment shader
	*/
	JTEshaders(std::string vertexShaderSourceFile, std::string fragmentShaderSourceFile);

	////////// Constructor //////////

	////////// Member Functions //////////

	/*
	* @brief Creates the shader program
	*/
	void create();

	/*
	* @brief Starts using the shader program
	*/
	void start();
	
	/*
	* @brief Stops using the shader program
	*/
	void stop();
	
	/*
	* @brief Deletes the shader program
	*/
	void terminate();

	////////// Member Functions //////////
};

#endif // !JTESHADERS_H




