#pragma once
#include "SDL.h"
#include "Jbw_Base.h"
#include "Jbw_Debug.h"

class Jbw_Circle : public Jbw_Base {
public:
	int CirX = 0;
	int CirY = 0;
	int CirRad = 0;
	SDL_Color Border = { 0, 0, 0, 255 };
	SDL_Color Fill = { 0, 0, 0, 255 };

	Jbw_Circle(Jbw_Handles* handles, int x, int y, int Radius);

	void CircleOpen();
	void CircleFill();
};

