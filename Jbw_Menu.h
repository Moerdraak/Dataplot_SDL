#pragma once

#include "Jbw_Base.h"
#include "JBW_ListBox.h"
#include "Jbw_Frame.h"
#include "Jbw_Debug.h"

class Jbw_Menu; // Forward declaration

///////////////////////////////////////////////////////////////////////////////////////////
//                       CLASS Jbw_lbxMenuName
///////////////////////////////////////////////////////////////////////////////////////////
//class Jbw_lbxMenuName {
//public:
//	int Index = 0;
//	J_Type Type = J_ITEM;
//	Jbw_Button* Item = NULL;
//	Jbw_ListBox* lbxMenuName = NULL;
//};
//

///////////////////////////////////////////////////////////////////////////////////////////
//                       CLASS Jbw_Menu
///////////////////////////////////////////////////////////////////////////////////////////
class Jbw_Menu : public Jbw_Frame{
private:

public:
	int TotalWidth = 0;
	int TotH = 0;
	int MnuCnt = 0;
	bool ShowSub = false;
	bool MenuClick = false;

	Jbw_Button* btnMenuName = NULL;
	Jbw_ListBox* lbxMenuName = NULL;
	Jbw_Handles lstHandles;
//	Jbw_lbxMenuName* Items = NULL;
	SDL_Texture* AreaImage;

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
	Jbw_Menu(Jbw_Handles* h, std::string SubbtnMenuName, const SDL_Rect* ParentObj);
	~Jbw_Menu();

/*-----------------------------------------------------------------------------------------
		FUNCTION DECLARATIONS
------------------------------------------------------------------------------------------*/
private:
	void CreateTopLbx(Jbw_Menu* Menu);

public:
	void MenuAdd(std::string NewTopMenu, int w);
	Jbw_Return MenuAdd(std::string ParbtnMenuName, std::string SubbtnMenuName);
	void ItemAdd(std::string ParbtnMenuName, std::string MenuItem);
	void ItemAdd(std::string NewText, std::string SubbtnMenuName, std::string MenuItem);
	void MnuRdr();
	void lbxMenuNameRdr();
	const Jbw_Menu* MnuEvent(SDL_Event* Event);
};

