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
	CbxBtn = NULL;
	CbxList = NULL;
}

/*-----------------------------------------------------------------------------------------
	COPY CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ComboBox::Jbw_ComboBox(const Jbw_ComboBox& cp) : Jbw_Base(cp)
{
	GridBtn = cp.GridBtn;
	CbxListVis = cp.CbxListVis;
	CbxTxtSize = cp.CbxTxtSize;

	CreateCbx();

	for (int I = 0; I < cp.CbxList->Cnt; I++) {
		CbxList->AddText(cp.CbxList->TxtList[I].Text);
	}
	CbxList->Index = cp.CbxList->Index;

	// Assign TxtBox Border to it's own memory space
	CbxEdit->Tbx->Border = new Jbw_Frame(Jhandle, cp.CbxEdit->Tbx->Border->Obj.x,
		cp.CbxEdit->Tbx->Border->Obj.y, cp.CbxEdit->Tbx->Border->Obj.w,
		cp.CbxEdit->Tbx->Border->Obj.h, cp.CbxEdit->Tbx->Border->Fill);

	CbxEdit->Tbx->txtImage = NULL; // So that you remove it from the prvious memory space without deleting that
	CbxEdit->Tbx->CreateTexture(); // Create its own new TxtImage
}

/*-----------------------------------------------------------------------------------------
	ASIGNMENT OPERATOR OVERLOAD
------------------------------------------------------------------------------------------*/
Jbw_ComboBox& Jbw_ComboBox::operator=(const Jbw_ComboBox& cp)
{
	Jbw_Base::operator=(cp); // Calling Baseclass Assignment

	GridBtn = cp.GridBtn;
	CbxListVis = cp.CbxListVis;
	CbxTxtSize = cp.CbxTxtSize;

	delete CbxEdit;
	delete CbxBtn;
	delete CbxList;
	delete lstHandles;

	
//	CbxEdit = new Jbw_EditBox(*cp.CbxEdit);
//	CbxBtn = new Jbw_Button(*cp.CbxBtn);
//	CbxList = new Jbw_ListBox(*cp.CbxList);
//
//
//	if (lstHandles == NULL) {
//		lstHandles = new Jbw_Handles;
//	}
//
//	if (CbxList == NULL) {
//		CbxList = new Jbw_ListBox(lstHandles, 0, 0, Obj.w, 20, 11);
//	}
//return *this;

		
	CreateCbx();

	for (int I = 0; I < cp.CbxList->Cnt; I++) {
		CbxList->AddText(cp.CbxList->TxtList[I].Text);
	}
	CbxList->Index = cp.CbxList->Index;
	
	// Assign TxtBox Border to it's own memory space
	CbxEdit->Tbx->Border = new Jbw_Frame(Jhandle, cp.CbxEdit->Tbx->Border->Obj.x,
		cp.CbxEdit->Tbx->Border->Obj.y, cp.CbxEdit->Tbx->Border->Obj.w,
		cp.CbxEdit->Tbx->Border->Obj.h, cp.CbxEdit->Tbx->Border->Fill);

	CbxEdit->Tbx->Border->Fill = cp.CbxEdit->Tbx->Border->Fill;
	CbxEdit->Tbx->Border->FillColor = cp.CbxEdit->Tbx->Border->FillColor;

	CbxEdit->Tbx->txtImage = NULL; // So that you remove it from the prvious memory space without deleting that
	
	

	/* NOT RIGHT !!! Must be a shorter way !!*/
	CbxEdit->Tbx->TxtSize = cp.CbxEdit->Tbx->TxtSize;
	CbxEdit->Tbx->Angle = cp.CbxEdit->Tbx->Angle;
	CbxEdit->Tbx->Flip = cp.CbxEdit->Tbx->Flip;
	CbxEdit->Tbx->RotPoint = cp.CbxEdit->Tbx->RotPoint;
	CbxEdit->Tbx->TxtColor = cp.CbxEdit->Tbx->TxtColor;

	CbxEdit->Tbx->F_Bold = cp.CbxEdit->Tbx->F_Bold;
	CbxEdit->Tbx->F_Italic = cp.CbxEdit->Tbx->F_Italic;
	CbxEdit->Tbx->F_UnderL = cp.CbxEdit->Tbx->F_UnderL;
	CbxEdit->Tbx->F_Strike = cp.CbxEdit->Tbx->F_Strike;

	CbxEdit->Tbx->Text = cp.CbxEdit->Tbx->Text;
	CbxEdit->Tbx->Value = cp.CbxEdit->Tbx->Value;

	CbxEdit->Tbx->txtBox = cp.CbxEdit->Tbx->txtBox;
	CbxEdit->Tbx->txtClip = cp.CbxEdit->Tbx->txtClip;
	CbxEdit->Tbx->FrameOn = cp.CbxEdit->Tbx->FrameOn;
	CbxEdit->Tbx->FillOn = cp.CbxEdit->Tbx->FillOn;
	CbxEdit->Tbx->Align = cp.CbxEdit->Tbx->Align;
	CbxEdit->Tbx->Flip = cp.CbxEdit->Tbx->Flip;
	/* NOT RIGHT !!! Must be a shorter way !!*/
	
	CbxEdit->Tbx->CreateTexture(); // Create its own new TxtImage	
	return *this;
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

	if (lstHandles == NULL) {
		lstHandles = new Jbw_Handles;
	}

	if (CbxList == NULL) {
		CbxList = new Jbw_ListBox(lstHandles, 0, 0, Obj.w, 20, 11);
	}
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
	SDL_DestroyWindow(lstHandles->JbwGui);
	SDL_DestroyRenderer(lstHandles->Rdr);
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
		lstHandles->JbwGui = SDL_CreateWindow("CbxList", GuiX + Obj.x, GuiY + Obj.y + Obj.h - 1,
			Obj.w, Lheight, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS |
			SDL_WINDOW_ALWAYS_ON_TOP);

		// Create Listbox Renderer
		lstHandles->Rdr = SDL_CreateRenderer(lstHandles->JbwGui, -1, SDL_RENDERER_ACCELERATED);

		SDL_RenderPresent(lstHandles->Rdr);
		CbxList->RdrLbx();
		SDL_RenderPresent(lstHandles->Rdr);

		// Draw border around window
		Jbw_Frame Border(lstHandles, 0, 0, CbxList->Obj.w + 1, Lheight, false);
		Border.LineColor = J_C_Frame;
		Border.RdrFrame();

		SDL_RenderPresent(lstHandles->Rdr);
	}
	else if (lstHandles != NULL){
		SDL_DestroyRenderer(lstHandles->Rdr);
		SDL_DestroyWindow(lstHandles->JbwGui);
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
	if (CbxListVis == true && lstHandles != NULL) {
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
