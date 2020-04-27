#pragma once
#include "SDL.h"

class Jbw_Polygon
{
public:
	//short int Id = 0;
	//std::string Tag = "";

	SDL_Renderer* Prdr = NULL;
	SDL_Point* PolyLine = NULL;
	
	int NumPoints = 0;
	SDL_Color LineColor = { 0, 0, 0, 255 };

	Jbw_Polygon() {};
	Jbw_Polygon(SDL_Renderer* Rdr);
	~Jbw_Polygon()
	{
//		delete PolyLine;
	};

	void AddPoint(int x, int y);
	void PolyRdr(void);
};

