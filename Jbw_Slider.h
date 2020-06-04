#pragma once
#include "Jbw_Base.h"
#include "Jbw_Frame.h"
#include "Jbw_Button.h"

class Jbw_Slider : public Jbw_Frame
{
/*-----------------------------------------------------------------------------------------
	VARIABLES
------------------------------------------------------------------------------------------*/
private:
	int Steps = 0; // Number of Steps that it can move
	float StepSize = 0; // Step size each time it moves
	int SldrPos = 0;
public:
	Jbw_Frame* Slider = NULL;
	Jbw_Button* SldrBtnUp = NULL;
	Jbw_Button* SldrBtnDwn = NULL;

	bool BtnRender = true;
	bool SliderActive = false;
	bool Vert = true;
	int StepPos = 0;
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

	Jbw_Slider(const Jbw_Slider& cp);
	Jbw_Slider& operator=(const Jbw_Slider& cp);

/*-----------------------------------------------------------------------------------------
		FUNCTION DECLARATIONS
------------------------------------------------------------------------------------------*/
public:

	void RdrSldr();
/*-----------------------------------------------------------------------------------------
		EVENT FUNCTIONS
------------------------------------------------------------------------------------------*/
public:
	J_Type SldrEvent(SDL_Event* Event);
	void SetResolution(int NumSteps);
private:
	J_Type SliderBoxEvent(SDL_Event* Event);
	J_Type SliderEvent(SDL_Event* Event);
	J_Type BtnUpEvent(SDL_Event* Event);
	J_Type BtnDwnEvent(SDL_Event* Event);

};

