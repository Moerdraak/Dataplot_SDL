#include "JBW_ComboBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ComboBox::Jbw_ComboBox( SDL_Renderer* Rdr, int x, int y, int w, int h, int Fsize, 
	bool IsGridBtn)
{
	J_Properties P;
	P.handles.JbwRdr = Rdr;
	P.x = x;
	P.y = y;
	P.w = w;
	P.h = h;
	P.Fsize = Fsize;
	P.BoolVal = IsGridBtn;
	InitCbx(&P);
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
void Jbw_ComboBox::InitCbx(J_Properties* Prop)
{
	Id = Prop->Id;
	Tag.assign(Prop->Tag);
	Jrdr = Prop->handles.JbwRdr;
	
	GridBtn = Prop->BoolVal;
	ComboX = Prop->x; // Needed for the CbxList during Rendering
	ComboY = Prop->y; // Needed for the CbxList during Rendering
	ComboW = Prop->w; // Needed for the CbxList during Rendering
	ComboH = Prop->h; // Needed for the CbxList during Rendering

	// Don't use these properties any further
	Prop->Id = -1;
	Prop->Tag = " ";

	// Initialize Editbox 
	J_Properties Pedit = *Prop;
	if (GridBtn == true) {
		Pedit.w = Prop->w;
	}
	else {
		Pedit.w = Prop->w - 14;
	}
	
	CbxEdit.InitEbx(&Pedit);

	// Initialize Button
	J_Properties Pbtn = *Prop;
	Pbtn.x = Prop->x + Prop->w - 15;
	Pbtn.w = 15;
	CbxBtn.InitBtn(&Pbtn);
	CbxBtn.Text = "^";
	CbxBtn.Flip = SDL_FLIP_VERTICAL;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: AddRow
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::AddRow(Jbw_Handles* h, std::string NewText)
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
void Jbw_ComboBox::RdrCbx(Jbw_Handles* h)
{	
	// Rendering the Listbox
	if (CbxListVis == true) {

		// Get Main window current position
		int GuiX = 0, GuiY = 0;
		SDL_GetWindowPosition(h->JbwGui, &GuiX, &GuiY);

		// Create Listbox Window
		ListWindow = SDL_CreateWindow("CbxList", GuiX + ComboX, GuiY + ComboY + ComboH - 1,
			ComboW, 80, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS |
			SDL_WINDOW_ALWAYS_ON_TOP);

		// Create Listbox Renderer
		ListRdr = SDL_CreateRenderer(ListWindow, -1, SDL_RENDERER_ACCELERATED);
		SDL_RenderPresent(ListRdr);
		// Create List Box
		J_Properties Plbx;
		// Plbx.handles.GuiArea = { 0, 0, 0, 0 };
		Plbx.handles.JbwGui = ListWindow;
		Plbx.handles.JbwRdr = ListRdr;

		Plbx.x = 0;
		Plbx.y = 0;
		Plbx.w = ComboW;
		Plbx.h = 80;
		CbxList.InitLbx(&Plbx);
		for (int I = 0; I < LbxCnt; I++) {
			CbxList.AddText(LbxTxt[I]);
		}
		SDL_RenderPresent(ListRdr);

		CbxList.RdrLbx(h);

		SDL_RenderPresent(ListRdr);

		// Draw border around window
		Jbw_Frame Border(ListRdr, 0, 0, CbxList.FrameW + 1, CbxList.FrameH, false);
		Border.LineColor = J_C_Frame;
		Border.RdrFrame();

		SDL_RenderPresent(ListRdr);
		
	//	h->LbxPtr[0].AddText("Opening List");
	//	h->LbxPtr[0].RdrLbx(h);	
	}
	else if (ListWindow != NULL){
		SDL_DestroyRenderer(ListRdr);
		SDL_DestroyWindow(ListWindow);
		CbxList.Clear();
	}
	CbxEdit.RdrEbx();
	CbxBtn.RdrBtn();

	SDL_RenderPresent(Jrdr); // Render to screen
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CbxEvent
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::CbxEvent(Jbw_Handles *h)
{
	bool Inside = false;
	bool Flag = false;

	if (h->Event.type == SDL_WINDOWEVENT && CbxListVis == true) {
		if (h->Event.window.event == SDL_WINDOWEVENT_FOCUS_LOST && 
			strcmp(SDL_GetWindowTitle(SDL_GetWindowFromID(h->Event.window.windowID)), 
				"CbxList") == 0) {
			CbxListVis = false;
			RdrCbx(h);
		}
	}

	// EditBox Events
	CbxEdit.EbxEvent(h);

	if (GridBtn == true) {
		if (CbxBtn.BtnEvent(h) == J_BTN_CLICK && CbxListVis == false) {
			CbxListVis = true;
			RdrCbx(h);
		}

		if (CbxBtn.msOver == true || CbxEdit.msOver == true) {
			CbxBtn.RdrBtn();
		}
		else {
			CbxEdit.RdrEbx();
		}
	}
	else {		
		if (CbxBtn.BtnEvent(h) == J_BTN_CLICK && CbxListVis == false) {
			CbxListVis = true;
			RdrCbx(h);
		}
	}

	// Listbox Events
	if (ListWindow != NULL) {
		CbxList.RdrLbx(h);
	}



}





