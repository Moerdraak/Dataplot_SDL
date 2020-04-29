#pragma once
#include "JBW_EditBox.h"
class Jbw_Button : public Jbw_EditBox{
public:

	bool Inside = false;


/*-----------------------------------------------------------------------------------------
	 CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_Button() {}; // 
	Jbw_Button(SDL_Renderer* Rdr, int x, int y, int w, int h, std::string Caption, int Fsize = 12);
	~Jbw_Button();

/*-----------------------------------------------------------------------------------------
	FUNCTIONS
------------------------------------------------------------------------------------------*/
public:
	void InitBtn(J_Properties* Prop);
	void RdrBtn(void);
	void BtnEvent(SDL_Event* e);
	void SetmsOver(bool State);
};

