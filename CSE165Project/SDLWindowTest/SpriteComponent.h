//Header file for sprite components -> dictates sprite associated with a given entity

#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "AllComponents.h"
#include "SDL.h"
#include "TransformComponent.h"

#pragma once


class SpriteComponent : public Component {
public:
	SpriteComponent() = default;	//Default constructor->Empty sprite component

	SpriteComponent(const char* path) {
		texture = TextureManager::LoadTexture(path);	//input path to a sprite, loads texture from texture manager to variable
		start.x = 0;
		dest.y = 0;
	}

	SpriteComponent(const char* path, int x, int y) {			//Real Constructor

		texture = TextureManager::LoadTexture(path);	//input path to a sprite, loads texture from texture manager to variable
		start.x = x;
		dest.y = y;

	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	//Initialize sprite comp.
	void init() override {

		transform = &entity->getComponent<TransformComponent>();	//Get position component of existing entity
																// lets us manipulate positon of entity with position functions
		start.x = 0;
		start.y = 0;
		//start.w = transform->width;
		//start.h = transform->height;
		SDL_QueryTexture(texture, NULL, NULL, &start.w, &start.h);	//Get dimensions of loaded texture
		dest.w = start.w * transform->scale;
		dest.h = start.h * transform->scale;

		transform->width = start.w;
		transform->height = start.h;
	}

	//Update location of the sprite in relation to entity
	void update() override {
		dest.x = (int)transform->position.x;
		dest.y = (int)transform->position.y;

	}

	//render Sprite to screen
	void draw() override {
		
		TextureManager::draw(texture, start, dest, transform->flip);	//uses texture variable from construction to render

	}

private:

	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect start, dest;
};





#endif // !SPRITECOMPONENT_H


