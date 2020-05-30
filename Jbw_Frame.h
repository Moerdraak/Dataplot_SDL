#pragma once
#include "Jbw_Base.h"
#include "Jbw_Polygon.h"

class Jbw_Frame : public Jbw_Polygon {
public:
	bool Fill = false;

	SDL_Color FillColor = { 255, 255, 255, 255 };

/*-----------------------------------------------------------------------------------------
	CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_Frame(){};	
	Jbw_Frame(Jbw_Handles* handles, int x, int y, int w, int h, bool DoFill = false);
	~Jbw_Frame();

/*-----------------------------------------------------------------------------------------
	FUNCTIONS
------------------------------------------------------------------------------------------*/
public:
	void CreateFrame(void);
	void RdrFrame(void);
};

