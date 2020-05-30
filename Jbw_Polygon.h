#pragma once
#include "SDL.h"
#include "Jbw_Base.h"

class Jbw_Polygon : public Jbw_Base {
public:
	SDL_Point* PolyLine = NULL;
	
	int NumPoints = 0;
	SDL_Color LineColor = { 0, 0, 0, 255 };

	Jbw_Polygon() {};
	Jbw_Polygon(Jbw_Handles* handles);
	~Jbw_Polygon() {};

	void AddPoint(int x, int y);
	void RdrPoly(void);
};

