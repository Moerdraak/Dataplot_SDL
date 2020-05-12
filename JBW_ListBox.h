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
	Jbw_TextBox* TxtList = NULL;
	Jbw_Frame* SliderBox = NULL;
	Jbw_Frame* Slider = NULL;
	Jbw_Button* SldrBtnUp = NULL;
	Jbw_Button* SldrBtnDwn = NULL;

	bool TxtRendered = false;
	int FontSize = 0;
	int Lines = 0;
	int FromLine = 0;
	int ToLine = 0;
	int Index = -1;


/*-----------------------------------------------------------------------------------------
		CONSTRUCTORS / DESTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_ListBox() {};
	Jbw_ListBox(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize);
	~Jbw_ListBox();

/*-----------------------------------------------------------------------------------------
		FUNCTION DECLARATIONS
------------------------------------------------------------------------------------------*/
public:
	void AddText(std::string NewTxt);
	void DelText(int Row);
	void Clear(void);
	void RdrLbx();
	void LbxEvent(Jbw_Handles *h);
};