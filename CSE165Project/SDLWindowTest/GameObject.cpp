#include "GameObject.h"
#include "TextureManager.h"

//Create an object 
//Assign object a renderer and a texture
GameObject::GameObject(const char* textureSheet, int x, int y) {
	objectTexture = TextureManager::LoadTexture("assets/gutsSprite.png");

	xpos = x;
	ypos = y;

}

//Update function -> defines behaviors
void GameObject::Update() {
	xpos++;
	ypos++;

	startRect.h = 51;
	startRect.w = 72;
	startRect.x = 0;
	startRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = startRect.w * 2;
	destRect.h = startRect.h * 2;

	std::cout << "GameOBJ updates" << std::endl;
}

//Draws texture to the screen
void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objectTexture, &startRect, &destRect);
}