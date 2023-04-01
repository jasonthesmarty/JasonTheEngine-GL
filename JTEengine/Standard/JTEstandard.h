#pragma once

#ifndef JTESTANDARD_H
#define JTESTANDARD_H

#include "pch.h"

class JTEstandard {
public:
	////////// Constructor //////////

	/*
	* @brief An empty constructor for the Standard Class
	*/
	JTEstandard();

	////////// Constructor //////////

	////////// Member Functions //////////

	/*
	* @brief Prints a value
	*/
	template<typename Type>
	void print(Type data);

	/*
	* @brief Prints a value with a new line
	*/
	template<typename Type>
	void println(Type data);
	
	/*
	* @brief Turns a number value into a string
	* 
	* @return std::string - from the input data
	*/
	template<typename Type>
	std::string string(Type data);

	////////// Member Functions //////////
};

#include "JTEstandard.ipp"

#endif // !JTESTANDARD_H


