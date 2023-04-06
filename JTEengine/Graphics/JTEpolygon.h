#pragma once

#ifndef JTEPOLYGON_H
#define JTEPOLYGON_H

#include "../Standard/JTEstructs.h"
#include "../Window/JTEwindow.h"

#include "pch.h"

namespace JTEpolygon {
	
	class JTEsquare {
	private:
		JTEstructs::Polygon_Square p_sq;
		JTEstructs::Buffer_Obj buf;
		JTEstructs::RGBA_val colorv;

		JTEwindow* window;
		int type;

	public:
		////////// Constructors //////////

		/*
		* @brief Initializes the placement and dimensions
		* 
		* @param x - x coordinate of the top-left vertex
		* @param y - y coordinate of the top-left vertex
		* @param sideLength - length of the sides
		* @param window - a reference to the window being drawn on
		*/
		JTEsquare(int x, int y, int sideLength, JTEwindow* window);
		
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
		*/
		JTEsquare(int x, int y, int sideLength, int red, int green, int blue, int alpha, JTEwindow* window);
		
		/*
		* @brief Initializes the placement, color (int array), and dimensions
		*
		* @param x - x coordinate of the top-left vertex
		* @param y - y coordinate of the top-left vertex
		* @param sideLength - length of the sides
		* @param colors - Sets the red, green, blue, and alpha values (Pixel Values, 0 - 255)
		* @param window - a reference to the window being drawn on
		*/
		JTEsquare(int x, int y, int sideLength, int color[4], JTEwindow* window);

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

		////////// Member Functions //////////
	};
}

#endif // !JTEPOLYGON_H

