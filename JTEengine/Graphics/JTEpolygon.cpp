#include "pch.h"

#include "JTEpolygon.h"

// Variables

JTEstandard jstdp = JTEstandard();

// Definitions

namespace JTEpolygon {
	
	// SQUARE //

	JTEsquare::JTEsquare(int x, int y, int sideLength, JTEwindow* window, JTEshaders shaders) {
		p_sq.x = x;
		p_sq.y = y;
		p_sq.sideLength = sideLength;
		
		this->stable_sLength = sideLength;

		this->window = window;
		this->shaders = shaders;
		this->type = 0;

		// VAO
		glGenVertexArrays(1, &buf.VAO);
		glBindVertexArray(buf.VAO);

		// VBO
		glGenBuffers(1, &buf.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, buf.VBO);
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);

		// CBO
		glGenBuffers(1, &buf.CBO);
		glBindBuffer(GL_ARRAY_BUFFER, buf.CBO);
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);

		// Single White Pixel 
		glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		/// To ward off C26495 

		colorv.r, colorv.g, colorv.b, colorv.a = 0;
		colorv2.r, colorv2.g, colorv2.b, colorv2.a = 0;
		colorv3.r, colorv3.g, colorv3.b, colorv3.a = 0;
		colorv4.r, colorv4.g, colorv4.b, colorv4.a = 0;
	}

	JTEsquare::JTEsquare(int x, int y, int sideLength, int red, int green, int blue, int alpha, JTEwindow* window, JTEshaders shaders) {
		p_sq.x = x;
		p_sq.y = y;
		p_sq.sideLength = sideLength;
		
		this->stable_sLength = sideLength;

		colorv.r = (float)red / 255;
		colorv.g = (float)green / 255;
		colorv.b = (float)blue / 255;
		colorv.a = (float)alpha / 255;
		
		this->window = window;
		this->shaders = shaders;
		this->type = 1;

		// VAO
		glGenVertexArrays(1, &buf.VAO);
		glBindVertexArray(buf.VAO);

		// VBO
		glGenBuffers(1, &buf.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, buf.VBO);
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);

		// CBO
		glGenBuffers(1, &buf.CBO);
		glBindBuffer(GL_ARRAY_BUFFER, buf.CBO);
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);

		// Single White Pixel 
		glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		/// To ward off C26495

		colorv2.r, colorv2.g, colorv2.b, colorv2.a = 0;
		colorv3.r, colorv3.g, colorv3.b, colorv3.a = 0;
		colorv4.r, colorv4.g, colorv4.b, colorv4.a = 0;
	}

	JTEsquare::JTEsquare(int x, int y, int sideLength, int color[4], JTEwindow* window, JTEshaders shaders) {
		p_sq.x = x;
		p_sq.y = y;
		p_sq.sideLength = sideLength;

		this->stable_sLength = sideLength;

		colorv.r = (float)color[0] / 255;
		colorv.g = (float)color[1] / 255;
		colorv.b = (float)color[2] / 255;
		colorv.a = (float)color[3] / 255;

		this->window = window;
		this->shaders = shaders;
		this->type = 2;

		// VAO
		glGenVertexArrays(1, &buf.VAO);
		glBindVertexArray(buf.VAO);

		// VBO
		glGenBuffers(1, &buf.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, buf.VBO);
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);

		// CBO
		glGenBuffers(1, &buf.CBO);
		glBindBuffer(GL_ARRAY_BUFFER, buf.CBO);
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);

		// Single White Pixel 
		glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		/// To ward off C26495

		colorv2.r, colorv2.g, colorv2.b, colorv2.a = 0;
		colorv3.r, colorv3.g, colorv3.b, colorv3.a = 0;
		colorv4.r, colorv4.g, colorv4.b, colorv4.a = 0;
	}

	JTEsquare::JTEsquare(int x, int y, int sideLength, int color_tl[4], int color_tr[4], int color_bl[4], int color_br[4], JTEwindow* window, JTEshaders shaders) {
		p_sq.x = x;
		p_sq.y = y;
		p_sq.sideLength = sideLength;

		this->stable_sLength = sideLength;

		colorv.r = (float)color_tl[0] / 255;
		colorv.g = (float)color_tl[1] / 255;
		colorv.b = (float)color_tl[2] / 255;
		colorv.a = (float)color_tl[3] / 255;

		colorv2.r = (float)color_tr[0] / 255;
		colorv2.g = (float)color_tr[1] / 255;
		colorv2.b = (float)color_tr[2] / 255;
		colorv2.a = (float)color_tr[3] / 255;

		colorv3.r = (float)color_bl[0] / 255;
		colorv3.g = (float)color_bl[1] / 255;
		colorv3.b = (float)color_bl[2] / 255;
		colorv3.a = (float)color_bl[3] / 255;

		colorv4.r = (float)color_br[0] / 255;
		colorv4.g = (float)color_br[1] / 255;
		colorv4.b = (float)color_br[2] / 255;
		colorv4.a = (float)color_br[3] / 255;

		this->window = window;
		this->shaders = shaders;
		this->type = 3;

		// VAO
		glGenVertexArrays(1, &buf.VAO);
		glBindVertexArray(buf.VAO);

		// VBO
		glGenBuffers(1, &buf.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, buf.VBO);
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);

		// CBO
		glGenBuffers(1, &buf.CBO);
		glBindBuffer(GL_ARRAY_BUFFER, buf.CBO);
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);

		// Single White Pixel 
		glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void JTEsquare::render() {
		float widthHalf = (float)this->window->getWidth() / 2;
		float heightHalf = (float)this->window->getHeight() / 2;

		float X = (1 - (p_sq.x / widthHalf)) * -1;
		float Y = (1 - (p_sq.y / heightHalf));

		float WIDTH = (p_sq.sideLength / widthHalf);
		float HEIGHT = (p_sq.sideLength / heightHalf);

		float vertices[6][4] = {
			// Vertex Coords        // Texture Coords
			{X, Y - HEIGHT,            0.0f, 1.0f},
			{X + WIDTH, Y,             1.0f, 0.0f},
			{X + WIDTH, Y - HEIGHT,    1.0f, 1.0f},
			{X, Y - HEIGHT,            0.0f, 1.0f},
			{X + WIDTH, Y,             1.0f, 0.0f},
			{X, Y,                     0.0f, 0.0f}
		};

		std::array<float, 24> colorArraySTD{};
		float color[24]{};

		if (this->type == 0) {
			float colorType0[] = {
				0.5f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 0.5f, 1.0f,
				1.0f, 0.5f, 1.0f, 1.0f,
				1.0f, 1.0f, 0.5f, 1.0f,
				1.0f, 0.5f, 1.0f, 1.0f,
				1.0f, 1.0f, 0.5f, 1.0f
			};
			std::copy(std::begin(colorType0), std::end(colorType0), std::begin(colorArraySTD));
		}
		else if (this->type == 1 || this->type == 2) {
			float colorType12[] = {
				colorv.r, colorv.g, colorv.b, colorv.a,
				colorv.r, colorv.g, colorv.b, colorv.a,
				colorv.r, colorv.g, colorv.b, colorv.a,
				colorv.r, colorv.g, colorv.b, colorv.a,
				colorv.r, colorv.g, colorv.b, colorv.a,
				colorv.r, colorv.g, colorv.b, colorv.a
			};
			std::copy(std::begin(colorType12), std::end(colorType12), std::begin(colorArraySTD));
		}
		else if (this->type == 3) {
			float colorType3[] = {
				colorv4.r, colorv4.g, colorv4.b, colorv4.a,
				colorv2.r, colorv2.g, colorv2.b, colorv2.a,
				colorv3.r, colorv3.g, colorv3.b, colorv3.a,
				colorv3.r, colorv3.g, colorv3.b, colorv3.a,
				colorv2.r, colorv2.g, colorv2.b, colorv2.a,
				colorv.r, colorv.g, colorv.b, colorv.a
			};
			std::copy(std::begin(colorType3), std::end(colorType3), std::begin(colorArraySTD));
		}

		std::copy(std::begin(colorArraySTD), std::end(colorArraySTD), std::begin(color));

		// VBO
		glBindBuffer(GL_ARRAY_BUFFER, buf.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

		// CBO
		glBindBuffer(GL_ARRAY_BUFFER, buf.CBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

		// Single White Pixel
		glBindTexture(GL_TEXTURE_2D, textureID);
		GLubyte buffer[] = { 255, 255, 255, 255 };
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

		int textureUniformId = glGetUniformLocation(shaders.getShader(), "texture0");
		glUniform1i(textureUniformId, 0);

		// Drawing
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void JTEsquare::erase() {
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDeleteVertexArrays(1, &buf.VAO);
		glDeleteBuffers(1, &buf.VBO);
		glDeleteBuffers(1, &buf.CBO);
		glDeleteTextures(1, &textureID);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	void JTEsquare::setX(int x) {
		p_sq.x = x;
	}

	void JTEsquare::setY(int y) {
		p_sq.y = y;
	}

	void JTEsquare::setSideLength(int length) {
		p_sq.sideLength = length;
		this->stable_sLength = length;
	}

	int JTEsquare::getX() {
		return p_sq.x;
	}

	int JTEsquare::getY() {
		return p_sq.y;
	}
	
	int JTEsquare::getSideLength() {
		return p_sq.sideLength;
	}

	void JTEsquare::dilate(float multiplier) {
		this->multiplier = multiplier;
		p_sq.sideLength = (int)((float)this->stable_sLength * multiplier);
	}

	float JTEsquare::getDilation() {
		return this->multiplier;
	}

	// SQUARE //

}