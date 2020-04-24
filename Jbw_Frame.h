#pragma once
#include "SDL.h"
#include "Jbw_Polygon.h"

class Jbw_Frame : public Jbw_Polygon{
public:

	Jbw_Frame(){};	
	Jbw_Frame(SDL_Renderer* Rdr, int Xo, int Yo, int w, int h);
	~Jbw_Frame()
	{
		delete Points;
	}

	void CreateFrame(SDL_Renderer* Rdr, int Xo, int Yo, int w, int h);
	void FrameRdr(void);
};

