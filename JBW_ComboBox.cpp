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
	ComboY = y; // Needed for the CbxList during Rendering
	ComboW = w; // Needed for the CbxList during Rendering
	ComboH = h; // Needed for the CbxList during Rendering

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
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: AddRow
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::AddRow(std::string NewText)
{
	std::string* TmpLbxTxt = new std::string[LbxCnt + 1];

	if (LbxCnt > 0) {
		for (int I = 0; I < LbxCnt; I++) {
			TmpLbxTxt[I] = LbxTxt[I];
		}
		delete[] LbxTxt;
	}
	LbxTxt = TmpLbxTxt;
	LbxTxt[LbxCnt++].assign(NewText);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrCbx
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::RdrCbx()
{	
	// Rendering the Listbox
	if (CbxListVis == true) {

		lsthandles = new Jbw_Handles;

		// Get Main window current position
		int GuiX = 0, GuiY = 0;
		SDL_GetWindowPosition(Jhandle->JbwGui, &GuiX, &GuiY);

		// Create Listbox Window
		lsthandles->JbwGui = SDL_CreateWindow("CbxList", GuiX + ComboX, GuiY + ComboY + ComboH - 1,
			ComboW, 80, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS |
			SDL_WINDOW_ALWAYS_ON_TOP);

		// Create Listbox Renderer
		lsthandles->Rdr = SDL_CreateRenderer(lsthandles->JbwGui, -1, SDL_RENDERER_ACCELERATED);

		// Create List Box

		CbxList = new Jbw_ListBox(lsthandles, 0, 0, ComboW, 80, 11);

		for (int I = 0; I < LbxCnt; I++) {
			CbxList->AddText(LbxTxt[I]);
		}
		SDL_RenderPresent(lsthandles->Rdr);

		CbxList->RdrLbx();

		SDL_RenderPresent(lsthandles->Rdr);

		// Draw border around window
		Jbw_Frame Border(lsthandles, 0, 0, CbxList->FrameW + 1, CbxList->FrameH, false);
		Border.LineColor = J_C_Frame;
		Border.RdrFrame();

		SDL_RenderPresent(lsthandles->Rdr);
		
	//	Jhandle->LbxPtr[0].AddText("Opening List");
	//	Jhandle->LbxPtr[0].RdrLbx(Jhandle);
	}
	else if (lsthandles != NULL){
		SDL_DestroyRenderer(lsthandles->Rdr);
		SDL_DestroyWindow(lsthandles->JbwGui);
		CbxList->Clear();
	}
	CbxEdit->RdrEbx();
	CbxBtn->RdrBtn();

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
	//		Jhandle->LbxPtr[0].AddText("Yo Yo Yo!");
			RdrCbx();
		}
	}

	// Listbox Events
	if (lsthandles != NULL) {
		CbxList->RdrLbx();
	}
}





