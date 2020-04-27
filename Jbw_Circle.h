#pragma once
#include "SDL.h"
class Jbw_Circle
{
public:
	SDL_Renderer* Crdr = NULL;
	int CirX = 0;
	int CirY = 0;
	int CirRad = 0;
	SDL_Color Border = { 0, 0, 0, 255 };
	SDL_Color Fill = { 0, 0, 0, 255 };

	Jbw_Circle(SDL_Renderer* Rdr, int x, int y, int Radius);

	void CircleOpen();
	void CircleFill();
};

