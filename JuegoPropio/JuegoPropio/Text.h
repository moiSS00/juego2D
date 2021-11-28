#pragma once

#include "Game.h"

class Text
{
public:
	Text(string content, float x, float y, int r, int g, int b, Game* game);
	void draw();
	string content; // texto
	int x;
	int y;
	int r; 
	int g;
	int b; 
	int width;
	int height;
	Game* game; // referencia al juego
};


