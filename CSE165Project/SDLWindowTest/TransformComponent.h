//Header file for position component -> dictates position and movement of entities on the screen
#ifndef TransformComponent_H
#define TransformComponent_H

#include "AllComponents.h"
#include "Vector2D.h"

//Component to hand position of an entity in the world
class TransformComponent : public Component{
public:
	Vector2D position;

	Vector2D velocity;

	SDL_RendererFlip flip = SDL_FLIP_NONE;	//Variable to determine how to flip the sprite based on button input 

	int height = 0;
	int width = 0;
	int scale = 2;
	
	int speed = 3;

	// Constructors 
	TransformComponent() {
		position.zero(); //Zero out the vector
	}

	TransformComponent(float _x, float _y) {
		position.x = _x;
		position.y = _y;
	}

	TransformComponent(float _x, float _y, int _width, int _height) {
		position.x = _x;
		position.y = _y;

		width = _width;
		height = _height;
	}

	TransformComponent(float _x, float _y, int _width, int _height, int _scale) {
		position.x = _x;
		position.y = _y;

		width = _width;
		height = _height;
		scale = _scale;
	}


	bool stepTowards(Vector2D goalPosition) {
		bool goalReached = false;

		speed = 1;
		goalX = goalPosition.x;
		goalY = goalPosition.y;
		if (position.x < goalX) {
			velocity.x = 1;
		}
		else if (position.x > goalX) {
			velocity.x = -1;
		}
		else {
			velocity.x = 0;
		}
		if (position.y < goalY) {
			velocity.y = 1;
		}
		else if (position.y > goalY) {
			velocity.y = -1;
		}
		else {
			velocity.y = 0;
		}

		if ((position.x == goalX) && (position.y == goalY) ||
			(position.x == goalX + 80) && (position.y == goalY)){
			goalReached = true;
		}

		return goalReached;
		
	}


	//Update position of transformation component relative to entity 
	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

	}

	//Initialize velocity of t.c.
	void init() override {
		velocity.zero(); //Zero out the velocity
	}



private: 
	int xPos, yPos;
	int goalX, startX, goalY, StartY;

};

#endif