#include "Jbw_Slider.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Slider::Jbw_Slider(Jbw_Handles* handles, int x, int y, int w, int h, int Resolution)
{
	Jhandle = handles;
	Steps = Resolution - 1;
	
	// Size and position for the SliderBox
	FrameX = x;
	FrameY = y + (w - 1); // Leave space for Up button
	FrameW = w;
	FrameH = h - 2 * (w - 1); // Leave space for top and bottom buttons
	Fill = true; // Slider box must be solid grey color
	LineColor = J_C_Frame; // Frame Color
	FillColor = J_C_LGrey;
	CreatePts(); // Create the points for the sliderbox from above info

	// Create Slider 	
	int SlrH = (int)floor(FrameH / (Steps + 1)); // Determine Slider Button height
	if(SlrH < 5){ // Minimum sensible height for a slider
		SlrH = 5;
	}
	Slider = new Jbw_Frame(handles, FrameX + 1, FrameY, w - 2, SlrH, true);
	Slider->LineColor = J_C_Frame;
	Slider->FillColor = J_C_BtnGrey;
	StepSize = (float)(FrameH - 2 - Slider->FrameH) / Steps; // Step size when moving slider

	// Create Slider Buttons
	SldrBtnUp = new Jbw_Button(handles, x, y, w, w, "^"); // Button is square so use width for height as well
	SldrBtnDwn = new Jbw_Button(handles, x, y + h - w, w, w, "^");
	SldrBtnDwn->Flip = SDL_FLIP_VERTICAL;
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
void Jbw_Slider::RdrSldr(void)
{
	RdrFrame(); // Render Slider Box

	if(BtnRender == true){ // prevents flickering when dragging slider
		BtnRender = false; 
		SldrBtnUp->RdrBtn(); // Render Up button
		SldrBtnDwn->RdrBtn(); // Render Down button
	}
	Slider->FrameY = (int)floor(FrameY + 1 + SldrPos * StepSize); // Get the Slider Y position
	Slider->CreatePts();
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
	if (msX > Slider->FrameX&& msX < Slider->FrameX + Slider->FrameW
		&& msY > Slider->FrameY&& msY < Slider->FrameY + Slider->FrameH) {
		if (Slider->msOver == false) {
			Slider->msOver = true;
			Slider->LineColor = J_BLACK;
			DoRender = true;
		}

		// If you left click on the Slider button it becomes Active for dragging
		if (Event->type == SDL_MOUSEBUTTONDOWN) {
			msStartPos = msY;
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
	
		SldrPos = (msY - msStartPos) / StepSize + SldrStartPos;
			
		// If you pull mouse past edges of sliderbox
		if (SldrPos < 0) {
			SldrPos = 0;
		}
		else if (SldrPos > Steps) { 
			SldrPos = Steps;
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
		Answer = J_BTN_CLICK;
		if (SldrPos > 0) {
			SldrPos--;
			Answer = J_UP;
		}
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
		if (SldrPos < Steps) {
			SldrPos++;
			Answer = J_DOWN;
		}
	}
	return Answer;
}
