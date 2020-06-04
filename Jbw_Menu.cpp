#include "Jbw_Menu.h"

///////////////////////////////////////////////////////////////////////////////////////////
//                       CLASS Jbw_Menu
///////////////////////////////////////////////////////////////////////////////////////////
/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR: Jbw_Menu
------------------------------------------------------------------------------------------*/
Jbw_Menu::Jbw_Menu(Jbw_Handles* handles)
{
	Jhandle = handles;
	// Create Frame at the top of the screen
	Obj.x = 0;
	Obj.y = 0; // Hide Top line of Frame
	Obj.h = 18;
	Obj.w = Jhandle->GuiArea.w;
	LineColor = J_WHITE;
	FillColor = J_WHITE;
	Fill = true;
	CreateFrame(); // Create the frame points from above info
}

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR: Jbw_Menu
------------------------------------------------------------------------------------------*/
Jbw_Menu::Jbw_Menu(Jbw_Handles* h, std::string SubMenuName, const SDL_Rect* ParentObj)
{
	Jhandle = h;
	Obj = *ParentObj;
	MenuName.assign(SubMenuName);
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR: ~Jbw_Menu
------------------------------------------------------------------------------------------*/
Jbw_Menu::~Jbw_Menu()
{

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MenuAdd Overload 1: Adding a Top Menu
------------------------------------------------------------------------------------------*/
void Jbw_Menu::MenuAdd(std::string MenuName, int w)
{
	Jbw_SubMenu* TmpMenu = new Jbw_SubMenu[MnuCnt + 1];


	if (MnuCnt > 0) {
		for (int I = 0; I < MnuCnt; I++) {
			TmpMenu[I] = Menu[I];
		}
		delete[] Menu;
	}

	Menu = TmpMenu;

	Menu[MnuCnt].Item = new Jbw_Button(Jhandle, TotalWidth, 0, w, 18, MenuName, 12);
	Menu[MnuCnt].Item->BtnColor = J_WHITE; // Change the color to white
	Menu[MnuCnt].Item->BtnBorderColor = J_WHITE;
	Menu[MnuCnt].Item->CreateButton(); // Because we changed the color

	// This is the Top Menu so it must have Sub Menus
	Menu[MnuCnt].SubMenu = new Jbw_ListBox(Jhandle, Obj.x, Obj.y + 18, 0, 0, 12); // Width & Height will be 
																					//determined later
	MnuCnt++;
	TotalWidth += w;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MenuAdd Overload 2: Adding a Sub Menu
------------------------------------------------------------------------------------------*/
void Jbw_Menu::MenuAdd(std::string MenuName, std::string SubMenuName)
{
	bool FoundMenu = false;

	// Create a new Sub Menu in the link List
	Next = new Jbw_Menu(Jhandle, SubMenuName, &Obj);
	Next->Prev = this;

	// Now link it to the right parent
	while (this != NULL){
		for (int I = 0; I < MnuCnt; I++) {
			if (MenuName.compare(Menu[I].Item->Caption) == 0) { // find the right Menu to add this to.
				FoundMenu = true;
				
				Next->Parent = this;
				break;
			}
			else if()
		}
		if (FoundMenu == true) {
			break;
		}
	} ;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: ItemAdd Overload 1 Adding an Item to the Menu
------------------------------------------------------------------------------------------*/
void Jbw_Menu::ItemAdd(std::string MenuName, std::string MenuItem)
{
	for (int I = 0; I < MnuCnt; I++) {
		//if (MenuName.compare(Menu[I].Name) == 0) {
		//	Menu[I].AddItem(MenuItem);
		//}
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: ItemAdd Overload 2 Adding an Item to the Sub Menu
------------------------------------------------------------------------------------------*/
void Jbw_Menu::ItemAdd(std::string NewText, std::string SubMenuName, std::string MenuItem)
{

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MnuRdr
------------------------------------------------------------------------------------------*/
void Jbw_Menu::MnuRdr(Jbw_Handles* h)
{
	RdrFrame();
	for (int I = 0; I < MnuCnt; I++) {
	//	MainMenu[I].RdrBtn();
		Menu[I].Item->RdrBtn();
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MnuEvent
------------------------------------------------------------------------------------------*/
int Jbw_Menu::MnuEvent(Jbw_Handles* h)
{
	int Answer = -1;

	// Check if Window is active
	if ((SDL_GetWindowFlags(h->JbwGui) & SDL_WINDOW_MOUSE_FOCUS) != SDL_WINDOW_MOUSE_FOCUS) {
		return Answer;
	}

	for (int I = 0; I < MnuCnt; I++) {
		if (MainMenu[I].BtnEvent(&h->Event) == J_BTN_CLICK) {
			Answer = I;
		}
	}
	
	return Answer;
}














