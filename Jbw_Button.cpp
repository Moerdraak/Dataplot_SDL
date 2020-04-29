#include "Jbw_Button.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Button::Jbw_Button(SDL_Renderer* Rdr, int x, int y, int w, int h,
	std::string Caption, int Fsize)
{
	J_Properties P;
	P.Rdr = Rdr;
	P.x = x;
	P.y = y;
	P.w = w;
	P.h = h;
	P.Caption = Caption;
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
	Text = Prop->Caption;
	Align = J_CENTRE;
	EditX = Prop->x + 1; EditY = Prop->y + 1; EditW = Prop->w - 2; EditH = Prop->h - 2;
	Border.InitFrame(Prop);
	Border.Fill = true;
	Border.LineColor = J_C_Frame;
	Border.FillColor = J_C_BtnGrey;
	Jrdr = Prop->Rdr;
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
void Jbw_Button::BtnEvent(SDL_Event* e)
{

	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Mouse pointer inside Edit box
		if (x > EditX&& x < EditX + EditW && y > EditY&& y < EditY + EditH)
		{


			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				msOver = true;
				Border.FillColor = J_C_msOver;
				Border.LineColor = J_C_Black;
				break;

			case SDL_MOUSEBUTTONDOWN:
				Border.FillColor = J_C_BtnDwn;
				RdrBtn();

				//		SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, &Dp);
				break;

			case SDL_MOUSEBUTTONUP:
				Border.FillColor = J_C_msOver;
				RdrBtn();
				break;
			}			
			if (Inside == false) {
				Inside = true;
				RdrBtn();
			}
		}
		else {
			Inside = false;
			Border.LineColor = J_C_Frame;
			Border.FillColor = J_C_BtnGrey;
			
			if (msOver == true ) {
				RdrBtn();
				msOver = false;	
			}
		}
	}
}