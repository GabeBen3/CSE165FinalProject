#ifndef FOLLOWCOMPONENT_H
#define FOLLOWCOMPONENT_H
#pragma once

#include "AllComponents.h"
#include "Vector2D.h"

#include <list>

class FollowComponent : public Component {
public:
	FollowComponent(Entity& entity) {
		goalVect = entity.getComponent<TransformComponent>().position;
		
	}

	void update() override {

	}
private:
	Vector2D goalVect;
	Vector2D startVect;

	std::list<Vector2D> path;


};
#endif // !1
