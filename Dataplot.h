#pragma once
#include "Jbw_Base.h"
#include <stdio.h>
#include <sstream>
#include "DpGraph.h"

#include "Jbw_Polygon.h"
#include "Jbw_FrameWork.h"
#include "Jbw_Circle.h"
#include "Jbw_Menu.h"
#include "Jbw_Slider.h"
#include "Jbw_Debug.h"
#include "Jbw_Base.h"
#include <array>

/****************************************************************************************/
/*******************************  DO NOT EDIT  ******************************************/
/****************************************************************************************/

class Dp_Handles {

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
	
	/*  DataPlot Heading */
	Jbw_Text* txtDataPlotName;
	Jbw_Text* txtVersion;
	
	/*  Project Detail */
	Jbw_Text* txtConfig;
	Jbw_Text* txtProject;
	
	/*  Bitplot/Wordplot Heading */
	Jbw_Text* txtBpWp;

	/*  Data Directory */
	Jbw_Text* txtDataDir;
	Jbw_EditBox* edDataDir;
	Jbw_Button* btnDataDir;

	/*  File ID: */
	Jbw_Text* txtFileId;
	Jbw_EditBox* edFileId;

	/*  DataSet Description */
	Jbw_Text* txtDataSet;
	Jbw_EditBox* edDataSet;
	
	/*  Figure Combobox  */
	Jbw_Text* txtFigure;
	Jbw_ComboBox* cbxFigure;

	/*  Graph Title  */
	Jbw_Text* txtTitle;
	Jbw_EditBox* edTitle;

	/*  Y Axes label */
	Jbw_Text* txtYaxLabel;
	Jbw_EditBox* edYaxLabel;

	/*  X Axes label */
	Jbw_Text* txtXaxLabel;
	Jbw_EditBox* edXaxLabel;

	/*   Time On/Off Button */
	Jbw_Text* txtOnOffBtn;

	/*   Messages   */
	Jbw_Text* txtMessages;
	Jbw_ListBox* lbxMessage;
	Jbw_Button* btnClear;

	/* Plot Buttons  */
	Jbw_Button* btnPlot;
	Jbw_Button* btnPlotAll;
	Jbw_Button* btnUp;
	Jbw_Button* btnDown;
	Jbw_Button* btnAdd;

	/*   Figure Type Button */
	Jbw_Text* txtFigBtn;

	
	Jbw_ListBox* MsgMsg;
	Jbw_Grid* grdFigure;

	/********** PLAY AREA ********/
	Jbw_Slider* Slider;
	Jbw_ComboBox* cbxPlayCopy;
	Jbw_Polygon* Lyn;
	
	/*******************************************************
			   Gui Menu Callbacks
	*******************************************************/
	void LoadConfigFile(std::string FileName);

	/*******************************************************
			   Gui Objects Callbacks
	*******************************************************/
	void btnClear_Click(void);
	void btnDataDir_Click(Jbw_Handles* h);
	void btnPlot_Click(Jbw_Handles* h);
	void btnPlotAll_Click(Jbw_Handles* h);
	void btnAdd_Click(Jbw_Handles* h);
	void btnUp_Click(Jbw_Handles* h);
	void btnDown_Click(Jbw_Handles* h);

	void grdFigure_OnChange(Jbw_Grid::grdEvent GridEvent);
	void GridCellColorChange(int Col, int Row, int Index);

	void lbxMessage_CallBack(void);
};