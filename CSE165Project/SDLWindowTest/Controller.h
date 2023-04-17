//Header file to get user input from keyboard
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "AllComponents.h"
#include "TransformComponent.h"
#include "Game.h"

#pragma once

class Controller : public Component {
public:
	TransformComponent* transform;	//Insantiate ptr to transform object->(x, y)

	bool flippedLeft = false;	

	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		transform->velocity.x = 0;
		transform->velocity.y = 0;

		if (keystates[SDL_SCANCODE_UP]) {
			transform->velocity.y = -1;
		}
		else if (keystates[SDL_SCANCODE_LEFT]) {
			transform->velocity.x = -1;
			transform->flip = SDL_FLIP_HORIZONTAL;
			flippedLeft = true;
		}
		else if (keystates[SDL_SCANCODE_DOWN]) {
			transform->velocity.y = 1;
		}
		else if (keystates[SDL_SCANCODE_RIGHT]) {
			transform->velocity.x = 1;
			if (flippedLeft) {
				transform->flip = SDL_FLIP_NONE;
				flippedLeft = false;
			}
		}

	}
};

#endif // !CONTROLLER_H


