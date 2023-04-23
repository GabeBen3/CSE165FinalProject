#ifndef SWORDCOMPONENT_H
#define SWORDCOMPONENT_H
#pragma once

#include "SDL.h"
#include "AllComponents.h"

class SwordComponent : public Component {
public:

	TransformComponent* transform;
	SDL_Rect colliderStart, colliderDest;

	SwordComponent() = default;

	SwordComponent(int _x , int _y, int _width, int _height) {
		colliderStart.x = _x;
		colliderStart.y = _y;

		colliderDest.w = _width;
		colliderDest.h = _height;


	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		colliderDest.x = (int)transform->position.x;
		colliderDest.y = (int)transform->position.y;

	}
};

#endif 
