#pragma once
#include "JBW_EditBox.h"
//#include "Jbw_Debug.h"
//#include "Jbw_ListBox.h"

class Jbw_Button : public Jbw_Base{
public:
	SDL_Color BtnColor = J_C_BtnGrey;
	SDL_Color BtnBorderColor = J_C_Frame;
	SDL_Color HoverColor = J_C_msOver;
	SDL_Color HoverBorderColor = J_BLACK;
	SDL_Color ClickColor = J_C_BtnDwn;

	int TxtSize = 12;
	J_Type TxtAlign = J_CENTRE;

	std::string Caption = "";
	Jbw_TextBox* Tbx = NULL;

/*-----------------------------------------------------------------------------------------
	 CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_Button() {}; // 
	Jbw_Button(Jbw_Handles* handles, int x, int y, int w, int h, std::string Text,
		int Fsize = 12);
	~Jbw_Button();

	Jbw_Button(const Jbw_Button& cp, std::string NewCaption);
	Jbw_Button& operator=(const Jbw_Button& cp);

/*-----------------------------------------------------------------------------------------
	FUNCTIONS
------------------------------------------------------------------------------------------*/
public:
	void InitBtn(Jbw_Handles* handles, int x, int y, int w, int h, std::string Text,
		int Fsize = 12);
	void CreateButton(void);
	void RdrBtn();
	J_Event BtnEvent(SDL_Event* Event);
	
};

