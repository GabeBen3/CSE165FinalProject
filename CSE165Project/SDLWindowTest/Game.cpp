//Game function definitions
// Game functions to be used in the main loop

#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "AllComponents.h"
#include "Vector2D.h"
#include "Collision.h"

SDL_Renderer* Game::renderer = nullptr;	//Ptr to main renderer

Map* map;	//Instantiate map ptr

Manager entityManager;	//Instatiate Manager to manage entities in the game

auto& player(entityManager.addEntity());	//Create reference to new entity "player"
auto& enemy(entityManager.addEntity());
auto& wall(entityManager.addEntity());

SDL_Event Game::event;		//Instantiate event detector

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

	//Add components to entities	
	player.addComponent<TransformComponent>();	
	player.addComponent<SpriteComponent>("assets/gutsSprite.png");
	player.addComponent<Controller>();
	player.addComponent<ColliderComponent>("player");

	enemy.addComponent<TransformComponent>(300, 300);
	enemy.addComponent<SpriteComponent>("assets/smokeMonster.png", 200, 200);
	enemy.addComponent<ColliderComponent>("enemy");





	map = new Map();	//Create new map

}

//Handle Events in game 
	//Quit Game
void Game::eventHandler() {

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

	Vector2D playerPosition = player.getComponent<TransformComponent>().position;

	entityManager.refresh();	//Check if entities need to be removed from world
	entityManager.update();	//Update all components of all entities

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		enemy.getComponent<ColliderComponent>().collider)) {

		std::cout << "Collision Detected" << std::endl;
		player.getComponent<TransformComponent>().position = playerPosition;
	}
}


// Main render function -> displays textures/game objects to the screen 
void Game::render() {

	SDL_RenderClear(renderer);
	//Add more elements to render

	map->drawMap();

	//Render all existing entities to the screen->Compo
	entityManager.draw();
	
	// Render Player to the screen
								//Use entire img  //whole render frame

	SDL_RenderPresent(renderer);	//Launch render

}


// Clear game from memory
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game has been cleaned and closed" << std::endl;

}


