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

	void init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);	//Initialize game window

	void eventHandler();	//Handle events

	void update();		//Update main window and entities
	void render();		//Render objs to the screen
	void clean();

	static SDL_Renderer* renderer;	//Declare static renderer all other files can use

	static SDL_Event event;	//Static event handler

	bool running() {
		return isrunning;	//check if game is running 
	};

private:
	int count = 0;
	bool isrunning;

	SDL_Window* window;		//Window var

};


#endif // !GAME_H

