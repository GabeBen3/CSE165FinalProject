//Game function definitions
// Game functions to be used in the main loop

#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"

GameObject* player;
GameObject* enemy;

SDL_Renderer* Game::renderer = nullptr;

//Game constructor
Game::Game() {

}

//Game Destructor
Game::~Game() {

}


//Initialize the game
	//Create Game window
	//Create renderer
	//Load in assets
void Game::init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
	
	int fullscreenflag = 0;

	if (fullscreen == true) {
		fullscreenflag = SDL_WINDOW_FULLSCREEN;
	}
	//Test if SDL is initialized
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		std::cout << "SDL SubSystems Initialized Successfully" << std::endl;
		
		// Create window obj
		window = SDL_CreateWindow(title, x_pos, y_pos, width, height, fullscreenflag);

		if (window) {
			std::cout << "Window Successfully Created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Rendered successfully" << std::endl;

		}

		isrunning = true;
	}

	else {
		isrunning = false;
		std::cout << "Game has exited" << std::endl;
	}

	player = new GameObject("assets/gutsSprite.png", 0, 0);
	//enemy = new GameObject("assets/smokeMonster.png", renderer, 0, 0);

}

//Handle Events in game 
	//Quit Game
void Game::eventHandler() {

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			isrunning = false;
			break;
		default:
			break;

	}

}

//All game objs will have their own update funcs -> updating scores, movement, assets, etc... 
void Game::update() {
	player->Update();
}


// Main render function -> displays textures/game objects to the screen 
void Game::render() {

	SDL_RenderClear(renderer);
	//Add more elements to render
	
	// Render Player to the screen
								//Use entire img  //whole render frame
	player->Render();

	SDL_RenderPresent(renderer);	//Launch render

}


// Clear game from memory
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game has been cleaned and closed" << std::endl;

}


