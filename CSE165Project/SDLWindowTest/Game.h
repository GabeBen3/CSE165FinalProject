//Main game Header File
// Decalres class functions that will be used in main game loop 

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Game {
public:

	Game();
	~Game();

	void init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);

	void eventHandler();

	void update();
	void render();
	void clean();

	static SDL_Renderer* renderer;

	bool running() {
		return isrunning;
	};

private:
	int count = 0;
	bool isrunning;

	SDL_Window* window;

};


#endif // !GAME_H

