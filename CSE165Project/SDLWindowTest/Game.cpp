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
auto& enemy1(entityManager.addEntity());
auto& enemy2(entityManager.addEntity());
auto& enemy3(entityManager.addEntity());
auto& enemy4(entityManager.addEntity());
auto& wall(entityManager.addEntity());

SDL_Event Game::event;		//Instantiate event detector

float enemyPos[2][4];

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

	enemy1.addComponent<TransformComponent>(900, 300);
	enemy1.addComponent<SpriteComponent>("assets/smokeMonster.png", 200, 200);
	enemy1.addComponent<ColliderComponent>("enemy1");
	enemyPos[0][0] = 900;
	enemyPos[1][0] = 300;

	enemy2.addComponent<TransformComponent>(400, 700);
	enemy2.addComponent<SpriteComponent>("assets/smokeMonster.png", 200, 200);
	enemy2.addComponent<ColliderComponent>("enemy2");
	enemyPos[0][1] = 400;
	enemyPos[1][1] = 700;

	enemy3.addComponent<TransformComponent>(900, 700);
	enemy3.addComponent<SpriteComponent>("assets/smokeMonster.png", 200, 200);
	enemy3.addComponent<ColliderComponent>("enemy3");
	enemyPos[0][2] = 900;
	enemyPos[1][2] = 700;

	enemy4.addComponent<TransformComponent>(100, 700);
	enemy4.addComponent<SpriteComponent>("assets/smokeMonster.png", 200, 200);
	enemy4.addComponent<ColliderComponent>("enemy4");
	enemyPos[0][3] = 100;
	enemyPos[1][3] = 700;



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

	/*Vector2D playerPosition = player.getComponent<TransformComponent>().position;
	Vector2D enemyPosition = enemy.getComponent<TransformComponent>().position;
	float dx = playerPosition.x - enemyPosition.x;
	float dy = playerPosition.y - enemyPosition.y;
	float distance = sqrt(dx * dx + dy * dy);
	if (distance > 0) {
		enemy.getComponent<TransformComponent>().velocity.x = dx / distance * 3;
		enemy.getComponent<TransformComponent>().velocity.y = dy / distance * 3;
	}*/

	enemy1.getComponent<TransformComponent>().stepTowards(playerPosition);
	enemy2.getComponent<TransformComponent>().stepTowards(playerPosition);
	enemy3.getComponent<TransformComponent>().stepTowards(playerPosition);
	enemy4.getComponent<TransformComponent>().stepTowards(playerPosition);


	entityManager.refresh();	//Check if entities need to be removed from world
	entityManager.update();	//Update all components of all entities


	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		enemy1.getComponent<ColliderComponent>().collider)) {

		std::cout << "Collision Detected - Enemy 1" << std::endl;
		enemy1.getComponent<TransformComponent>().position.x = enemyPos[0][0];
		enemy1.getComponent<TransformComponent>().position.y = enemyPos[1][0];
	}

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		enemy2.getComponent<ColliderComponent>().collider)) {

		std::cout << "Collision Detected - Enemy 2" << std::endl;
		enemy2.getComponent<TransformComponent>().position.x = enemyPos[0][1];
		enemy2.getComponent<TransformComponent>().position.y = enemyPos[1][1];
	}

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		enemy3.getComponent<ColliderComponent>().collider)) {

		std::cout << "Collision Detected - Enemy 3" << std::endl;
		enemy3.getComponent<TransformComponent>().position.x = enemyPos[0][2];
		enemy3.getComponent<TransformComponent>().position.y = enemyPos[1][2];
	}

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		enemy4.getComponent<ColliderComponent>().collider)) {

		std::cout << "Collision Detected - Enemy 4" << std::endl;
		enemy4.getComponent<TransformComponent>().position.x = enemyPos[0][3];
		enemy4.getComponent<TransformComponent>().position.y = enemyPos[1][3];
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


