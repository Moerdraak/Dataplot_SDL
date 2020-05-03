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
	
	// Don't use these properties any further
	Prop->Id = -1;
	Prop->Tag = " ";

	// Create Editbox 
	J_Properties Pedit = *Prop;
	Pedit.w = Prop->w - 14;
	CbxEdit.InitEbx(&Pedit);

	// Create Button
	J_Properties Pbtn = *Prop;
	Pbtn.x = Prop->x + Prop->w - 15;
	Pbtn.w = 15;
	CbxBtn.InitBtn(&Pbtn);
	CbxBtn.Text = "^";
	CbxBtn.Flip = SDL_FLIP_VERTICAL;

	// Create List Box
	J_Properties Plbx = *Prop;
	Plbx = *Prop;
	Plbx.y = Prop->y + Prop->h - 1;
	Plbx.w = Prop->w -1;
	Plbx.h = 40;
	CbxList.Visible = false;
	CbxList.InitLbx(&Plbx);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrCbx
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::RdrCbx(Jbw_Handles h)
{	
	if (CbxListVis == true) {

		// Get Main window current position
		int x = 0, y = 0;
		SDL_GetWindowPosition(h.JbwGui, &x, &y);

		// Create List Window
		ListWindow = SDL_CreateWindow("", x + CbxList.FrameX, y + CbxList.FrameY,
			CbxList.FrameW + 1, CbxList.FrameH, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS |
			SDL_WINDOW_ALWAYS_ON_TOP);

		// Create renderer
		ListRdr = SDL_CreateRenderer(ListWindow, -1, SDL_RENDERER_ACCELERATED);
			
		SDL_Rect LstBox = { 0, 0, CbxList.FrameW + 1, CbxList.FrameH };
		SDL_RenderSetViewport(ListRdr, &LstBox);
		
		// Fill Box with white	
		SDL_SetRenderDrawColor(ListRdr, 255, 255, 255, 255);
		SDL_RenderFillRect(ListRdr, &LstBox);
		
		// Draw border around window
		Jbw_Frame Border(ListRdr, 0, 0, CbxList.FrameW + 1, CbxList.FrameH, false);
		Border.LineColor = J_C_Frame;
		Border.RdrFrame();

		SDL_RenderPresent(ListRdr);
	}
	else if (ListWindow != NULL){
		SDL_DestroyRenderer(ListRdr);
		SDL_DestroyWindow(ListWindow);
	}
	CbxEdit.RdrEbx();
	CbxBtn.RdrBtn();

	SDL_RenderPresent(Jrdr); // Render to screen
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CbxEvent
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::CbxEvent(Jbw_Handles h, SDL_Event* e)
{
	bool Inside = false;
	bool Flag = false;
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Mouse pointer inside Dropdown button
		if (x > CbxBtn.EditX&& x < CbxBtn.EditX + CbxBtn.EditW && y > CbxBtn.EditY&& y < CbxBtn.EditY + CbxBtn.EditH)
		{
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				msOver = true;
				CbxBtn.Border.FillColor = J_C_msOver;
				CbxBtn.Border.LineColor = J_C_Black;
				break;

			case SDL_MOUSEBUTTONDOWN:
				CbxBtn.Border.FillColor = J_C_BtnDwn;
				CbxBtn.RdrBtn();
				CbxCall(h, J_CLICK);

				//		SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, &Dp);
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
			// If Combobox is open and user clicks anywhere outside of Combobox
			// List area it must close the Listbox of Combobox
			if (e->type == SDL_MOUSEBUTTONDOWN ) {
				int a = 0;
			}
			if (e->type == SDL_MOUSEBUTTONDOWN && CbxListVis == true) {
				CbxCall(h, J_CLICK); 
			}

		}
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CbxCall
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::CbxCall(Jbw_Handles h, J_Type Type, std::string Input)
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



