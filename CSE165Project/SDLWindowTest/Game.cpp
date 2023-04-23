//Game function definitions
// Game functions to be used in the main loop

#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "AllComponents.h"
#include "Vector2D.h"
#include "Collision.h"
#include <vector>

SDL_Renderer* Game::renderer = nullptr;	//Ptr to main renderer

Map* map;	//Instantiate map ptr

Manager entityManager;	//Instatiate Manager to manage entities in the game

auto& player(entityManager.addEntity());	//Create reference to new entity "player"
auto& sword(entityManager.addEntity());
auto& enemy1(entityManager.addEntity());
auto& enemy2(entityManager.addEntity());
auto& enemy3(entityManager.addEntity());
auto& enemy4(entityManager.addEntity());

//vector <Entity> enemies;
float enemyPos[2][4];

SDL_Event Game::event;		//Instantiate event detector



//Game constructor
Game::Game() {

}

//Game Destructor
Game::~Game() {

}

void Game::deathScreen(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
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
	player.addComponent<TransformComponent>(400, 320, 30, 30);	
	player.addComponent<SpriteComponent>("assets/gutsSprite.png");
	player.addComponent<Controller>();
	player.addComponent<ColliderComponent>("player");
	//player.addComponent<SwordComponent>(45, 26, 50, 50);

	sword.addComponent<TransformComponent>(490, 325, 5, 5);
	//sword.addComponent<SpriteComponent>("assets/swordCollider.png");
	sword.addComponent<ColliderComponent>("sword");
	sword.addComponent<Controller>();

	enemy1.addComponent<TransformComponent>(400, -100);
	enemy1.addComponent<SpriteComponent>("assets/smokeMonster.png");
	enemy1.addComponent<ColliderComponent>("enemy1");
	enemyPos[0][0] = 400;
	enemyPos[1][0] = -100;

	enemy2.addComponent<TransformComponent>(900, 320);
	enemy2.addComponent<SpriteComponent>("assets/smokeMonster.png");
	enemy2.addComponent<ColliderComponent>("enemy2");
	enemyPos[0][1] = 900;
	enemyPos[1][1] = 320;

	enemy3.addComponent<TransformComponent>(400, 740);
	enemy3.addComponent<SpriteComponent>("assets/smokeMonster.png");
	enemy3.addComponent<ColliderComponent>("enemy3");
	enemyPos[0][2] = 400;
	enemyPos[1][2] = 740;

	enemy4.addComponent<TransformComponent>(-100, 320);
	enemy4.addComponent<SpriteComponent>("assets/smokeMonster.png");
	enemy4.addComponent<ColliderComponent>("enemy4");
	enemyPos[0][3] = -100;
	enemyPos[1][3] = 320;





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

	bool gameOver = false;

	Vector2D playerPosition = player.getComponent<TransformComponent>().position;
	Vector2D swordPosition = sword.getComponent<TransformComponent>().position;


	entityManager.refresh();	//Check if entities need to be removed from world
	entityManager.update();	//Update all components of all entities

	if (
		enemy1.getComponent<TransformComponent>().stepTowards(playerPosition) ||
		enemy2.getComponent<TransformComponent>().stepTowards(playerPosition) ||
		enemy3.getComponent<TransformComponent>().stepTowards(playerPosition) ||
		enemy4.getComponent<TransformComponent>().stepTowards(playerPosition)  )
	{
		gameOver = true;
		//std::cout << "Killed" << std::endl;
	}

	if ((player.getComponent<Controller>().flippedLeft == true)) {
		sword.getComponent<TransformComponent>().position.x = playerPosition.x + 30;
	}
	else {
		sword.getComponent<TransformComponent>().position.x = playerPosition.x + 100;
	}

	if (Collision::AABB(sword.getComponent<ColliderComponent>().collider,
		enemy1.getComponent<ColliderComponent>().collider)) {

		//std::cout << "Collision Detected - Enemy 1" << std::endl;
		enemy1.getComponent<TransformComponent>().position.x = enemyPos[0][0];
		enemy1.getComponent<TransformComponent>().position.y = enemyPos[1][0];
	}

	if (Collision::AABB(sword.getComponent<ColliderComponent>().collider,
		enemy2.getComponent<ColliderComponent>().collider)) {

		//std::cout << "Collision Detected - Enemy 2" << std::endl;
		enemy2.getComponent<TransformComponent>().position.x = enemyPos[0][1];
		enemy2.getComponent<TransformComponent>().position.y = enemyPos[1][1];
	}

	if (Collision::AABB(sword.getComponent<ColliderComponent>().collider,
		enemy3.getComponent<ColliderComponent>().collider)) {

		//std::cout << "Collision Detected - Enemy 3" << std::endl;
		enemy3.getComponent<TransformComponent>().position.x = enemyPos[0][2];
		enemy3.getComponent<TransformComponent>().position.y = enemyPos[1][2];
	}

	if (Collision::AABB(sword.getComponent<ColliderComponent>().collider,
		enemy4.getComponent<ColliderComponent>().collider)) {

		//std::cout << "Collision Detected - Enemy 4" << std::endl;
		enemy4.getComponent<TransformComponent>().position.x = enemyPos[0][3];
		enemy4.getComponent<TransformComponent>().position.y = enemyPos[1][3];
	}

	if (gameOver) {
		std::cout << "Game Over - Restarting" << std::endl;
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		Game::init("Main Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
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


