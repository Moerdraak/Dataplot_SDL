#include "JBW_ComboBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ComboBox::Jbw_ComboBox( SDL_Renderer* Rdr, int x, int y, int w, int h, int Fsize)
{
	J_Properties P;
	P.Rdr = Rdr;
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
	J_Properties P = *Prop;

	Jrdr = Prop->Rdr;
	
	// initialise  Editbox 
	P.w = Prop->w - 15;
	CbxEdit.InitEbx(&P);

	// Create Button
	P = *Prop;
	P.x = Prop->x + Prop->w - 16;
	P.w = 15;
	CbxBtn.InitBtn(&P);
	CbxBtn.Text = "\^";
	CbxBtn.Flip = SDL_FLIP_VERTICAL;

	// Create List Box
	P = *Prop;
	P.y = Prop->y + Prop->h - 1;
	P.w = Prop->w -1;
	P.h = 40;
	CbxList.Visible = false;
	CbxList.InitLbx(&P);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrCbx
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::RdrCbx(void)
{	
	if (CbxListVis == true) {
		CbxList.RdrLbx();
	}
	else {	
	//	SDL_Window *Big = new SDL_Window;
		int x, y;
	//	SDL_GetWindowPosition(UserWindow, &x, &y);
		// Create User Window
		SDL_Window* MsgWindow = SDL_CreateWindow("MsgBox", CbxList.FrameX, CbxList.FrameY, 
			CbxList.FrameW, CbxList.FrameH, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | 
			SDL_WINDOW_ALWAYS_ON_TOP);

		// Create renderer
		SDL_Renderer* LbxRdr = SDL_CreateRenderer(MsgWindow, -1, SDL_RENDERER_ACCELERATED);

		SDL_Rect FillArea = { 0, 0, CbxList.FrameW, CbxList.FrameH };
		SDL_RenderSetViewport(LbxRdr, &FillArea);
		SDL_SetRenderDrawColor(LbxRdr, 255, 255, 255, 255);
		SDL_RenderFillRect(LbxRdr, &FillArea);
		SDL_RenderPresent(LbxRdr);


	}
	CbxEdit.RdrEbx();
	CbxBtn.RdrBtn();

	SDL_RenderPresent(Jrdr); // Render to screen
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CbxEvent
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::CbxEvent(SDL_Event* e)
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
				CbxCall(J_CLICK);

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
		}
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CbxCall
------------------------------------------------------------------------------------------*/
void Jbw_ComboBox::CbxCall(J_Type Type, std::string Input)
{
	if (Type == J_CLICK) {
		if (CbxListVis == false) {
			CbxListVis = true;
			RdrCbx();
		}
		else {
			CbxListVis = false;
			RdrCbx();
			// Push User event to anything inside the Frame area so that it
			// will render again.
		}
		
	}
}