#include "pch.h"

#include "JTEstandard.h"

// Definitions

JTEstandard::JTEstandard() {}

std::string JTEstandard::getFileContents(const char* filename) {
	std::ifstream file;
	std::string contents = "";
	std::string line = "";
	file.open(filename, std::ios::in);
	while (std::getline(file, line)) {
		contents += line + "\n";
	}
	file.close();

	return contents;
}


