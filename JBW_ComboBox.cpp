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
	delete CbxLbx; 
	delete lstHandles;
}

/*-----------------------------------------------------------------------------------------
	COPY CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ComboBox::Jbw_ComboBox(const Jbw_ComboBox& cp) : Jbw_Base(cp)
{
	GridBtn = cp.GridBtn;
	CbxLbxVis = cp.CbxLbxVis;
	CbxTxtSize = cp.CbxTxtSize;

	CbxEdit = new Jbw_EditBox(*cp.CbxEdit);
	CbxBtn = new Jbw_Button(*cp.CbxBtn, cp.CbxBtn->Tbx->Text);
	CbxLbx = new Jbw_ListBox(*cp.CbxLbx);

	// Now change all Cbx Jhandles to point to the specific lstHandles
	lstHandles = new Jbw_Handles;
	CbxLbx->Jhandle = lstHandles;
	CbxLbx->Slider->Jhandle = lstHandles;
	CbxLbx->Slider->SldrBtnDwn->Jhandle = lstHandles;
	CbxLbx->Slider->SldrBtnUp->Jhandle = lstHandles;

	for (int I = 0; I < CbxLbx->Cnt; I++) {
		CbxLbx->TxtList[I].Jhandle = lstHandles;
		CbxLbx->TxtList[I].Border->Jhandle = lstHandles;
	}
}

/*-----------------------------------------------------------------------------------------
	ASIGNMENT OPERATOR OVERLOAD
------------------------------------------------------------------------------------------*/
Jbw_ComboBox& Jbw_ComboBox::operator=(const Jbw_ComboBox& cp)
{
	Jbw_Base::operator=(cp); // Calling Baseclass Assignment

	GridBtn = cp.GridBtn;
	CbxLbxVis = cp.CbxLbxVis;
	CbxTxtSize = cp.CbxTxtSize;

	delete CbxEdit; // Actually these should always be NULL at this point
	delete CbxBtn;
	delete CbxLbx;
	delete lstHandles; 

	CbxEdit = new Jbw_EditBox;
	*CbxEdit = *cp.CbxEdit;

	CbxBtn = new Jbw_Button; // (*cp.CbxBtn);
	*CbxBtn = *cp.CbxBtn;

	CbxLbx = new Jbw_ListBox;
	*CbxLbx = *cp.CbxLbx;
	
	// Now that all CbxLbx stuff was copied we need to replace it's Jhandle with the lsthandles
	lstHandles = new Jbw_Handles;
	CbxLbx->Jhandle = lstHandles;
	CbxLbx->Slider->Jhandle = lstHandles;
	CbxLbx->Slider->SldrBtnDwn->Jhandle = lstHandles;
	CbxLbx->Slider->SldrBtnUp->Jhandle = lstHandles;

	for (int I = 0; I < CbxLbx->Cnt; I++) {
		CbxLbx->TxtList[I].Jhandle = lstHandles;
		CbxLbx->TxtList[I].Border->Jhandle = lstHandles;
	}
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

	if (CbxLbx == NULL) {
		CbxLbx = new Jbw_ListBox(lstHandles, 0, 0, Obj.w, 20, 11);
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
	CbxLbx->AddText(NewText);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CloseList
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::CloseList(void)
{
	SDL_DestroyWindow(lstHandles->Gui);
	SDL_DestroyRenderer(lstHandles->Rdr);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrCbx
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::RdrCbx()
{	
	if (Visible == false) {
		return;
	}

	// Rendering the Listbox
	if (CbxLbxVis == true) {
		// Get Main window current position
		int GuiX = 0, GuiY = 0;
		SDL_GetWindowPosition(Jhandle->Gui, &GuiX, &GuiY);

		// Listbox Height 
		int Lheight = 0;
		if (CbxLbx->Cnt <= 10){											
			Lheight = 6 + CbxLbx->Cnt * 15;// Add 6 for top and bottom spacing	For now textbox height is fixed at 15
		}
		else {
			Lheight = 6 + 10 * 15; // Limit of List box size
		}
		CbxLbx->ResizeListBox(0, 0 , Obj.w, Lheight);

		// Create Listbox Window
		lstHandles->Gui = SDL_CreateWindow("CbxLbx", GuiX + Obj.x, GuiY + Obj.y + Obj.h - 1,
			Obj.w, Lheight, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS ); /* SDL_WINDOW_ALWAYS_ON_TOP*/

		// Create Listbox Renderer
		lstHandles->Rdr = SDL_CreateRenderer(lstHandles->Gui, -1, SDL_RENDERER_ACCELERATED);

		//	CbxLbx->RdrLbx(lstHandles->Rdr);
		CbxLbx->RdrLbx();

		// Draw border around window
		Jbw_Frame Border(lstHandles, 0, 0, CbxLbx->Obj.w + 1, Lheight, false);
		Border.LineColor = J_C_Frame;
		Border.RdrFrame();

	}
	else if (lstHandles != NULL){
		SDL_DestroyRenderer(lstHandles->Rdr);
		SDL_DestroyWindow(lstHandles->Gui);
	}
	if (CbxBtn->Visible == true) {
		CbxBtn->RdrBtn(); // Render the Button
	}
	CbxEdit->RdrEbx(); // Render the Editbox 
	SDL_RenderPresent(Jhandle->Rdr); // Render to screen
	
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CbxEvent
------------------------------------------------------------------------------------------*/
J_Event Jbw_ComboBox::CbxEvent(SDL_Event* Event)
{
	J_Event Answer = J_E_NULL;

	if (Visible == false || Enabled == false) {
		Jhandle->Debug->NewLine("CbxEvent = false");
		return Answer;
	}

	bool Inside = false;
	bool Flag = false;
	
	if (Event->type == SDL_WINDOWEVENT && CbxLbxVis == true) {
		if (Event->window.event == SDL_WINDOWEVENT_FOCUS_LOST &&
			strcmp(SDL_GetWindowTitle(SDL_GetWindowFromID(Event->window.windowID)),
				"CbxLbx") == 0) {
			Jhandle->Debug->NewLine("CbxEvent: CbxLbxVis = false");
			CbxLbxVis = false;
			RdrCbx();
		}
	}

	CbxBtn->BtnEvent(Event);
	CbxEdit->EbxEvent(Event);

	if (GridBtn == true) {
		if (CbxBtn->BtnEvent(Event) == J_MS_LCLICK && CbxLbxVis == false) {
			CbxLbxVis = true;
			RdrCbx();
			Event->user.type = 1; // OnChange Event
			SDL_PushEvent(Event);
			Answer = J_MS_LCLICK;
		}

		if (CbxBtn->msOver == true || CbxEdit->msOver == true) {
			if (CbxBtn->Visible == true) {
				CbxBtn->Enabled = true;
				CbxBtn->RdrBtn(); // Render the Button
			}
		}
		//else {
		//	if (CbxBtn->Enabled == true) {
		//		CbxEdit->DoRender = true;
		//		CbxBtn->Enabled = false;
		//	}
		//}
	}
	else {		
		if (CbxBtn->BtnEvent(Event) == J_MS_LCLICK && CbxLbxVis == false) {
			CbxLbxVis = true;
			RdrCbx();
		}
	}

	// Listbox Events
	if (CbxLbxVis == true && lstHandles != NULL) {
		Jhandle->Debug->NewLine("Jbw_Combobox: CbxEvent, Lbx");
		if (CbxLbx->LbxEvent(Event) == J_MS_LCLICK) {
			CbxEdit->Tbx->Text.assign(CbxLbx->TxtList[CbxLbx->Index].Text);
			CbxEdit->Tbx->CreateTexture();
			CbxEdit->DoRender = true;
			CbxLbxVis = false;
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
