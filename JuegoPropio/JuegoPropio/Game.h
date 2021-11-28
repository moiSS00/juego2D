#pragma once

// Todas las librerias de SDL y otras utilidades
#include <iostream>
#include <string>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map> 

// Valores generales
#define WIDTH 480
#define HEIGHT 320

#include "Layer.h"
class Layer;

class Game
{
public:
	Game();
	void loop();
	void scale();

	SDL_Window* window; // ventana
	SDL_Renderer* renderer; // renderizador
	bool loopActive; // Juego activo
	TTF_Font* font;
	Layer* layer;
	Layer* menuLayer;
	Layer* gameLayer;
	SDL_Texture* getTexture(string filename);
	map<string, SDL_Texture*> mapTextures; // map - cache

	int input;
	int const inputKeyboard = 1;
	int const inputMouse = 2;

	bool scaledToMax = false;
	float scaleLower = 1;

	int const stateMoving = 1;
	int const stateAttacking = 2;
	int const stateDying = 3;
	int const stateDead = 4;

	int currentLevel = 0;
	int finalLevel = 1;
};



