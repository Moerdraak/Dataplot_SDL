#include "Jbw_ListBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ListBox::Jbw_ListBox(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize)
{
	Jhandle = handles;

	FrameX = x;
	FrameY = y;
	FrameW = w;
	FrameH = h;
	FontSize = Fsize;
	TxtBoxH = FontSize + 4; // For Arial the Box height is generaly 2 points bigger than the font size
							// Then add a gap at the top and at the bottom so add 4
	Fill = true;

	LineColor = J_C_Frame; // Frame Color
	CreatePts(); // Build frame

	// Create Slider Box
	SliderBox = new Jbw_Frame(handles, FrameX + FrameW - 15, FrameY + 14, 15, FrameH - 28, true);
	SliderBox->LineColor = J_C_Frame;
	SliderBox->FillColor = J_C_LGrey;

	// Create Slider 
	Slider = new Jbw_Frame(handles, FrameX + FrameW - 15, FrameY + 20, 15, 5, true);
	Slider->LineColor = J_C_Frame;
	Slider->FillColor = J_C_BtnGrey;

	// Create Slider Buttons
	SldrBtnUp = new Jbw_Button(handles, FrameX + FrameW - 15, FrameY, 15, 15, "^");
	SldrBtnDwn = new Jbw_Button(handles, FrameX + FrameW - 15, FrameY + FrameH - 15, 15, 15, "^");
	SldrBtnDwn->Flip = SDL_FLIP_VERTICAL;
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
	FrameX = x;
	FrameY = y;
	FrameW = w;
	FrameH = h;

	// Setting Slider box position & size
	SliderBox->FrameX = FrameX + FrameW - 15;
	SliderBox->FrameY = FrameY + 14; 	//SliderBox->FrameW = 15; remains the same - never changes
	SliderBox->FrameH = FrameH - 28;

	// Setting Slider position
	Slider->FrameX = FrameX + FrameW - 15;
	Slider->FrameY = FrameY + 20;

	// Setting Slider Buttons positions
	SldrBtnUp->TbxX = FrameX + FrameW - 15;
	SldrBtnUp->TbxY = FrameX + FrameY;

	SldrBtnDwn->TbxX = FrameX + FrameW - 15;
	SldrBtnDwn->TbxY = FrameY + FrameH - 15;
	SldrBtnDwn->Border->FrameY = SldrBtnDwn->TbxY;

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

	NList[Cnt].InitTbx(Jhandle, NewTxt, FrameX + 3, FrameY + 3, FrameW - 5, TxtBoxH);
	NList[Cnt].Add(NewTxt);
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
	Lines = (int)floor((FrameH - 20)/TxtBoxH);
	
	// Set Slider size
	Slider->FrameH = SliderBox->FrameH - (Cnt - Lines - 1) * TxtBoxH / 5; // Divide by 5 gives a nice slider size
	if (Slider->FrameH < 4) {
		Slider->FrameH = 4; // Minimum size of slider
	} 

	if (Cnt > Lines + 1) {
		if (ChangeCnt == true) { // lines were added or deleted
			FromLine = Cnt - Lines - 1;
			ToLine = FromLine + Lines + 1;
		}
		// Number of mouse movement points per line of Text
		PointsPerline = (SliderBox->FrameH - Slider->FrameH) / (Cnt - Lines - 1);
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
	SDL_Rect RdrBox = { FrameX, FrameY, FrameW, FrameH };
	SDL_RenderSetViewport(Jhandle->Rdr, &RdrBox);
	
	// Render Frame of ListBox
	RdrFrame(); 
	int TxtWidth = FrameW - 5;

	if (Cnt > Lines + 1) {
		SliderBox->RdrFrame(); // Render  Slider Frame
		SldrBtnUp->RdrBtn(); // Render Up button
		SldrBtnDwn->RdrBtn(); // Render Down button
		// Set the Slider Y position
		Slider->FrameY = SliderBox->FrameY + FromLine * (SliderBox->FrameH - Slider->FrameH) / (Cnt - Lines - 1);
		Slider->CreatePts();
		Slider->RdrFrame(); // Render Slider
		TxtWidth -= 15;
	}

	// Render Text Inside ListBox
	if (TxtList != NULL) {
		TxtRendered = true;
		for (int I = FromLine; I < ToLine; I++) {
			TxtList[I].TbxY = FrameY + 1 + (I - FromLine) * TxtBoxH;
			TxtList[I].TbxW = TxtWidth - 2;
			TxtList[I].Border->FrameW = TxtWidth;
			TxtList[I].Border->FrameY = FrameY + 1 + (I - FromLine) * TxtBoxH;
			TxtList[I].Border->CreatePts();
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
J_Type Jbw_ListBox::LbxEvent(Jbw_Handles* h)
{
	J_Type Answer = J_NULL;

	if (h->Event.type == SDL_MOUSEMOTION || h->Event.type == SDL_MOUSEBUTTONDOWN
		|| h->Event.type == SDL_MOUSEBUTTONUP) {

		// Get mouse position
		int msX, msY;
		SDL_GetMouseState(&msX, &msY);

		Answer = ListEvent(h, msX, msY); // Events happening inside List Box area

		// Only Render the Slider stuff if there are more text lines than the Txtbox can show
		if (Cnt > Lines + 1) { 
			SliderEvent(h, msX, msY); // Mouse Events happening on Slider
			BtnUpEvent(h); // Mouse Events happening on Up button
			BtnDwnEvent(h); // Mouse Events happening on Down button
		}
	}
	return Answer;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER LIST
------------------------------------------------------------------------------------------*/
J_Type Jbw_ListBox::ListEvent(Jbw_Handles* h, int msX, int msY)
{
	J_Type Answer = J_NULL;

		// Mouse pointer inside List Box box
		if (msX > FrameX&& msX < FrameX + FrameW && msY > FrameY&& msY < FrameY + FrameH) {
			msOver = true;
			if (TxtList != NULL) {
				for (int I = FromLine; I < ToLine; I++)
				{
					if (msX > TxtList[I].TbxX
						&& msX < TxtList[I].TbxX + TxtList[I].TbxW
						&& msY > TxtList[I].TbxY + 6
						&& msY < TxtList[I].TbxY + 7 + TxtList[I].TbxH)
					{
						TxtList[I].msOver = true;
						if (TxtList[I].DoRender == false) {
							TxtList[I].DoRender = true;
							TxtList[I].Border->FillColor = J_C_Grey;
							TxtList[I].RdrTbx();
						}
						// Mouse button Click
						if (h->Event.type == SDL_MOUSEBUTTONDOWN) {
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
void Jbw_ListBox::SliderEvent(Jbw_Handles* h, int msX, int msY)
{
	// If the mouse button is up the slider can't be active
	if (h->Event.type == SDL_MOUSEBUTTONUP) {		
		SliderActive = false;
		return;
	}

	// Mouse pointer inside Slider 
	if (msX > Slider->FrameX && msX < Slider->FrameX + Slider->FrameW 
		&& msY > Slider->FrameY && msY < Slider->FrameY + Slider->FrameH) {
		Slider->msOver = true;
		Slider->LineColor = J_BLACK;
		Slider->RdrFrame();

		// If you left click on the Slider button it becomes Active for dragging
		if (h->Event.type == SDL_MOUSEBUTTONDOWN) {
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
void Jbw_ListBox::BtnUpEvent(Jbw_Handles* h)
{
	if (SldrBtnUp->BtnEvent(h) == J_BTN_CLICK) {
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
void Jbw_ListBox::BtnDwnEvent(Jbw_Handles* h)
{
	if (SldrBtnDwn->BtnEvent(h) == J_BTN_CLICK) {
		if (ToLine < Cnt) {
			FromLine++;
			ToLine++;
			RdrLbx();
		}
	}
}