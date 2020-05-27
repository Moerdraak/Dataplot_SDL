#include "Jbw_Menu.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR Jbw_Menu
------------------------------------------------------------------------------------------*/
Jbw_Menu::Jbw_Menu(Jbw_Handles* handles)
{
	Jhandle = handles;
	// Create Frame at the top of the screen
	FrameX = 0;
	FrameY = 0; // Hide Top line of Frame
	FrameH = 18;
	FrameW = Jhandle->GuiArea.w;
	LineColor = J_WHITE;
	FillColor = J_WHITE;
	Fill = true;
	CreatePts(); // Create the frame points from above info
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

	MainMenu[MnuCnt].Jhandle = Jhandle;
	MainMenu[MnuCnt].TbxX = TotalWidth + 1;
	MainMenu[MnuCnt].TbxY = 1;
	MainMenu[MnuCnt].TbxW = w-2;
	MainMenu[MnuCnt].TbxH = 16;
	MainMenu[MnuCnt].TxtSize = 12;
	MainMenu[MnuCnt].Align = J_CENTRE;
	MainMenu[MnuCnt].Add(NewText);

	// Build a nice border
	MainMenu[MnuCnt].Border = new Jbw_Frame(Jhandle, TotalWidth, 0, w, 18, true);
	MainMenu[MnuCnt].Border->FrameX = TotalWidth;
	MainMenu[MnuCnt].Border->FrameY = 0;
	MainMenu[MnuCnt].Border->FrameW = w;
	MainMenu[MnuCnt].Border->FrameH = 18;
	MainMenu[MnuCnt].Border->CreatePts();
	MainMenu[MnuCnt].Border->LineColor = J_WHITE;
	MainMenu[MnuCnt].Border->FillColor = J_WHITE;	
	MainMenu[MnuCnt].BtnColor = J_WHITE;
	MainMenu[MnuCnt].BtnBorderColor = J_WHITE;
	MainMenu[MnuCnt].HoverColor = J_C_msOver;
	MainMenu[MnuCnt].HoverBorderColor = J_C_Frame;
	MainMenu[MnuCnt].ClickColor = J_C_BtnDwn;
	
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
		if (MainMenu[I].BtnEvent(h) == J_BTN_CLICK) {
			Answer = I;
		}
	}
	
	return Answer;
}





