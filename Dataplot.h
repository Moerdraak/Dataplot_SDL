#pragma once
#include "Jbw_Base.h"
#include <stdio.h>
//#include "SDL_image.h"
//#include "SDL_ttf.h"
//#include <string>
#include <sstream>
#include "Jbw_Polygon.h"
#include "Jbw_FrameWork.h"
#include "Jbw_Circle.h"


/****************************************************************************************/
/*******************************  DO NOT EDIT  ******************************************/
/****************************************************************************************/


/**************************************************************************************
	CLASS: DataPlot    (Jbw_GUI = JaBberWock Graphical User Interface)
	=============
	This is where all the stuff goes for the Specific GUI that you.
	This is where you BUILD your GUI.
**************************************************************************************/
class Dataplot : public Jbw_FrameWork {
private:

public:
	
	SDL_Rect LogoArea;
	SDL_Surface* wSurf = NULL; // The surface contained by the window
	SDL_Texture* LogoImage = NULL; //Current displayed texture

	/*******************  CONSTRUCTORS  *******************/
	Dataplot() {};
	~Dataplot();

	/*******************  FUNCTIONS  *******************/
	Jbw_Handles* JbwCreateLayout(void);
	void UserRender(void);
	void TheLoop(void);

	/*******************************************************
	               Gui Specific Objects
	*******************************************************/
	Jbw_EditBox* Ding;
	Jbw_ListBox* MsgMsg;
	Jbw_Grid* Tst;
	Jbw_Button* btnDataDir;
	
	/*******************************************************
			   Gui Objects Callbacks
	*******************************************************/
	void btnClear_Click(Jbw_Handles* h);
	void btnDataDir_Click(Jbw_Handles* h);
};