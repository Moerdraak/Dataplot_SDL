#include "Jbw_Button.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Button::Jbw_Button(Jbw_Handles* handles, int x, int y, int w, int h,
	std::string Caption, int Fsize)
{
	Jhandle = handles;
	Text.assign(Caption);
	Align = J_CENTRE;
	TbxX = x + 1; 
	TbxY = y + 1; 
	TbxW = w - 2; 
	TbxH = h - 2;
	TxtSize = Fsize;

	Border = new Jbw_Frame(handles, x, y, w, h, true);
	Border->LineColor = J_C_Frame;
	Border->FillColor = J_C_BtnGrey;
	
	CreateTexture();
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Button::~Jbw_Button() 
{

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
				Border->FillColor = ClickColor;
				RdrBtn();
				EventType = J_BTN_CLICK;
				//		SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, &Dp);
				break;

			case SDL_MOUSEBUTTONUP:
				Border->FillColor = HoverColor;
				RdrBtn();
				break;
			}		

			Border->FillColor = HoverColor;
			Border->LineColor = HoverBorderColor;
			;
			if (DoRender == false) {
				DoRender = true;
				RdrBtn();
			}
		}
		else {
			msOver = false;
			Border->LineColor = BtnBorderColor;
			Border->FillColor = BtnColor;
			
			if (DoRender == true ) {
				DoRender = false;
				RdrBtn();
			}
		}
	}
	return EventType;
}