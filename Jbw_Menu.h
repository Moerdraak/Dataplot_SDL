#pragma once

#include "Jbw_Base.h"
#include "JBW_ListBox.h"
#include "Jbw_Frame.h"

class Jbw_Menu; // Forward declaration

///////////////////////////////////////////////////////////////////////////////////////////
//                       CLASS Jbw_SubMenu
///////////////////////////////////////////////////////////////////////////////////////////
class Jbw_SubMenu {
public:
	int Index = 0;
	J_Type Type = J_ITEM;
	Jbw_Button* Item = NULL;
	Jbw_ListBox* SubMenu = NULL;
};


///////////////////////////////////////////////////////////////////////////////////////////
//                       CLASS Jbw_Menu
///////////////////////////////////////////////////////////////////////////////////////////
class Jbw_Menu : public Jbw_Frame{
private:

public:
	int TotalWidth = 0;
	int MnuCnt = 0;

	std::string MenuName = "";
	Jbw_SubMenu* Menu = NULL;

	// Linked List pointers
	Jbw_Menu* Next = NULL;
	Jbw_Menu* Prev = NULL;
	Jbw_Menu* Parent = NULL;

/*-----------------------------------------------------------------------------------------
		CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_Menu() {};
	Jbw_Menu(Jbw_Handles* h);
	Jbw_Menu(Jbw_Handles* h, std::string SubMenuName, const SDL_Rect* ParentObj);
	~Jbw_Menu();

/*-----------------------------------------------------------------------------------------
		FUNCTION DECLARATIONS
------------------------------------------------------------------------------------------*/
private:


public:
	void MenuAdd(std::string MenuName, int w);
	void MenuAdd(std::string MenuName, std::string SubMenuName);
	void ItemAdd(std::string MenuName, std::string MenuItem);
	void ItemAdd(std::string NewText, std::string SubMenuName, std::string MenuItem);
	void MnuRdr(Jbw_Handles* h);
	int MnuEvent(Jbw_Handles* handles);
};

