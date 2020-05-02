#pragma once

#include "Jbw_Base.h"
#include "JBW_EditBox.h"
#include "JBW_ListBox.h"
#include "Jbw_Frame.h"

class Jbw_ComboBox : public Jbw_Base {
public:
	Jbw_Button CbxEdit;
	Jbw_Button CbxBtn; // dropdown button
	Jbw_ListBox CbxList;
	bool CbxListVis = false;
	SDL_Window* ListWindow = NULL;
	SDL_Renderer* ListRdr = NULL;
/*-----------------------------------------------------------------------------------------
		CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_ComboBox() {};
	Jbw_ComboBox( SDL_Renderer* Rdr, int x, int y, int w, int h, int Fsize);
	~Jbw_ComboBox();

/*-----------------------------------------------------------------------------------------
		FUNCTION DECLARATIONS
------------------------------------------------------------------------------------------*/
public:
	void InitCbx(J_Properties* Prop);
	void RdrCbx(Jbw_Handles h);
	void CbxEvent(Jbw_Handles h, SDL_Event* e);
	void CbxCall(Jbw_Handles h, J_Type Type, std::string Input = "");
};

