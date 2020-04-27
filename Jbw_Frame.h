#pragma once
#include "SDL.h"
#include "Jbw_Polygon.h"

class Jbw_Frame : public Jbw_Polygon{
public:

	int FrameX = 0; // X origin of Frame
	int FrameY = 0; // X origin of Frame
	int FrameW = 0; // Width of Frame
	int FrameH = 0; // Height of Frame

	/*--------------------------------------------------------------------
		CONSTRUCTORS
	--------------------------------------------------------------------*/
	Jbw_Frame(){};	
	Jbw_Frame(SDL_Renderer* Rdr, int Xo, int Yo, int Width, int Height);
	~Jbw_Frame()
	{
	//	delete PolyLine;
	}

	/*--------------------------------------------------------------------
		FUNCTIONS
	--------------------------------------------------------------------*/
	void SetFrame();
	void CreateFrame(SDL_Renderer* Rdr, int Xo, int Yo, int Width, int Height);
	void FrameRdr(void);
};

