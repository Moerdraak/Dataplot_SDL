#pragma once

#include "Jbw_Base.h"
#include "JBW_EditBox.h"
#include "JBW_ListBox.h"
#include "Jbw_Frame.h"

class Jbw_ComboBox : public Jbw_Base {
public:

	int ComboX = 0;
	int ComboY = 0;
	int ComboW = 0;
	int ComboH = 0;


	Jbw_Button CbxEdit;
	Jbw_Button CbxBtn; // dropdown button
	Jbw_ListBox CbxList;
	bool GridBtn = false;
	bool CbxListVis = false;
	SDL_Window* ListWindow = NULL;
	SDL_Renderer* ListRdr = NULL;
	int LbxCnt = 0;
	std::string* LbxTxt = NULL;
/*-----------------------------------------------------------------------------------------
		CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_ComboBox() {};
	Jbw_ComboBox( SDL_Renderer* Rdr, int x, int y, int w, int h, int Fsize, 
		bool IsGridBtn = false);
	~Jbw_ComboBox();

/*-----------------------------------------------------------------------------------------
		FUNCTION DECLARATIONS
------------------------------------------------------------------------------------------*/
public:
	void InitCbx(J_Properties* Prop);
	void AddRow(Jbw_Handles* h, std::string NewText);
	void RdrCbx(Jbw_Handles* h);
	void CbxEvent(Jbw_Handles* h);

};

