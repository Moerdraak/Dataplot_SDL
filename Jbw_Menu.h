#pragma once

#include "Jbw_Base.h"
#include "JBW_TextBox.h"
#include "JBW_ListBox.h"
#include "Jbw_Frame.h"

class Jbw_Menu : public Jbw_Frame{
public:
	int MnuX = 0;
	int MnuY = 0;
	int MnuW = 0;
	int MnuH = 18;
	int TotalWidth = 0;

	int MnuCnt = 0;
	Jbw_Button* MainMenu;
 
	struct Menus {
		Jbw_ListBox* MenuItems;
		//CallBack Pointers
	};

/*-----------------------------------------------------------------------------------------
		CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_Menu() {};
	Jbw_Menu(Jbw_Handles* h);
	~Jbw_Menu();

/*-----------------------------------------------------------------------------------------
		FUNCTION DECLARATIONS
------------------------------------------------------------------------------------------*/
public:
	void MenuAdd(std::string NewText, int w);
	void MenuAddSub(std::string NewText);
	void MnuRdr(Jbw_Handles* h);
	int MnuEvent(Jbw_Handles* handles);
};


