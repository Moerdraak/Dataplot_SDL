#pragma once
#include "Jbw_Base.h"
#include "Jbw_Polygon.h"

class Jbw_Frame : public Jbw_Polygon {
public:
	bool Fill = false;
	int FrameX = 0; // X origin of Frame
	int FrameY = 0; // X origin of Frame
	int FrameW = 0; // Width of Frame
	int FrameH = 0; // Height of Frame
	SDL_Color FillColor = { 255, 255, 255, 255 };

/*-----------------------------------------------------------------------------------------
	CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_Frame(){};	
	Jbw_Frame(SDL_Renderer* Rdr, int Xo, int Yo, int Width, int Height, bool DoFill = false);
	~Jbw_Frame()
	{

	}

/*-----------------------------------------------------------------------------------------
	FUNCTIONS
------------------------------------------------------------------------------------------*/
public:
	void CreatePts();
	void InitFrame(J_Properties *Prop);
	void RdrFrame(void);
};

