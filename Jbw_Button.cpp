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
J_Type Jbw_Button::BtnEvent(SDL_Event* Event)
{
	J_Type EventType = J_NULL;
	//If mouse event happened
	if (Event->type == SDL_MOUSEMOTION || Event->type == SDL_MOUSEBUTTONDOWN ||
		Event->type == SDL_MOUSEBUTTONUP) {
		// Get mouse position
		int msX, msY;
		SDL_GetMouseState(&msX, &msY);

		// Mouse pointer over button
		if (msX > TbxX && msX < TbxX + TbxW && msY > TbxY && msY < TbxY + TbxH)
		{
			if (msOver == false) {
				msOver = true;
				DoRender = true;
			}
			
			switch (Event->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				Border->FillColor = ClickColor;
				DoRender = true;
				EventType = J_BTN_CLICK;
				break;

			case SDL_MOUSEBUTTONUP:
				Border->FillColor = HoverColor;
				DoRender = true;
				break;
			}		
			Border->FillColor = HoverColor;
			Border->LineColor = HoverBorderColor;
		}
		else {
			if (msOver == true) {
				msOver = false;
				DoRender = true;
			}
			Border->LineColor = BtnBorderColor;
			Border->FillColor = BtnColor;
		}

		if (DoRender == true) {
			DoRender = false;
			RdrBtn();
		}
	}
	return EventType;
}