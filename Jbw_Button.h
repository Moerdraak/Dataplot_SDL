#pragma once
#include "Jbw_Base.h"
#include "JBW_EditBox.h"
class Jbw_Button : public Jbw_EditBox{
public:
	SDL_Color BtnColor = J_C_BtnGrey;
	SDL_Color BtnBorderColor = J_C_Frame;
	SDL_Color HoverColor = J_C_msOver;
	SDL_Color HoverBorderColor = J_BLACK;
	SDL_Color ClickColor = J_C_BtnDwn;

/*-----------------------------------------------------------------------------------------
	 CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_Button() {}; // 
	Jbw_Button(Jbw_Handles* handles, int x, int y, int w, int h, std::string Caption,
		int Fsize = 12);
	~Jbw_Button();

/*-----------------------------------------------------------------------------------------
	FUNCTIONS
------------------------------------------------------------------------------------------*/
public:
//	void InitBtn(J_Properties* Prop);

	void RdrBtn(void);
	J_Type BtnEvent(SDL_Event* Event);
	

};

