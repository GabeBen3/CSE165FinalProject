//Definition for texture Manager
// Loads in assets and converts to textures to render to screen

#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {

	SDL_Surface* tempSurface = IMG_Load(texture);	//Create Surface from input image
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);	//Create texture to render from surface 
	SDL_FreeSurface(tempSurface);	//Release Surface in memory 

	return tex;		//Return texture from loaded image

}