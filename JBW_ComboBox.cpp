#include "JBW_ComboBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ComboBox::Jbw_ComboBox( SDL_Renderer* Rdr, int x, int y, int w, int h, int Fsize)
{
	J_Properties P;
	P.handles.JbwRdr = Rdr;
	P.x = x;
	P.y = y;
	P.w = w;
	P.h = h;
	P.Fsize = Fsize;
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
	
	ComboX = Prop->x; // Needed for the CbxList during Rendering
	ComboY = Prop->y; // Needed for the CbxList during Rendering
	ComboW = Prop->w; // Needed for the CbxList during Rendering
	ComboH = Prop->h; // Needed for the CbxList during Rendering

	// Don't use these properties any further
	Prop->Id = -1;
	Prop->Tag = " ";

	// Initialize Editbox 
	J_Properties Pedit = *Prop;
	Pedit.w = Prop->w - 14;
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

		CbxList.RdrLbx();

		SDL_RenderPresent(ListRdr);

		// Draw border around window
		Jbw_Frame Border(ListRdr, 0, 0, CbxList.FrameW + 1, CbxList.FrameH, false);
		Border.LineColor = J_C_Frame;
		Border.RdrFrame();

		SDL_RenderPresent(ListRdr);
		
	//	h->LbxPtr[0].AddText("Opening List");
		
	}
	else if (ListWindow != NULL){
		SDL_DestroyRenderer(ListRdr);
		SDL_DestroyWindow(ListWindow);
	//	h->LbxPtr[0].AddText("Closing List");
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

	Jbw_ListBox* Tmp = static_cast<Jbw_ListBox*>(h->Jbw_Obj[1]);

	if (h->Event.type == SDL_WINDOWEVENT && CbxListVis == true) {
		if (h->Event.window.event == SDL_WINDOWEVENT_FOCUS_LOST && 
			strcmp(SDL_GetWindowTitle(SDL_GetWindowFromID(h->Event.window.windowID)), 
				"CbxList") == 0) {
			h->LbxPtr[0].AddText("Focus outside");
			Tmp->AddText("Focus outside");
			CbxListVis = false;
			RdrCbx(h);
		}
	}


	//If mouse event happened
	if (h->Event.type == SDL_MOUSEMOTION || h->Event.type == SDL_MOUSEBUTTONDOWN || 
		h->Event.type == SDL_MOUSEBUTTONUP) {
		// Get mouse position
		int x, y, Rx, Ry, Gx, Gy;
		SDL_GetMouseState(&x, &y);
		SDL_GetRelativeMouseState(&Rx, &Ry);
		SDL_GetGlobalMouseState(&Gx, &Gy);

		int wPosX, wPosY;
		SDL_GetWindowPosition(h->JbwGui, &wPosX, &wPosY);

		if (!(x > ComboX && x < CbxBtn.EditX + CbxBtn.EditW 
			&& Gy > wPosY + ComboY && Gy < wPosY + ComboY + ComboH + 80)
			&& CbxListVis == true)
		{
				if (h->Event.type == SDL_MOUSEBUTTONDOWN && (Tag.compare("cbxFigure") == 0)) {
					h->LbxPtr[0].AddText("!Click!");
					Tmp->AddText("!Click!");
				}
			}
		
		// Mouse pointer inside Dropdown button
		if (x > CbxBtn.EditX&& x < CbxBtn.EditX + CbxBtn.EditW && y > CbxBtn.EditY&& y < CbxBtn.EditY + CbxBtn.EditH)
		{
			switch (h->Event.type)
			{
			case SDL_MOUSEMOTION:
				msOver = true;
				CbxBtn.Border.FillColor = J_C_msOver;
				CbxBtn.Border.LineColor = J_C_Black;
				break;

			case SDL_MOUSEBUTTONDOWN:
				CbxBtn.Border.FillColor = J_C_BtnDwn;
				CbxBtn.RdrBtn();
				CbxCall(h, J_CLICK);;
				break;

			case SDL_MOUSEBUTTONUP:
				CbxBtn.Border.FillColor = J_C_msOver;
				CbxBtn.RdrBtn();
				break;
			}
			if (Inside == false) {
				Inside = true;
				CbxBtn.RdrBtn();
			}
		}
		else {
			Inside = false;
			CbxBtn.Border.LineColor = J_C_Frame;
			CbxBtn.Border.FillColor = J_C_BtnGrey;

			if (msOver == true) {
				CbxBtn.RdrBtn();
				msOver = false;
			}
			if (h->Event.type == SDL_MOUSEBUTTONDOWN && (Tag.compare("cbxFigure") == 0)) {

			}

		}
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CbxCall
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::CbxCall(Jbw_Handles *h, J_Type Type, std::string Input)
{
	

	if (Type == J_CLICK) {
		if (CbxListVis == false) {
			CbxListVis = true;
			RdrCbx(h);
		}
		else {
			CbxListVis = false;
			RdrCbx(h);
		}
	}
}



