//H_FILE for texture mananger 
//Declares class to load an image/texture from assets into game

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#pragma once
#include "Game.h"

class TextureManager {
public:

	//Function to load image to a texture to render in game
	static SDL_Texture* LoadTexture(const char* filename) {	//Declare LoadTexture function that returns a static ptr to a texture 
		SDL_Surface* tempSurface = IMG_Load(filename);	//Create Surface from input image
		SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);	//Create texture to render from surface 
		SDL_FreeSurface(tempSurface);	//Release Surface in memory 

		return tex;		//Return texture from loaded image
	}

	//Function to render loaded texture to the screen
	static void draw(SDL_Texture* texture, SDL_Rect start, SDL_Rect dest) { 	//Renders texture
		SDL_RenderCopy(Game::renderer, texture, &start, &dest);
	}

	static void draw(SDL_Texture* texture, SDL_Rect start, SDL_Rect dest, SDL_RendererFlip flip) {
		SDL_RenderCopyEx(Game::renderer, texture, &start, &dest, NULL, NULL, flip);
	}
};

#endif