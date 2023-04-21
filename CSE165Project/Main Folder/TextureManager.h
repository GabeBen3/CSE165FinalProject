//H_FILE for texture mananger 
//Declares class to load an image/texture from assets into game

#pragma once
#include "Game.h"

class TextureManager {
public:

	static SDL_Texture* LoadTexture(const char* filename);
};