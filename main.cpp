#include <iostream>
#include <SDL.h>
#include <string>
#undef main

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

const int ScreenWidth = 640;
const int ScreenHeight = 480;

SDL_Window* window = nullptr;
SDL_Surface* screen = nullptr;
SDL_Surface* KeyPress[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* currentPress = nullptr;

bool init();
void close();
bool loadMedia();
SDL_Surface* loadSurface(const std::string& filename);

int main() {
	bool quit = false;
	SDL_Event e;
	if (init()) {
		//loadMedia();
		if (loadMedia()) {
			while (!quit) {
				//Handle event
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					else if(e.type == SDL_KEYDOWN){
						switch (e.key.keysym.sym)
						{
						case SDLK_UP: 
							currentPress = KeyPress[KEY_PRESS_SURFACE_UP];
							break;
						case SDLK_DOWN:
							currentPress = KeyPress[KEY_PRESS_SURFACE_DOWN];
							break;
						case SDLK_LEFT:
							currentPress = KeyPress[KEY_PRESS_SURFACE_LEFT];
							break;
						case SDLK_RIGHT:
							currentPress = KeyPress[KEY_PRESS_SURFACE_RIGHT];
							break;
						default:
							currentPress = KeyPress[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}
				SDL_BlitSurface(currentPress, nullptr, screen, nullptr);
				SDL_UpdateWindowSurface(window);
			}
		}
	}

	close();
}
bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Error init" << std::endl;
		success = false;
	}
	else {
		window = SDL_CreateWindow("Pham Thanh Vinh",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			std::cerr << "Error create window" << std::endl;
			success = false;
		}
		else {
			screen = SDL_GetWindowSurface(window);
		}
	}
	return success;
}
SDL_Surface* loadSurface(const std::string& filename) {
	SDL_Surface* load = SDL_LoadBMP(filename.c_str());
	if (load == nullptr) {
		std::cerr << "Error load surface" << std::endl;
		return nullptr;
	}
	return load;
}

bool loadMedia() {
	bool success = true;
	KeyPress[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
	if (KeyPress[KEY_PRESS_SURFACE_DEFAULT] == nullptr) {
		std::cerr << "Error load default press" << std::endl;
		success = false;
	}
	KeyPress[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
	if (KeyPress[KEY_PRESS_SURFACE_UP] == nullptr) {
		std::cerr << "Error load up press" << std::endl;
		success = false;
	}
	KeyPress[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	if (KeyPress[KEY_PRESS_SURFACE_DOWN] == nullptr) {
		std::cerr << "Error load down press" << std::endl;
		success = false;
	}
	KeyPress[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	if (KeyPress[KEY_PRESS_SURFACE_LEFT] == nullptr) {
		std::cerr << "Error load left press" << std::endl;
		success = false;
	}
	KeyPress[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
	if (KeyPress[KEY_PRESS_SURFACE_RIGHT] == nullptr) {
		std::cerr << "Error load right press" << std::endl;
		success = false;
	}
	return success;
}

void close() {
	for (int i = KEY_PRESS_SURFACE_DEFAULT; i < KEY_PRESS_SURFACE_TOTAL; i++) {
		SDL_FreeSurface(KeyPress[i]);
		KeyPress[i] = nullptr;
	}
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}