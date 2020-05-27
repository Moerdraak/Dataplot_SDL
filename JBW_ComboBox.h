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

	Jbw_EditBox *CbxEdit = NULL;
	Jbw_Button* CbxBtn = NULL; // dropdown button
	Jbw_ListBox* CbxList = NULL;
	Jbw_Handles* lsthandles = NULL;
	bool GridBtn = false; // When true it will hide the Combobox dropdown button until msOver.
	bool CbxListVis = false;
	int LbxCnt = 0;

/*-----------------------------------------------------------------------------------------
		CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_ComboBox() {};
	Jbw_ComboBox(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize,
		bool IsGridBtn = false);
	~Jbw_ComboBox();

/*-----------------------------------------------------------------------------------------
		FUNCTION DECLARATIONS
------------------------------------------------------------------------------------------*/
public:
	void InitCbx(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize,
		bool IsGridBtn = false);
	void AddRow(std::string NewText);
	void RdrCbx(void);
	J_Type CbxEvent(void);
	void CloseList(void);
};

