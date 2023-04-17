//Definition for texture Manager
// Loads in assets and converts to textures to render to screen
/*
#include "TextureManager.h"

//Function to load in a texture to render
SDL_Texture* TextureManager::LoadTexture(const char* texture) {

	SDL_Surface* tempSurface = IMG_Load(texture);	//Create Surface from input image
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);	//Create texture to render from surface 
	SDL_FreeSurface(tempSurface);	//Release Surface in memory 

	return tex;		//Return texture from loaded image

}

//Render a tile texture to the screen
void TextureManager::draw(SDL_Texture* texture, SDL_Rect start, SDL_Rect dest) {

	SDL_RenderCopy(Game::renderer, texture, &start, &dest);

}

*/