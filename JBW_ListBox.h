#pragma once
#include "Jbw_Base.h"
#include "Jbw_Frame.h"
#include "Jbw_Text.h"
#include "Jbw_Button.h"


class Jbw_ListBox : public Jbw_Frame {
/*-----------------------------------------------------------------------------------------
		VARIABLES
------------------------------------------------------------------------------------------*/
public:
	int Cnt = 0;
	Jbw_Text* TextList = NULL;
	Jbw_Frame* SliderBox = NULL;
	Jbw_Frame* Slider = NULL;
	Jbw_Button* SldrBtnUp = NULL;
	Jbw_Button* SldrBtnDwn = NULL;


	int FontSize = 0;
/*-----------------------------------------------------------------------------------------
		CONSTRUCTORS / DESTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_ListBox() {};
	Jbw_ListBox(J_Properties* Prop);
	Jbw_ListBox(SDL_Renderer* Rdr, int x, int y, int w, int h, int Fsize);
	~Jbw_ListBox();

/*-----------------------------------------------------------------------------------------
		FUNCTION DECLARATIONS
------------------------------------------------------------------------------------------*/
public:
	void InitLbx(J_Properties* Prop);
	void AddText(std::string NewTxt);
	void DelText(int Row);
	void Clear(void);
	void RdrLbx(void);
	void LbxEvent(SDL_Event* e);
};