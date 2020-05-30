#include "Jbw_ListBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ListBox::Jbw_ListBox(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize)
{
	Jhandle = handles;

	Obj.x = x;
	Obj.y = y;
	Obj.w = w;
	Obj.h = h;
	FontSize = Fsize;
	TxtBoxH = FontSize + 4; // For Arial the Box height is generaly 2 points bigger than the font size
							// Then add a gap at the top and at the bottom so add 4
	Fill = true;

	LineColor = J_C_Frame; // Frame Color
	CreateFrame(); // Build frame

	// Create Slider Box
	SliderBox = new Jbw_Frame(handles, Obj.x + Obj.w - 15, Obj.y + 14, 15, Obj.h - 28, true);
	SliderBox->LineColor = J_C_Frame;
	SliderBox->FillColor = J_C_LGrey;

	// Create Slider 
	Slider = new Jbw_Frame(handles, Obj.x + Obj.w - 15, Obj.y + 20, 15, 5, true);
	Slider->LineColor = J_C_Frame;
	Slider->FillColor = J_C_BtnGrey;

	// Create Slider Buttons
	SldrBtnUp = new Jbw_Button(handles, Obj.x + Obj.w - 15, Obj.y, 15, 15, "^");
	SldrBtnDwn = new Jbw_Button(handles, Obj.x + Obj.w - 15, Obj.y + Obj.h - 15, 15, 15, "^");
	SldrBtnDwn->Tbx->Flip = SDL_FLIP_VERTICAL;
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ListBox::~Jbw_ListBox() {

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: AddText
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::ResizeListBox(int x, int y, int w, int h)
{
	// Setting basic Listbox size
	Obj.x = x;
	Obj.y = y;
	Obj.w = w;
	Obj.h = h;

	// Setting Slider box position & size
	SliderBox->Obj.x = Obj.x + Obj.w - 15;
	SliderBox->Obj.y = Obj.y + 14; 	//SliderBox->Obj.w = 15; remains the same - never changes
	SliderBox->Obj.h = Obj.h - 28;

	// Setting Slider position
	Slider->Obj.x = Obj.x + Obj.w - 15;
	Slider->Obj.y = Obj.y + 20;

	// Setting Slider Buttons positions
	SldrBtnUp->Obj.x = Obj.x + Obj.w - 15;
	SldrBtnUp->Obj.y = Obj.x + Obj.y;

	SldrBtnDwn->Obj.x = Obj.x + Obj.w - 15;
	SldrBtnDwn->Obj.y = Obj.y + Obj.h - 15;
	SldrBtnDwn->Tbx->Border->Obj.y = SldrBtnDwn->Obj.y;

	FitLines(true);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: AddText
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::AddText(std::string NewTxt)
{
	// Create pointer with more memory
	Jbw_TextBox* NList = new Jbw_TextBox[Cnt + 1];

	for (int I = 0; I < Cnt; I++) {
		NList[I] = TxtList[I]; // Copy all current TxtPtrs		
	}

	NList[Cnt].InitTbx(Jhandle, NewTxt, Obj.x + 3, Obj.y + 3, Obj.w - 5, TxtBoxH);

	if (Cnt > 0) {
		delete[] TxtList;
	}
	TxtList = NList;
	Cnt++;
	TxtRendered = false;

	FitLines(true);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Clear
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::Clear(void)
{
	delete[] TxtList;
	TxtList = NULL;
	Cnt = 0;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Close
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::Close(void)
{

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: FitLines
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::FitLines(bool ChangeCnt)
{
	// Get number of lines that will fit into the ListBox display
	Lines = (int)floor((Obj.h - 20)/TxtBoxH);
	
	// Set Slider size
	Slider->Obj.h = SliderBox->Obj.h - (Cnt - Lines - 1) * TxtBoxH / 5; // Divide by 5 gives a nice slider size
	if (Slider->Obj.h < 4) {
		Slider->Obj.h = 4; // Minimum size of slider
	} 

	if (Cnt > Lines + 1) {
		if (ChangeCnt == true) { // lines were added or deleted
			FromLine = Cnt - Lines - 1;
			ToLine = FromLine + Lines + 1;
		}
		// Number of mouse movement points per line of Text
		PointsPerline = (SliderBox->Obj.h - Slider->Obj.h) / (Cnt - Lines - 1);
	}
	else {
		FromLine = 0;
		ToLine = Cnt;
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Create
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::RdrLbx()
{	
	SDL_Rect RdrBox = { Obj.x, Obj.y, Obj.w, Obj.h };
	SDL_RenderSetViewport(Jhandle->Rdr, &RdrBox);
	
	// Render Frame of ListBox
	RdrFrame(); 
	int TxtWidth = Obj.w - 5;

	if (Cnt > Lines + 1) {
		SliderBox->RdrFrame(); // Render  Slider Frame
		SldrBtnUp->RdrBtn(); // Render Up button
		SldrBtnDwn->RdrBtn(); // Render Down button
		// Set the Slider Y position
		Slider->Obj.y = SliderBox->Obj.y + FromLine * (SliderBox->Obj.h - Slider->Obj.h) / (Cnt - Lines - 1);
		Slider->CreateFrame();
		Slider->RdrFrame(); // Render Slider
		TxtWidth -= 15;
	}

	// Render Text Inside ListBox
	if (TxtList != NULL) {
		TxtRendered = true;
		for (int I = FromLine; I < ToLine; I++) {
			TxtList[I].Obj.y = Obj.y + 1 + (I - FromLine) * TxtBoxH;
			TxtList[I].Obj.w = TxtWidth - 2;
			TxtList[I].Border->Obj.w = TxtWidth;
			TxtList[I].Border->Obj.y = Obj.y + 1 + (I - FromLine) * TxtBoxH;
			TxtList[I].Border->CreateFrame();
			TxtList[I].FrameOn = true;
			TxtList[I].FillOn = true;
			TxtList[I].Border->LineColor = J_WHITE;
			TxtList[I].Border->FillColor = J_WHITE;
			TxtList[I].CreateTexture();
			TxtList[I].RdrTbx();			
		}
	}
	SDL_RenderPresent(Jhandle->Rdr); // Render to screen
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER MAIN
------------------------------------------------------------------------------------------*/
J_Type Jbw_ListBox::LbxEvent(SDL_Event* Event)
{
	J_Type Answer = J_NULL;

	if (Event->type == SDL_MOUSEMOTION || Event->type == SDL_MOUSEBUTTONDOWN
		|| Event->type == SDL_MOUSEBUTTONUP) {

		// Get mouse position
		int msX, msY;
		SDL_GetMouseState(&msX, &msY);

		Answer = ListEvent(Event, msX, msY); // Events happening inside List Box area

		// Only Render the Slider stuff if there are more text lines than the Txtbox can show
		if (Cnt > Lines + 1) { 
			SliderEvent(Event, msX, msY); // Mouse Events happening on Slider
			BtnUpEvent(Event); // Mouse Events happening on Up button
			BtnDwnEvent(Event); // Mouse Events happening on Down button
		}
	}
	return Answer;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER LIST
------------------------------------------------------------------------------------------*/
J_Type Jbw_ListBox::ListEvent(SDL_Event* Event, int msX, int msY)
{
	J_Type Answer = J_NULL;

		// Mouse pointer inside List Box box
		if (msX > Obj.x && msX < Obj.x + Obj.w && msY > Obj.y && msY < Obj.y + Obj.h) {
			msOver = true;

			if (TxtList != NULL) {
				for (int I = FromLine; I < ToLine; I++)
				{
					if (msX > TxtList[I].Border->Obj.x
						&& msX < TxtList[I].Border->Obj.x + TxtList[I].Border->Obj.w
						&& msY > TxtList[I].Border->Obj.y
						&& msY < TxtList[I].Border->Obj.y + 3 + TxtList[I].Border->Obj.h)
					{
						TxtList[I].msOver = true;
						if (TxtList[I].DoRender == false) {
							TxtList[I].DoRender = true;
							TxtList[I].Border->FillColor = J_C_Grey;
							TxtList[I].RdrTbx();
						}
						// Mouse button Click
						if (Event->type == SDL_MOUSEBUTTONDOWN) {
							Index = I;
							Answer = J_BTN_CLICK;
						}
					}
					else
					{
						TxtList[I].msOver = false;
						if (TxtList[I].DoRender == true)
						{
							TxtList[I].DoRender = false;
							TxtList[I].Border->FillColor = J_WHITE;
							if (Index == I) {
								for (int J = FromLine; J < ToLine; J++) {
									TxtList[J].Border->LineColor = J_WHITE;
									TxtList[J].RdrTbx();
								}
								TxtList[I].Border->LineColor = J_C_BtnGrey;
							}
							TxtList[I].RdrTbx();
						}
					}
				}
			}
		}
	return Answer;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER LIST
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::SliderEvent(SDL_Event* Event, int msX, int msY)
{
	// If the mouse button is up the slider can't be active
	if (Event->type == SDL_MOUSEBUTTONUP) {		
		SliderActive = false;
		return;
	}

	// Mouse pointer inside Slider 
	if (msX > Slider->Obj.x && msX < Slider->Obj.x + Slider->Obj.w 
		&& msY > Slider->Obj.y && msY < Slider->Obj.y + Slider->Obj.h) {
		Slider->msOver = true;
		Slider->LineColor = J_BLACK;
		Slider->RdrFrame();

		// If you left click on the Slider button it becomes Active for dragging
		if (Event->type == SDL_MOUSEBUTTONDOWN) {
			msPrevPosY = msY;
			SliderActive = true;
		}	
	}
	else {
		Slider->LineColor = J_C_Frame;
		Slider->RdrFrame();
	}
	
	// Move slider up and down while Mousebutton down
	if (SliderActive == true) {
		if (msPrevPosY - msY > PointsPerline) {
			if (FromLine > 0) {
				FromLine--;
				ToLine--;
				msPrevPosY = msY;
			}
			else { // If you pull mouse past top of sliderbox
				FromLine = 0;		
			}
			RdrLbx();
		}	
		else if (msY - msPrevPosY > PointsPerline) {
			if (FromLine < Cnt - Lines - 1) {
				FromLine++;
				ToLine++;
				msPrevPosY = msY;	
			}
			else {  // If you pull mouse past bottom of sliderbox
				FromLine = Cnt - Lines - 1;
			}
			RdrLbx();
		}
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER LIST
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::BtnUpEvent(SDL_Event* Event)
{
	if (SldrBtnUp->BtnEvent(Event) == J_BTN_CLICK) {
		if (FromLine > 0) {
			FromLine--;
			ToLine--;
			RdrLbx();
		}
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER LIST
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::BtnDwnEvent(SDL_Event* Event)
{
	if (SldrBtnDwn->BtnEvent(Event) == J_BTN_CLICK) {
		if (ToLine < Cnt) {
			FromLine++;
			ToLine++;
			RdrLbx();
		}
	}
}