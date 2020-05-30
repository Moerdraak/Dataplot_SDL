#include "Jbw_Slider.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Slider::Jbw_Slider(Jbw_Handles* handles, int x, int y, int w, int h, int Resolution, bool Vertical)
{
	Jhandle = handles;
	Steps = Resolution - 1;
	Vert = Vertical;

	// Size and position for the SliderBox
	if (Vert == true) {
		Obj.x = x;
		Obj.y = y + (w - 1); // Leave space for Up button
		Obj.w = w;
		Obj.h = h - 2 * (w - 1); // Leave space for top and bottom buttons
	}
	else {
		Obj.x = x + (h - 1); // Leave space for Left button
		Obj.y = y; 
		Obj.w = w - 2 * (h - 1); // Leave space for Right and bottom buttons
		Obj.h = h;
	}
	
	Fill = true; // Slider box must be solid grey color
	LineColor = J_C_Frame; // Frame Color
	FillColor = J_C_Grey; // { 240, 240, 240, 255 }
	CreateFrame(); // Create the points for the sliderbox from above info

	// Create Slider 	
	if (Vert == true) {
		int SlrH = (int)floor(Obj.h / (Steps + 1)); // Determine Slider Button height
		if (SlrH < 5) { // Minimum sensible height for a slider
			SlrH = 5;
		}
		Slider = new Jbw_Frame(handles, Obj.x + 1, Obj.y, w - 2, SlrH, true);
		StepSize = (float)(Obj.h - 2 - Slider->Obj.h) / Steps; // Step size when moving slider
	}
	else {
		int SlrW = (int)floor(Obj.w / (Steps + 1)); // Determine Slider Button height
		if (SlrW < 5) { // Minimum sensible height for a slider
			SlrW = 5;
		}
		Slider = new Jbw_Frame(handles, Obj.x, Obj.y + 1, SlrW, h - 2 , true);
		StepSize = (float)(Obj.w - 2 - Slider->Obj.w) / Steps; // Step size when moving slider
	}
	Slider->LineColor = J_C_Frame;
	Slider->FillColor = J_C_BtnGrey;

	// Create Slider Buttons
	if (Vert == true) {
		SldrBtnUp = new Jbw_Button(handles, x, y, w, w, "^"); // Button is square so use width for height as well
		SldrBtnDwn = new Jbw_Button(handles, x, y + h - w, w, w, "^");
		SldrBtnDwn->Tbx->Flip = SDL_FLIP_VERTICAL;
	}
	else {
		SldrBtnUp = new Jbw_Button(handles, x, y, h, h, "<"); // Button is square so use height for width as well
		SldrBtnDwn = new Jbw_Button(handles, x + w - h, y, h, h, ">");
	}
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Slider::~Jbw_Slider() {
	delete Slider;
	delete SldrBtnUp;
	delete SldrBtnDwn;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrSldr
------------------------------------------------------------------------------------------*/
void Jbw_Slider::RdrSldr()
{
	RdrFrame(); // Render Slider Box

	if(BtnRender == true){ // prevents flickering when dragging slider
		BtnRender = false; 
		SldrBtnUp->RdrBtn(); // Render Up button
		SldrBtnDwn->RdrBtn(); // Render Down button
	}
	if (Vert == true) {
		Slider->Obj.y = (int)floor(Obj.y + 1 + SldrPos); // Get the Slider Y position
	}
	else {
		Slider->Obj.x = (int)floor(Obj.x + 1 + SldrPos); // Get the Slider X position

	}
	
	Slider->CreateFrame();
	Slider->RdrFrame(); // Render Slider
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: SldrEvent
------------------------------------------------------------------------------------------*/
void Jbw_Slider::SldrEvent(SDL_Event* Event)
{
	// Only look at these Mouse events
	if (Event->type == SDL_MOUSEMOTION || Event->type == SDL_MOUSEBUTTONDOWN
		|| Event->type == SDL_MOUSEBUTTONUP) 
	{
		if (SliderEvent(Event) == J_TRUE) { // Mouse Events happening on Slider

		}
		else if (BtnUpEvent(Event) == J_UP) { // Mouse Events happening on Up button
			RdrSldr();
		}
		else if (BtnDwnEvent(Event) == J_DOWN) { // Mouse Events happening on Down button
			RdrSldr();
		}
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: SldrEvent
------------------------------------------------------------------------------------------*/
J_Type Jbw_Slider::SliderEvent(SDL_Event* Event)
{
	J_Type Answer = J_NULL;

	// Get mouse position
	int msX, msY;

	SDL_GetMouseState(&msX, &msY);


	// If the mouse button is up the slider can't be active
	if (Event->type == SDL_MOUSEBUTTONUP) {
		SliderActive = false;
		return Answer;
	}

	// Mouse pointer inside Slider 
	if (msX > Slider->Obj.x && msX < Slider->Obj.x + Slider->Obj.w
		&& msY > Slider->Obj.y && msY < Slider->Obj.y + Slider->Obj.h) {
		if (Slider->msOver == false) {
			Slider->msOver = true;
			Slider->LineColor = J_BLACK;
			DoRender = true;
		}

		// If you left click on the Slider button it becomes Active for dragging
		if (Event->type == SDL_MOUSEBUTTONDOWN) {
			if (Vert == true) {
				msStartPos = msY;
			}
			else{
				msStartPos = msX;	
			}
			SldrStartPos = SldrPos;
			SliderActive = true;
		}
	}
	else {
		if (Slider->msOver == true) {
			DoRender = true;
			Slider->msOver = false;
			Slider->LineColor = J_C_Frame;
		}
	}

	// Move slider up and down while Mousebutton down
	if (SliderActive == true) {
		if (Vert == true) {
			SldrPos = msY - msStartPos + SldrStartPos;
			if (SldrPos >= Obj.h - Slider->Obj.h - 1) {// If you pull mouse past maximum of sliderbox
				SldrPos = Obj.h - Slider->Obj.h - 2;
			}
		}
		else {
			SldrPos = msX - msStartPos  + SldrStartPos;
			if (SldrPos >= Obj.w - Slider->Obj.w - 1) {// If you pull mouse past maximum of sliderbox
				SldrPos = Obj.w - Slider->Obj.w - 2;
			}
		}
			
		// If you pull mouse past minimum of sliderbox
		if (SldrPos < 0) {
			SldrPos = 0;
		}

		DoRender = true;
	}

	if (DoRender == true) {
		DoRender = false;
		RdrSldr();
	}
	return Answer;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER LIST
------------------------------------------------------------------------------------------*/
J_Type Jbw_Slider::BtnUpEvent(SDL_Event* Event)
{
	J_Type Answer = J_NULL;
	if (SldrBtnUp->BtnEvent(Event) == J_BTN_CLICK) {
		if (Vert == true ) {
			if (SldrPos > Slider->Obj.h) {
				SldrPos -= (int)StepSize;
			}
			else {
				SldrPos = 0;
			}
		}
		else {
			if (SldrPos > Slider->Obj.w) {
				SldrPos -= (int)StepSize;
			}
			else {
				SldrPos = 0;
			}
		}
		Answer = J_UP;
	}
	return Answer;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER LIST
------------------------------------------------------------------------------------------*/
J_Type Jbw_Slider::BtnDwnEvent(SDL_Event* Event)
{
	J_Type Answer = J_NULL;
	if (SldrBtnDwn->BtnEvent(Event) == J_BTN_CLICK) {
		if (Vert == true) {
			if (SldrPos <= Obj.h - 2 * Slider->Obj.h - 1) {
				SldrPos += (int)StepSize;
			}
			else {
				SldrPos = Obj.h - Slider->Obj.h - 2;
			}
		}
		else {
			if (SldrPos <= Obj.w - 2*Slider->Obj.w - 1) {
				SldrPos += (int)StepSize;
			}
			else {
				SldrPos = Obj.w - Slider->Obj.w - 2;
			}
		}
		Answer = J_DOWN;
	}
	return Answer;
}
