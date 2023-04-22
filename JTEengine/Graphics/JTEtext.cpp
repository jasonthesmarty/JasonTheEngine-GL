#include "pch.h"
#include "JTEtext.h"

#include "../Standard/JTEstandard.h"

#include "../Dependencies/ft2build.h"
#include FT_FREETYPE_H

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <../Dependencies/STB/stb_image_write.h>

JTEstandard jstdf;

JTEtext::JTEtext(const char* fontFile, int fontSize, JTEwindow* window, int style) {
	this->window = window;
	buf.VAO = 0, buf.VBO = 0, buf.CBO = 0;

	FT_Library ft;
	FT_Init_FreeType(&ft);

	FT_Face face;
	FT_New_Face(ft, fontFile, 0, &face);

	FT_Set_Pixel_Sizes(face, 0, fontSize);

	if (style == 1) {
		FT_Matrix matrix{};
		matrix.xx = 0x10000L;
		matrix.xy = 0x06000L;
		matrix.yx = 0L;
		matrix.yy = 0x10000L;
		FT_Set_Transform(face, &matrix, NULL);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	int letterCount = 0;
	int atlasWidth = 0, atlasHeight = 0;
	int wAtlas = 0, hAtlas = 0;
	for (int l = 32; l < 2048; l++) {
		letterCount++;
		FT_Load_Char(face, l, FT_LOAD_RENDER);
		atlasWidth += (int)face->glyph->bitmap.width;
		atlasHeight = max(atlasHeight, (int)face->glyph->bitmap.rows);
		if (letterCount == 100) {
			wAtlas = max(wAtlas, atlasWidth);
			hAtlas += atlasHeight;
			letterCount = 0;
			atlasWidth = 0;
			atlasHeight = 0;
		}
	}

	glGenTextures(1, &fontAtlas);
	glBindTexture(GL_TEXTURE_2D, fontAtlas);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wAtlas, hAtlas, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glClearTexImage(fontAtlas, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

	int xOFF = 0;
	int yOFF = 0;
	int characterCount = 0;
	for (int r = 32; r < 2048; r++) {
		FT_Load_Char(face, r, FT_LOAD_RENDER);
		characterCount++;

		float xTexCoords    = static_cast<float>(xOFF) / static_cast<float>(wAtlas);
		float yTexCoords    = static_cast<float>(yOFF)    / static_cast<float>(hAtlas);
		float textureWidth  = static_cast<float>(face->glyph->bitmap.width) / static_cast<float>(wAtlas);
		float textureHeight = static_cast<float>(face->glyph->bitmap.rows)  / static_cast<float>(hAtlas);

		Character character = {
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			glm::fvec4(xTexCoords, yTexCoords, textureWidth, textureHeight),
			static_cast<unsigned int>(face->glyph->advance.x)
		};
		characters.insert(std::pair<char, Character>(r, character));

		glTexSubImage2D(GL_TEXTURE_2D, 0, xOFF, yOFF, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		unsigned char* RGBAfied = new unsigned char[face->glyph->bitmap.width * face->glyph->bitmap.rows * 4];
		for (int i = 0; i < face->glyph->bitmap.width * face->glyph->bitmap.rows; ++i) {
			RGBAfied[i * 4] = face->glyph->bitmap.buffer[i];
			RGBAfied[i * 4 + 1] = face->glyph->bitmap.buffer[i];
			RGBAfied[i * 4 + 2] = face->glyph->bitmap.buffer[i];
			RGBAfied[i * 4 + 3] = face->glyph->bitmap.buffer[i];
		}
		glTexSubImage2D(GL_TEXTURE_2D, 0, xOFF, yOFF, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RGBA, GL_UNSIGNED_BYTE, RGBAfied);

		delete[] RGBAfied;

		xOFF += face->glyph->bitmap.width;
		if (characterCount == 100) {
			yOFF += fontSize;
			xOFF = 0;
			characterCount = 0;
		}
	}

	/*
	unsigned char* pixels = new unsigned char[wAtlas * hAtlas * 4];
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	stbi_write_bmp("text.bmp", wAtlas, hAtlas, 4, pixels);
	*/

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// jstdf.println("Font Initialized");
}

void JTEtext::write(std::string text, int x, int y, std::array<int, 4> color, bool multi, int yChange) {
	int originalX = x;
	
	float scale = 1;

	float widthHalf = (float)this->window->getWidth() / 2;
	float heightHalf = (float)this->window->getHeight() / 2;

	float red = (float)color[0] / 255;
	float green = (float)color[1] / 255;
	float blue = (float)color[2] / 255;
	float alpha = (float)color[3] / 255;

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

	glBindVertexArray(buf.VAO);

	if (multi) {
		std::vector<float> vertices;
		std::vector<float> colors;

		for (int i = 0; i < text.size(); i++) {
			Character charc = characters[text[i]];

			if (text[i] == '\n') {
				y += yChange;
				x = originalX;
			}
			else {
				float X = (1 - (x + charc.bearing.x * scale) / widthHalf) * -1;
				float Y = (1 - (y + (charc.size.y - charc.bearing.y) * scale) / heightHalf);

				float WIDTH = ((charc.size.x * scale) / widthHalf);
				float HEIGHT = ((charc.size.y * scale) / heightHalf);

				float glyphVertices[] = {
					X, Y + HEIGHT,           charc.texCoords.x, charc.texCoords.y,
					X, Y,                    charc.texCoords.x, charc.texCoords.y + charc.texCoords.w,
					X + WIDTH, Y,            charc.texCoords.x + charc.texCoords.z, charc.texCoords.y + charc.texCoords.w,

					X, Y + HEIGHT,           charc.texCoords.x, charc.texCoords.y,
					X + WIDTH, Y,            charc.texCoords.x + charc.texCoords.z, charc.texCoords.y + charc.texCoords.w,
					X + WIDTH, Y + HEIGHT,   charc.texCoords.x + charc.texCoords.z, charc.texCoords.y
				};

				vertices.insert(vertices.end(), std::begin(glyphVertices), std::end(glyphVertices));

				float glyphColors[] = {
					red, green, blue, alpha,
					red, green, blue, alpha,
					red, green, blue, alpha,
					red, green, blue, alpha,
					red, green, blue, alpha,
					red, green, blue, alpha
				};

				colors.insert(colors.end(), std::begin(glyphColors), std::end(glyphColors));

				x += (charc.advance >> 6) * scale;
			}
		}

		// VBO
		glBindBuffer(GL_ARRAY_BUFFER, buf.VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

		// CBO
		glBindBuffer(GL_ARRAY_BUFFER, buf.CBO);
		glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

		// Transparency
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		// Drawing
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fontAtlas);

		glDrawArrays(GL_TRIANGLES, 0, text.size() * 6);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDeleteVertexArrays(1, &buf.VAO);
		glDeleteBuffers(1, &buf.VBO);
		glDeleteBuffers(1, &buf.CBO);
	}
	else {
		std::vector<float> vertices;
		std::vector<float> colors;

		for (int i = 0; i < text.size(); i++) {
			Character charc = characters[text[i]];

			float X = (1 - (x + charc.bearing.x * scale) / widthHalf) * -1;
			float Y = (1 - (y + (charc.size.y - charc.bearing.y) * scale) / heightHalf);

			float WIDTH = ((charc.size.x * scale) / widthHalf);
			float HEIGHT = ((charc.size.y * scale) / heightHalf);

			float glyphVertices[] = {
				X, Y + HEIGHT,           charc.texCoords.x, charc.texCoords.y,
				X, Y,                    charc.texCoords.x, charc.texCoords.y + charc.texCoords.w,
				X + WIDTH, Y,            charc.texCoords.x + charc.texCoords.z, charc.texCoords.y + charc.texCoords.w,

				X, Y + HEIGHT,           charc.texCoords.x, charc.texCoords.y,
				X + WIDTH, Y,            charc.texCoords.x + charc.texCoords.z, charc.texCoords.y + charc.texCoords.w,
				X + WIDTH, Y + HEIGHT,   charc.texCoords.x + charc.texCoords.z, charc.texCoords.y
			};
			vertices.insert(vertices.end(), std::begin(glyphVertices), std::end(glyphVertices));

			float glyphColors[] = {
				red, green, blue, alpha,
				red, green, blue, alpha,
				red, green, blue, alpha,
				red, green, blue, alpha,
				red, green, blue, alpha,
				red, green, blue, alpha
			};

			colors.insert(colors.end(), std::begin(glyphColors), std::end(glyphColors));

			x += (charc.advance >> 6) * scale;
		}

		// VBO
		glBindBuffer(GL_ARRAY_BUFFER, buf.VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

		// CBO
		glBindBuffer(GL_ARRAY_BUFFER, buf.CBO);
		glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

		// Transparency
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		// Drawing
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fontAtlas);

		glDrawArrays(GL_TRIANGLES, 0, text.size() * 6);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDeleteVertexArrays(1, &buf.VAO);
		glDeleteBuffers(1, &buf.VBO);
		glDeleteBuffers(1, &buf.CBO);
	}
}