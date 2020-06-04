#pragma once
#include "Jbw_Base.h"
#include "Jbw_Frame.h"
#include "Jbw_Text.h"
#include "Jbw_Button.h"
#include "Jbw_Slider.h"

class Jbw_ListBox : public Jbw_Frame {
/*-----------------------------------------------------------------------------------------
		VARIABLES
------------------------------------------------------------------------------------------*/
public:
	Jbw_TextBox* TxtList = NULL;
	Jbw_Slider* Slider = NULL;

	bool TxtRendered = false;
	int Cnt = 0;
	int TxtBoxH = 0;
	int FontSize = 0;
	int Lines = 0;
	int FromLine = 0;
	int ToLine = 0;
	int Index = -1;
	
	int msPrevPosY = 0;
	bool SliderActive = false;
	int PointsPerline = 0;
/*-----------------------------------------------------------------------------------------
		CONSTRUCTORS / DESTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_ListBox() {};
	Jbw_ListBox(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize);
	~Jbw_ListBox();

	Jbw_ListBox(const Jbw_ListBox& cp);
	Jbw_ListBox& operator=(const Jbw_ListBox& copy);
/*-----------------------------------------------------------------------------------------
		FUNCTION DECLARATIONS
------------------------------------------------------------------------------------------*/
public:
	void AddText(std::string NewTxt);
	void ResizeListBox(int x, int y, int w, int h);
	void DelText(int Row);
	void Clear(void);
	void RdrLbx(void);
	void Close(void);
	void FitLines(bool ChangeCnt);

/*-----------------------------------------------------------------------------------------
		EVENT FUNCTIONS
------------------------------------------------------------------------------------------*/
private:
	J_Type ListEvent(SDL_Event* Event, int msX, int msY);
public:
	J_Type LbxEvent(SDL_Event* Event);

};