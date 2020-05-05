#include "Jbw_Button.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Button::Jbw_Button(SDL_Renderer* Rdr, int x, int y, int w, int h,
	std::string Caption, int Fsize)
{
	J_Properties P;
	P.handles.JbwRdr = Rdr;
	P.x = x;
	P.y = y;
	P.w = w;
	P.h = h;
	P.Caption.assign(Caption);
	P.Fsize = Fsize;
	InitBtn(&P);
}

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
//Jbw_Button::Jbw_Button(J_Properties* Prop)
//{
//	InitEbx(Prop);
//}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Button::~Jbw_Button() 
{

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: InitEbx
------------------------------------------------------------------------------------------*/
void Jbw_Button::InitBtn(J_Properties* Prop)
{
	Id = Prop->Id;
	Tag.assign(Prop->Tag);
	Jrdr = Prop->handles.JbwRdr;
	Text.assign(Prop->Caption);
	Align = J_CENTRE;
	TbxX = Prop->x + 1; TbxY = Prop->y + 1; TbxW = Prop->w - 2; TbxH = Prop->h - 2;
	Border.InitFrame(Prop);
	Border.Fill = true;
	Border.LineColor = J_C_Frame;
	Border.FillColor = J_C_BtnGrey;
	TxtSize = Prop->Fsize;
	CreateTexture();
}



/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrBtn
------------------------------------------------------------------------------------------*/
void Jbw_Button::RdrBtn(void)
{
	CreateTexture();
	RdrEbx();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: BtnEvent
------------------------------------------------------------------------------------------*/
J_Type Jbw_Button::BtnEvent(Jbw_Handles* h)
{
	J_Type EventType = J_NULL;
	//If mouse event happened
	if (h->Event.type == SDL_MOUSEMOTION || h->Event.type == SDL_MOUSEBUTTONDOWN || 
		h->Event.type == SDL_MOUSEBUTTONUP) {
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Mouse pointer inside Edit box
		if (x > TbxX && x < TbxX + TbxW && y > TbxY && y < TbxY + TbxH)
		{
			msOver = true;
			switch (h->Event.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				Border.FillColor = J_C_BtnDwn;
				RdrBtn();
				EventType = J_BTN_CLICK;
				//		SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, &Dp);
				break;

			case SDL_MOUSEBUTTONUP:
				Border.FillColor = J_C_msOver;
				RdrBtn();
				break;
			}		

			Border.FillColor = J_C_msOver;
			Border.LineColor = J_C_Black;
			if (DoRender == false) {
				DoRender = true;
				RdrBtn();
			}
		}
		else {
			msOver = false;
			Border.LineColor = J_C_Frame;
			Border.FillColor = J_C_BtnGrey;
			
			if (DoRender == true ) {
				DoRender = false;
				RdrBtn();
			}
		}
	}
	return EventType;
}