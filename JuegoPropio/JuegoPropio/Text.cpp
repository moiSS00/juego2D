#include "Text.h"

Text::Text(string content, float x, float y, int r, int g, int b, Game* game) {
	this->content = content;
	this->x = x;
	this->y = y;
	this->r = r; 
	this->g = g; 
	this->b = b; 
	this->game = game;
}

void Text::draw() {
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255; //transparente

	SDL_Surface* surface = TTF_RenderText_Blended(game->font, content.c_str(), color);
	// c_str() transforma el string a cost *char;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);

	SDL_Rect rect; // Base de coordenadas esquina superior izquierda
	rect.x = x - surface->w / 2;
	rect.y = y - surface->h / 2;
	rect.w = surface->w / 2;
	rect.h = surface->h / 2;

	SDL_FreeSurface(surface);
	SDL_RenderCopy(game->renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

