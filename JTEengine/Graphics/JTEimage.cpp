#include "pch.h"
#include "JTEimage.h"

#define STB_IMAGE_IMPLEMENTATION
#include <Dependencies/STB/stb_image.h>

// Definitions

JTEimage::JTEimage(int x, int y, const char* filename, JTEwindow* window, JTEshaders shaders) {
	img.x = x;
	img.y = y;
	img.filename = filename;
	this->shaders = shaders;
	this->window = window;
	this->type = 0;
}

JTEimage::JTEimage(int x, int y, int width, int height, const char* filename, JTEwindow* window, JTEshaders shaders) {
	img.x = x;
	img.y = y;
	img.width = width;
	img.height = height;
	oDimen.oWidth = width;
	oDimen.oHeight = height;
	img.filename = filename;
	this->shaders = shaders;
	this->window = window;
	this->type = 1;
	originalWidth = width;
	originalHeight = height;
}

void JTEimage::render() {
	unsigned char* imageData = stbi_load(img.filename, &img.stb_width, &img.stb_height, &img.stb_channels, STBI_rgb_alpha);

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.stb_width, img.stb_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData);

	float widthHalf = (float)this->window->getWidth() / 2;
	float heightHalf = (float)this->window->getHeight() / 2;

	float X = (1 - (img.x / widthHalf)) * -1;
	float Y = (1 - (img.y / heightHalf));

	if (this->type == 0) {
		WIDTH = (img.stb_width / widthHalf);
		HEIGHT = (img.stb_height / heightHalf);
		img.width = img.stb_width;
		img.height = img.stb_height;
	} 
	else if (this->type == 1) {
		WIDTH = (img.width / widthHalf);
		HEIGHT = (img.height / heightHalf);
	}

	float vertices[6][4] = {
		// Vertex Coords        // Texture Coords
		{X, Y - HEIGHT,            0.0f, 1.0f},
		{X + WIDTH, Y,             1.0f, 0.0f},
		{X + WIDTH, Y - HEIGHT,    1.0f, 1.0f},
		{X, Y - HEIGHT,            0.0f, 1.0f},
		{X + WIDTH, Y,             1.0f, 0.0f},
		{X, Y,                     0.0f, 0.0f}
	};
	float colors[] = {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};

	// VAO
	glGenVertexArrays(1, &buf.VAO);
	glBindVertexArray(buf.VAO);

	// VBO
	glGenBuffers(1, &buf.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, buf.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	// CBO
	glGenBuffers(1, &buf.CBO);
	glBindBuffer(GL_ARRAY_BUFFER, buf.CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Drawing
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void JTEimage::erase() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteVertexArrays(1, &buf.VAO);
	glDeleteBuffers(1, &buf.VBO);
	glDeleteBuffers(1, &buf.CBO);
	glDeleteTextures(1, &textureID);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void JTEimage::setX(int x) {
	img.x = x;
}

void JTEimage::setY(int y) {
	img.y = y;
}

void JTEimage::setWidth(int width) {
	img.width = width;
	oDimen.oWidth = width;
}

void JTEimage::setLength(int height) {
	img.height = height;
	oDimen.oHeight = height;
}

int JTEimage::getX() {
	return img.x;
}

int JTEimage::getY() {
	return img.y;
}

int JTEimage::getWidth() {
	return img.width;
}

int JTEimage::getHeight() {
	return img.height;
}

void JTEimage::dilate(float multiplier) {
	img.width = (int)((float)oDimen.oWidth * multiplier);
	img.height = (int)((float)oDimen.oHeight * multiplier);
}

void JTEimage::dilateWidth(float multiplier) {
	img.w_multiplier = multiplier;
	img.width = (int)((float)oDimen.oWidth * multiplier);
}

void JTEimage::dilateHeight(float multiplier) {
	img.h_multiplier = multiplier;
	img.height = (int)((float)oDimen.oHeight * multiplier);
}

void JTEimage::getDilation(float * dilationArray) {
	dilationArray[0] = img.w_multiplier;
	dilationArray[1] = img.h_multiplier;
}

float JTEimage::getWidthDilation() {
	return img.w_multiplier;
}

float JTEimage::getHeightDilation() {
	return img.h_multiplier;
}