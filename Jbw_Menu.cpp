#include "Jbw_Menu.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR Jbw_Menu
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
	DESTRUCTOR ~Jbw_Menu
------------------------------------------------------------------------------------------*/
Jbw_Menu::~Jbw_Menu()
{
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MenuAdd
------------------------------------------------------------------------------------------*/
void Jbw_Menu::MenuAdd(std::string NewText, int w)
{
	Jbw_Button* TmpMainMenu = new Jbw_Button[MnuCnt + 1];

	if (MnuCnt > 0) {
		for (int I = 0; I < MnuCnt; I++) {
			TmpMainMenu[I] = MainMenu[I];
		}
		delete[] MainMenu;
	}
	MainMenu = TmpMainMenu;

	MainMenu[MnuCnt].InitBtn(Jhandle, TotalWidth, 0, w, 18, NewText, 12); // Initialise the basic button
	MainMenu[MnuCnt].BtnColor = J_WHITE; // Change the color to white
	MainMenu[MnuCnt].BtnBorderColor = J_WHITE;
	MainMenu[MnuCnt].CreateButton(); // Because we changed the color

	MnuCnt++;
	TotalWidth += w;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MnuRdr
------------------------------------------------------------------------------------------*/
void Jbw_Menu::MnuRdr(Jbw_Handles* h)
{
	RdrFrame();
	for (int I = 0; I < MnuCnt; I++) {
		MainMenu[I].RdrBtn();
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





