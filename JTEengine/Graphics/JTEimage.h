#pragma once

#ifndef JTEIMAGE_H
#define JTEIMAGE_H

#include "../Standard/JTEstructs.h"
#include "../Shaders/JTEshaders.h"
#include "../Window/JTEwindow.h"

class JTEimage {
private:
	JTEstructs::Buffer_Obj buf;
	JTEstructs::Image img;
	JTEstructs::OriginalDimensions oDimen;

	GLuint textureID;
	
	std::shared_ptr<unsigned char[]> imageData{};

	JTEshaders shaders;
	JTEwindow* window;

	float WIDTH, HEIGHT;
	int originalWidth, originalHeight;
	int type;

public:
	////////// Constructors //////////

	/*
	* @brief Initializes the x & y positions and file to be rendered
	* 
	* @param x - Top-left x coordinate
	* @param y - Top-left y coordinate
	* @param filename - Image file to be rendered
	* @param window - The window to be rendered on
	* @param shaders - The shader program being used
	*/
	JTEimage(int x, int y, const char* filename, JTEwindow* window, JTEshaders shaders);

	/*
	* @brief Initializes the x & y positions, width, height, and file to be rendered
	* 
	* @param x - Top-left x coordinate
	* @param y - Top-left y coordinate
	* @param width - The width being set (other than default one)
	* @param height - The height being set (other than default one)
	* @param filename - Image file to be rendered
	* @param window - The window to be rendered on
	* @param shaders - The shader program being used
	*/
	JTEimage(int x, int y, int width, int height, const char* filename, JTEwindow* window, JTEshaders shaders);

	////////// Constructors //////////

	////////// Member Functions //////////

	/*
	* @brief Renders the image
	*/
	void render();

	/*
	* @brief Cleans and releases the resources being used by the render and image
	*/
	void erase();


	/*
	* @brief Sets a new x coordinate (top-left)
	* 
	* @param x - New top-left x coordinate
	*/
	void setX(int x);

	/*
	* @brief Sets a new y coordinate (top-left)
	* 
	* @param y - New top-left y coordinate
	*/
	void setY(int y);
	
	/*
	* @brief Sets the new width of the image
	*
	* @param width - New width
	*/
	void setWidth(int width);

	/*
	* @brief Sets the new height of the image
	*
	* @param height - New height
	*/
	void setLength(int height);


	/*
	* @brief Gets the top-left x coordinate
	* 
	* @return x - Top-left x coordinate 
	*/
	int getX();
	
	/*
	* @brief Gets the top-left y coordinate
	* 
	* @return y - Top-left y coordinate
	*/
	int getY();
	
	/*
	* @brief Gets the width of the image
	* 
	* @return width - Width of the image
	*/
	int getWidth();
	
	/* 
	* @brief Gets the height of the image
	* 
	* @return height - Height of the image
	*/
	int getHeight();


	/*
	* @brief Dilates the image by the multiplier
	* 
	* @param multiplier - The number to multiply both the width and height by
	*/
	void dilate(float multiplier);
	
	/*
	* @brief Dilates the image width by the multiplier
	*
	* @param multiplier - The number to multiply the width by
	*/
	void dilateWidth(float multiplier);
	
	/*
	* @brief Dilates the image height by the multiplier
	*
	* @param multiplier - The number to multiply the height by
	*/
	void dilateHeight(float multiplier);


	/*
	* @brief Gets the dilation factor
	*
	* @param dilationArray - An empty float array (has to have atleast two elements spaces)
	*/
	void getDilation(float* dilationArray);
	
	/*
	* @brief Gets the width dilation factor
	*
	* @return widthDilation - The dilation multiplier of the width
	*/
	float getWidthDilation();
	
	/*
	* @brief Gets the height dilation factor
	*
	* @return heightDilation - The dilation multiplier of the height
	*/
	float getHeightDilation();

	////////// Member Functions //////////
};

#endif // !JTEIMAGE_H

