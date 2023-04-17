//Header File to create and render GameObjects

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#pragma once
#include "Game.h"

class GameObject {
public:

	GameObject(const char* textureSheet, int x, int y);

	// Each game object will have specific behaviors for updating and rendering
	//-> we don't need to keep updating in main game class
	void Update();
	void Render();

	~GameObject();

private:
	//Position of object
	int xpos;
	int ypos;

	//Texture of object -> from assets using textureManager
	SDL_Texture* objectTexture;
	
	//Rectangle for movement
	SDL_Rect startRect, destRect;

	//Renderer for object

};

#endif