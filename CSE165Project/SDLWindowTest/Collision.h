//HeaderFile for collision detection

#ifndef COLLISION_H
#define COLLISION_H
#pragma once

#include <SDL.h>

//Class that contains collision checker
class Collision {
public:

	//function to return if collision between two rects occurs
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB) {

		if ((recA.x + recA.w >= recB.x) &&		//Check if rectangle dimensions intersect
			(recB.x + recB.w >= recA.x) &&
			(recA.y + recA.h >= recB.y) &&
			(recB.y + recB.w >= recA.y)
			) {
			return true;
			
		}

		return false;
	}
};

#endif // !COLLISION_H
