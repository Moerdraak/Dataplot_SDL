#include "JBW_ComboBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ComboBox::Jbw_ComboBox(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize,
	bool IsGridBtn)
{
	InitCbx(handles, x, y, w, h, Fsize, IsGridBtn);
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ComboBox::~Jbw_ComboBox() 
{

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Create
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::InitCbx(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize,
	bool IsGridBtn)
{
	Jhandle = handles;
	GridBtn = IsGridBtn;
	ComboX = x; // Needed for the CbxList during Rendering
	ComboY = y; 
	ComboW = w; 
	ComboH = h; 

	// Initialize Editbox 
	if (GridBtn == true) {
		CbxEdit = new Jbw_EditBox(handles, x, y, w, h, Fsize);
	}
	else {
		CbxEdit = new Jbw_EditBox(handles, x, y, w - 14, h, Fsize);
	}

	// Initialize Button
	CbxBtn = new Jbw_Button(handles, x + w - 15, y, 15, h, "^");
	CbxBtn->Flip = SDL_FLIP_VERTICAL;

	// Initalise List Box
	lsthandles = new Jbw_Handles;
	CbxList = new Jbw_ListBox(lsthandles, 0, 0, ComboW, 20, 11);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: AddRow
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::AddRow(std::string NewText)
{
	CbxList->AddText(NewText);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CloseList
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::CloseList(void)
{
	SDL_DestroyWindow(lsthandles->JbwGui);
	SDL_DestroyRenderer(lsthandles->Rdr);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrCbx
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::RdrCbx()
{	
	// Rendering the Listbox
	if (CbxListVis == true) {
		// Get Main window current position
		int GuiX = 0, GuiY = 0;
		SDL_GetWindowPosition(Jhandle->JbwGui, &GuiX, &GuiY);

		// Listbox Height 
		int Lheight = 0;
		if (CbxList->Cnt <= 10){											
			Lheight = 6 + CbxList->Cnt * 15;// Add 6 for top and bottom spacing	For now textbox height is fixed at 15
		}
		else {
			Lheight = 6 + 10 * 15; // Limit of List box size
		}
		CbxList->ResizeListBox(0, 0 , ComboW, Lheight);

		// Create Listbox Window
		lsthandles->JbwGui = SDL_CreateWindow("CbxList", GuiX + ComboX, GuiY + ComboY + ComboH - 1,
			ComboW, Lheight, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS |
			SDL_WINDOW_ALWAYS_ON_TOP);

		// Create Listbox Renderer
		lsthandles->Rdr = SDL_CreateRenderer(lsthandles->JbwGui, -1, SDL_RENDERER_ACCELERATED);

		SDL_RenderPresent(lsthandles->Rdr);

		CbxList->RdrLbx();

		SDL_RenderPresent(lsthandles->Rdr);

		// Draw border around window
		Jbw_Frame Border(lsthandles, 0, 0, CbxList->FrameW + 1, Lheight, false);
		Border.LineColor = J_C_Frame;
		Border.RdrFrame();

		SDL_RenderPresent(lsthandles->Rdr);
	}
	else if (lsthandles != NULL){
		SDL_DestroyRenderer(lsthandles->Rdr);
		SDL_DestroyWindow(lsthandles->JbwGui);
	}
	
	CbxBtn->RdrBtn(); // Render the Button
	CbxEdit->RdrEbx(); // Render the Editbox 
	SDL_RenderPresent(Jhandle->Rdr); // Render to screen
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CbxEvent
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::CbxEvent()
{
	bool Inside = false;
	bool Flag = false;

	if (Jhandle->Event.type == SDL_WINDOWEVENT && CbxListVis == true) {
		if (Jhandle->Event.window.event == SDL_WINDOWEVENT_FOCUS_LOST &&
			strcmp(SDL_GetWindowTitle(SDL_GetWindowFromID(Jhandle->Event.window.windowID)),
				"CbxList") == 0) {
			CbxListVis = false;
			RdrCbx();
		}
	}

	// EditBox Events
	CbxEdit->EbxEvent(Jhandle);

	if (GridBtn == true) {
		if (CbxBtn->BtnEvent(Jhandle) == J_BTN_CLICK && CbxListVis == false) {
			CbxListVis = true;
			RdrCbx();
		}

		if (CbxBtn->msOver == true || CbxEdit->msOver == true) {
			CbxBtn->RdrBtn();
		}
		else {
			CbxEdit->RdrEbx();
		}
	}
	else {		
		if (CbxBtn->BtnEvent(Jhandle) == J_BTN_CLICK && CbxListVis == false) {
			CbxListVis = true;
			RdrCbx();
		}
	}

	// Listbox Events
	if (CbxListVis == true && lsthandles != NULL) {
		if (CbxList->LbxEvent(Jhandle) == J_BTN_CLICK) {
			CbxEdit->Text.assign(CbxList->TxtList[CbxList->Index].Text);
			CbxEdit->CreateTexture();
			CbxEdit->RdrEbx();
			CbxListVis = false;
			RdrCbx();
		}
	}
}
