#include "Jbw_ComboBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ComboBox::Jbw_ComboBox(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize,
	bool IsGridBtn)
{
	Jhandle = handles;
	Obj.x = x; 
	Obj.y = y;
	Obj.w = w;
	Obj.h = h;

	CbxTxtSize = Fsize;
	GridBtn = IsGridBtn;
	CreateCbx();
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ComboBox::~Jbw_ComboBox() 
{
	delete CbxEdit;
	delete CbxBtn;
	delete CbxList;
	CbxEdit = NULL;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Create
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::CreateCbx(void)
{
	if (CbxEdit == NULL) {
		if (GridBtn == true) {
			CbxEdit = new Jbw_EditBox(Jhandle, Obj.x, Obj.y, Obj.w, Obj.h, CbxTxtSize);
		}
		else {
			CbxEdit = new Jbw_EditBox(Jhandle, Obj.x, Obj.y, Obj.w - 14, Obj.h, CbxTxtSize);
		}
	}
	else {
		CbxEdit->Obj = Obj;
		if (GridBtn != true) {
			CbxEdit->Obj.w -= 14; // Leave space For Button
		}
		CbxEdit->CreateEbx();
	}

	if (CbxBtn == NULL) {
		CbxBtn = new Jbw_Button(Jhandle, Obj.x + Obj.w - 15, Obj.y, 15, Obj.h, "^");
		CbxBtn->Tbx->Flip = SDL_FLIP_VERTICAL;
	}
	else {
		CbxBtn->Obj.x = Obj.x + Obj.w - 15;
		CbxBtn->Obj.y = Obj.y;
		CbxBtn->Obj.w = 15;
		CbxBtn->Obj.h = Obj.h;
		CbxBtn->CreateButton();
	}

	if (CbxList != NULL) {
		delete CbxList;
		CbxList = NULL;
	}
	if (lsthandles != NULL) {
		delete lsthandles;
		lsthandles = NULL;
	}

	// Create List Box
	lsthandles = new Jbw_Handles;
	CbxList = new Jbw_ListBox(lsthandles, 0, 0, Obj.w, 20, 11);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: InitCbx
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::InitCbx(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize,
	bool IsGridBtn)
{
	Jhandle = handles;
	Obj.x = x;
	Obj.y = y;
	Obj.w = w;
	Obj.h = h;

	CbxTxtSize = Fsize;
	GridBtn = IsGridBtn;
	CreateCbx();
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
		CbxList->ResizeListBox(0, 0 , Obj.w, Lheight);

		// Create Listbox Window
		lsthandles->JbwGui = SDL_CreateWindow("CbxList", GuiX + Obj.x, GuiY + Obj.y + Obj.h - 1,
			Obj.w, Lheight, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS |
			SDL_WINDOW_ALWAYS_ON_TOP);

		// Create Listbox Renderer
		lsthandles->Rdr = SDL_CreateRenderer(lsthandles->JbwGui, -1, SDL_RENDERER_ACCELERATED);

		SDL_RenderPresent(lsthandles->Rdr);
		CbxList->RdrLbx();
		SDL_RenderPresent(lsthandles->Rdr);

		// Draw border around window
		Jbw_Frame Border(lsthandles, 0, 0, CbxList->Obj.w + 1, Lheight, false);
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
J_Type Jbw_ComboBox::CbxEvent(SDL_Event* Event)
{
	J_Type Answer = J_NULL;

	bool Inside = false;
	bool Flag = false;

	if (Event->type == SDL_WINDOWEVENT && CbxListVis == true) {
		if (Event->window.event == SDL_WINDOWEVENT_FOCUS_LOST &&
			strcmp(SDL_GetWindowTitle(SDL_GetWindowFromID(Event->window.windowID)),
				"CbxList") == 0) {
			CbxListVis = false;
			RdrCbx();
		}
	}

	CbxBtn->BtnEvent(Event);
	CbxEdit->EbxEvent(Event);

	if (GridBtn == true) {
		if (CbxBtn->BtnEvent(Event) == J_BTN_CLICK && CbxListVis == false) {
			CbxListVis = true;
			RdrCbx();
			Event->user.type = 1; // OnChange Event
			SDL_PushEvent(Event);
			Answer = J_BTN_CLICK;
		}

		if (CbxBtn->msOver == true || CbxEdit->msOver == true) {
			CbxBtn->RdrBtn();
		}
	}
	else {		
		if (CbxBtn->BtnEvent(Event) == J_BTN_CLICK && CbxListVis == false) {
			CbxListVis = true;
			RdrCbx();
		}
	}

	// Listbox Events
	if (CbxListVis == true && lsthandles != NULL) {
		if (CbxList->LbxEvent(Event) == J_BTN_CLICK) {
			CbxEdit->Tbx->Text.assign(CbxList->TxtList[CbxList->Index].Text);
			CbxEdit->Tbx->CreateTexture();
			CbxEdit->DoRender = true;
			CbxListVis = false;
			RdrCbx();
			OnChange = true;
		}
	}

	if (CbxEdit->DoRender == true) {
		CbxEdit->DoRender = false;
		CbxEdit->RdrEbx();
	}
	return Answer;
}
