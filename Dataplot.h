#pragma once
#include "SDL.h"
#include <stdio.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>
#include "Jbw_Polygon.h"
#include "Jbw_FrameWork.h"
#include "Jbw_Circle.h"


/****************************************************************************************/
/*******************************  DO NOT EDIT  ******************************************/
/****************************************************************************************/
struct Jbw_Handles {
	SDL_Window* JbwGui;
	SDL_Renderer* J_Rdr = NULL;
	Jbw_Text* TxtPtr;
	Jbw_EditBox* EbxPtr = NULL;
	Jbw_ListBox* LbxPtr = NULL;
	Jbw_ComboBox* CbxPtr = NULL;
	Jbw_Button* BtnPtr = NULL;
	Jbw_Grid* GrdPtr = NULL;

	short int TxtCnt = 0;
	short int EbxCnt = 0;
	short int LbxCnt = 0;
	short int CbxCnt = 0;
	short int BtnCnt = 0;
	short int GrdCnt = 0;
};

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

	const int U_SCREEN_W = 1070;
	const int U_SCREEN_H = 600;

	/*******************  CONSTRUCTORS  *******************/
	Dataplot() {};
	~Dataplot();

	/*******************  FUNCTIONS  *******************/
	Jbw_Handles JbwCreateLayout(void);
	void Close(); // Frees media and shuts down SDL
	void UserRender(void);
};