#pragma once

#include <stdio.h>
#include <sstream>
#include <Windows.h>
#include "Jbw_Base.h"
#include "Jbw_FrameWork.h"
#include "Jbw_EditBox.h"
#include "Jbw_Polygon.h"
#include "Jbw_Circle.h"
#include "Jbw_Menu.h"


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
	Jbw_Menu* Menu;

	Jbw_EditBox* edDataDir;
	Jbw_ListBox* MsgMsg;

//	Jbw_ComboBox* cbxNew;
//	Jbw_TextBox* txtNew;
	Jbw_Button* btnDataDir;
	Jbw_Button* btnPlot;
	Jbw_Button* btnUp;
	Jbw_Button* btnDown;

	
	/*******************************************************
			   Gui Objects Callbacks
	*******************************************************/
	void btnClear_Click(Jbw_Handles* h);
	void btnDataDir_Click(Jbw_Handles* h);
	void btnPlot_Click(Jbw_Handles* h);
	void btnPlotAll_Click(Jbw_Handles* h);
	void btnAdd_Click(Jbw_Handles* h);
	void btnUp_Click(Jbw_Handles* h);
	void btnDown_Click(Jbw_Handles* h);


	// RECTANGLE OBJECTS
	SDL_Rect vp_Graph;
	SDL_Rect vp_Main; // For clearing the Thing  // TMP !!!!!!
	SDL_Rect GraphArea;
	SDL_Rect LegendArea;


	// TEXT OBJECTS

	Jbw_TextBox* txtTestTitle;
	Jbw_TextBox* txtLegend;
	Jbw_TextBox* ObjXlabel;
	Jbw_TextBox* ObjYlabel;
	Jbw_TextBox* txtRandom;



	const int GRAPH_W = 600;
	const int GRAPH_H = 500;

	void GraphRender(void);

	

};
HANDLE SetupSerialPort(std::string ComPort);


