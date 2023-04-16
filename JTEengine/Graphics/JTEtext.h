#pragma once

#ifndef JTETEXT_H
#define JTETEXT_H

#include "../Window/JTEwindow.h"
#include "../Shaders/JTEshaders.h"
#include "../Standard/JTEstructs.h"

class JTEtext {
private:
    struct Character {
        glm::ivec2   size;     
        glm::ivec2   bearing;   
        glm::fvec4   texCoords;
        unsigned int advance;   
    };

    std::map<char, Character> characters;

    JTEstructs::Buffer_Obj buf;

    GLuint fontAtlas;

	JTEwindow* window;

public:
    ////////// Constructor //////////

    /*
    * @brief Initializes the characters of the font file selected.
    * 
    * This draws the first 1024 characters of the file. Uses a font glyph atlas
    * 
    * @param fontFile - TTF font file (only)
    * @param fontSize - Size of characters using pixels (don't really know how it works)
    * @param window - The window being written on
    */
	JTEtext(const char* fontFile, int fontSize, JTEwindow* window);

    ////////// Constructor //////////

    ////////// Member Functions //////////

    /*
    * @briefs Renders text
    * 
    * Text unlike other renders (basic shapes, images), render bottom left aligned instead of top left aligned.
    * 
    * @param text - Text to be rendered
    * @param x - Bottom-left x-value (first letter if multiline)
    * @param y - Bottom-left x-value (first letter if multiline)
    * @param color - Color of the text - Default: white (255, 255, 255, 255)
    * param multi - A bool value that toggles if it renders multiline (uses \n) - Default: false
    * param yChange - **Only for multiline** The vertical line spacing between each line - Default: 0
    */
    void write(std::string text, int x, int y, std::array<int, 4> color = {255, 255, 255, 255}, bool multi = false, int yChange = 0);

    ////////// Member Functions //////////
};

#endif // !JTETEXT_H
