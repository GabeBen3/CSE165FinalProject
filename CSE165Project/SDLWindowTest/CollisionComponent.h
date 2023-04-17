//Header file for collision component-> will handle ingame collisions between entities
// AABB collision
#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include <string>
#include "AllComponents.h"
#include "SDL.h"

class ColliderComponent : public Component {
public:

	SDL_Rect collider;	// Collision rectangle
	std::string tag;	// tag to identify what entity is
	TransformComponent* transform;

	ColliderComponent(std::string _tag) {
		tag = _tag;

	}

	void init() override {

		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();
	}

	//Set collision rectangle vars 
	void update() override {
		collider.x = transform->position.x;
		collider.y = transform->position.y;
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}
};

#endif // !COLLISIONCOMPONENT_H
