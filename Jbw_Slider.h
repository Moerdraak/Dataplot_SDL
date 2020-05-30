#pragma once
#include "Jbw_Base.h"
#include "Jbw_Frame.h"
#include "Jbw_Button.h"

class Jbw_Slider : public Jbw_Frame
{
/*-----------------------------------------------------------------------------------------
	VARIABLES
------------------------------------------------------------------------------------------*/
public:
	Jbw_Frame* Slider = NULL;
	Jbw_Button* SldrBtnUp = NULL;
	Jbw_Button* SldrBtnDwn = NULL;

	bool BtnRender = true;
	int SldrPos = 0;
	int Steps = 0; // Number of Steps that it can move
	float StepSize = 0; // Step size each time it moves
	bool SliderActive = false;
	bool Vert = true;

	int msStartPos = 0;
	int SldrStartPos = 0;
/*-----------------------------------------------------------------------------------------
		CONSTRUCTORS / DESTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_Slider() {};
	Jbw_Slider(Jbw_Handles* handles, int x, int y, int w, int h, int Resolution = 10, 
		bool Vertical = true);
	~Jbw_Slider();

/*-----------------------------------------------------------------------------------------
		FUNCTION DECLARATIONS
------------------------------------------------------------------------------------------*/
public:

	void RdrSldr();
/*-----------------------------------------------------------------------------------------
		EVENT FUNCTIONS
------------------------------------------------------------------------------------------*/
public:
	void SldrEvent(SDL_Event* Event);
private:
	J_Type SliderEvent(SDL_Event* Event);
	J_Type BtnUpEvent(SDL_Event* Event);
	J_Type BtnDwnEvent(SDL_Event* Event);

};

