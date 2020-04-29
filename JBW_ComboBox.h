#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Jbw_Base.h"
#include "JBW_EditBox.h"
#include "JBW_ListBox.h"
#include "Jbw_Frame.h"
#include <string>

class Jbw_ComboBox : public Jbw_Base {
public:
	Jbw_Button CbxEdit;
	Jbw_Button CbxBtn; // dropdown button
	Jbw_ListBox CbxList;
	bool CbxListVis = false;


/*-----------------------------------------------------------------------------------------
		CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_ComboBox() {};
	Jbw_ComboBox(SDL_Renderer* Rdr, int x, int y, int w, int h, int Fsize);
	~Jbw_ComboBox();

/*-----------------------------------------------------------------------------------------
		FUNCTION DECLARATIONS
------------------------------------------------------------------------------------------*/
public:
	void InitCbx(J_Properties* Prop);

	void RdrCbx(void);
	void CbxEvent(SDL_Event* e);
	void CbxCall(J_Type Type, std::string Input = "");
};

