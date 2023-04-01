#pragma once

#include "pch.h"


template<typename Type>
void JTEstandard::print(Type data) {
	std::cout << data;
}

template<typename Type>
void JTEstandard::println(Type data) {
	std::cout << data << std::endl;
}

template<typename Type>
std::string JTEstandard::string(Type data) {
	std::string str = std::to_string(data);
	return str;
}
