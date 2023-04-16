#pragma once

#ifndef JTEPOLYGON_H
#define JTEPOLYGON_H

#include "../Standard/JTEstructs.h"
#include "../Window/JTEwindow.h"
#include "../Standard/JTEstandard.h"
#include "../Shaders/JTEshaders.h"

#include "pch.h"

namespace JTEpolygon {
	
	class JTEsquare {
	private:
		JTEstructs::Polygon_Square p_sq;
		JTEstructs::Buffer_Obj buf;
		JTEstructs::RGBA_val colorv;

		JTEstructs::RGBA_val colorv2;
		JTEstructs::RGBA_val colorv3;
		JTEstructs::RGBA_val colorv4;

		GLuint textureID;

		JTEwindow* window;
		JTEshaders shaders;
		int type;
		int stable_sLength;
		float multiplier;
	public:
		////////// Constructors //////////

		/*
		* @brief Initializes the placement and dimensions
		* 
		* @param x - x coordinate of the top-left vertex
		* @param y - y coordinate of the top-left vertex
		* @param sideLength - length of the sides
		* @param window - a reference to the window being drawn on
		* @param shaders - The shader program being used
		*/
		JTEsquare(int x, int y, int sideLength, JTEwindow* window, JTEshaders shaders);
		
		/*
		* @brief Initializes the placement, color (4 ints), and dimensions
		*
		* @param x - x coordinate of the top-left vertex
		* @param y - y coordinate of the top-left vertex
		* @param sideLength - length of the sides
		* @param red - Sets the red value (Pixel Values, 0 - 255)
		* @param green - Sets the green value (Pixel Values, 0 - 255)
		* @param blue - Sets the blue value (Pixel Values, 0 - 255)
		* @param alpha - Sets the alpha value (Pixel Values, 0 - 255)
		* @param window - a reference to the window being drawn on
		* @param shaders - The shader program being used
		*/
		JTEsquare(int x, int y, int sideLength, int red, int green, int blue, int alpha, JTEwindow* window, JTEshaders shaders);
		
		/*
		* @brief Initializes the placement, color (int array), and dimensions
		*
		* @param x - x coordinate of the top-left vertex
		* @param y - y coordinate of the top-left vertex
		* @param sideLength - length of the sides
		* @param colors - Sets the red, green, blue, and alpha values (Pixel Values, 0 - 255)
		* @param window - a reference to the window being drawn on
		* @param shaders - The shader program being used
		*/
		JTEsquare(int x, int y, int sideLength, int color[4], JTEwindow* window, JTEshaders shaders);

		/*
		* @brief Initializes the placement, color (int array), and dimensions
		*
		* @param x - x coordinate of the top-left vertex
		* @param y - y coordinate of the top-left vertex
		* @param sideLength - length of the sides
		* @param colors_tl - Sets the red, green, blue, and alpha values of the top-left vertex (Pixel Values, 0 - 255)
		* @param colors_tr - Sets the red, green, blue, and alpha values of the top-right vertex (Pixel Values, 0 - 255)
		* @param colors_bl - Sets the red, green, blue, and alpha values of the bottom-left vertex (Pixel Values, 0 - 255)
		* @param colors_tr - Sets the red, green, blue, and alpha values of the bottom-right vertex (Pixel Values, 0 - 255)
		* @param window - a reference to the window being drawn on
		* @param shaders - The shader program being used
		*/
		JTEsquare(int x, int y, int sideLength, int color_tl[4], int color_tr[4], int color_bl[4], int color_br[4], JTEwindow* window, JTEshaders shaders);

		////////// Constructors //////////

		////////// Member Functions //////////

		/*
		* @brief Renders the square
		*/
		void render();
		/*
		* @brief Cleans up resources used by drawing
		*/
		void erase();


		/*
		* @brief Sets the x value of the top-left corner of the square
		*/
		void setX(int x);

		/*
		* @brief Sets the y value of the top-left corner of the square
		*/
		void setY(int y);

		/*
		* @brief Sets the side length of the square
		*/
		void setSideLength(int length);


		/*
		* @brief Gets the x coordinate of the square
		* 
		* @return x - The x coordinate
		*/
		int getX();

		/*
		* @brief Gets the y coordinate of the square
		* 
		* @return y - The y coordinate
		*/
		int getY();

		/*
		* @brief Gets the side length of the square
		*/
		int getSideLength();


		/*
		* @brief Sets the dilation multiplier of the square
		*/
		void dilate(float multiplier);

		/*
		* @brief Gets the dilation multiplier of the square
		* 
		* @return multiplier - The dilation multiplier
		*/
		float getDilation();

		////////// Member Functions //////////
	};
}

#endif // !JTEPOLYGON_H


