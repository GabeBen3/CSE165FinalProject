//Main game loop
// Utilizes functions in main game header

#include <SDL.h>
#include "Game.h"
#include <iostream>

Game* game = nullptr;	//Create ptr to game object

int main(int argc, char* argv[]) {
	/*
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Main Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);
	*/
	
	// funciton to cap FPS to 60
	const int FPS = 60;	//FPS limit
	const int frameDelay = 1000 / FPS;
	unsigned int frameStart;
	int frameTime;


	game = new Game();	//set game ptr to an instance of a game object
	
	// Launch window 
	game->init("Main Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);


	while (game->running()) {
		frameStart = SDL_GetTicks();	// Get Ticks before game operations in loop

		//Handle User Input
		//Update obj, pos, scores, etc...
		//render changes to display

		

		game->eventHandler();
		game->update();		//Update all entities, map, components, etc...
		game->render();		//Render map, entities, components, main window, etc...

		frameTime = SDL_GetTicks() - frameStart;	// Get tick difference after game loop 

		if (frameDelay > frameTime) {			//Delay frame refresh rate to maintain 60 fps
			SDL_Delay(frameDelay - frameTime);
		}

	}



	//Clear game from memory
	game->clean();

	return 0;
}