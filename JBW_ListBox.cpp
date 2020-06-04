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
	Slider = new Jbw_Slider(Jhandle, Obj.x + Obj.w - 15, Obj.y, 15, Obj.h, 5/* random start value */, true);
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ListBox::~Jbw_ListBox() {

	delete[] TxtList;
	delete Slider;
}

/*-----------------------------------------------------------------------------------------
	COPY CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ListBox::Jbw_ListBox(const Jbw_ListBox& cp) : Jbw_Frame(cp)
{
	Cnt = cp.Cnt;
	TxtBoxH = cp.TxtBoxH;
	FontSize = cp.FontSize;
	Lines = cp.Lines;
	Index = 0;

	PointsPerline = 0;

	Slider = new Jbw_Slider(*cp.Slider);
	TxtList = new Jbw_TextBox[Cnt];
	for (int I = 0; I < Cnt; I++) {
		TxtList[I] = cp.TxtList[I];
	}
}

/*-----------------------------------------------------------------------------------------
	ASIGNMENT OPERATOR OVERLOAD
------------------------------------------------------------------------------------------*/
Jbw_ListBox& Jbw_ListBox::operator=(const Jbw_ListBox& cp)
{
	//	Jbw_Base(cp);
	Jbw_Frame::operator=(cp); // Calling Baseclass Assignment

	Cnt = cp.Cnt;
	TxtBoxH = cp.TxtBoxH;
	FontSize = cp.FontSize;
	Lines = cp.Lines;
	PointsPerline = cp.PointsPerline;

	delete Slider;
	Slider = new Jbw_Slider;
	*Slider = *cp.Slider;

	delete TxtList;
	TxtList = new Jbw_TextBox[Cnt];
	for (int I = 0; I < Cnt; I++) {
		TxtList[I] = cp.TxtList[I];
	}

	return *this;
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

	Slider = new Jbw_Slider(Jhandle, Obj.x + Obj.w - 15, Obj.y, 15, Obj.h, 5/* random start value */, true);
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

	if (Cnt > Lines + 1) {
		Slider->SetResolution(Cnt - Lines - 1);
		FromLine = 0;
		ToLine = FromLine + Lines + 1;
	}
	else {
		FromLine = 0;
		ToLine = Cnt;
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrLbx
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::RdrLbx()
{	
	SDL_Rect RdrBox = { Obj.x, Obj.y, Obj.w, Obj.h };
	SDL_RenderSetViewport(Jhandle->Rdr, &RdrBox);
	
	// Render Frame of ListBox
	RdrFrame(); 
	int TxtWidth = Obj.w - 5;

	if (Cnt > Lines + 1) {
		Slider->BtnRender = true;
		Slider->RdrSldr();
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
	SDL_RenderPresent(Jhandle->Rdr); 
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER MAIN
------------------------------------------------------------------------------------------*/
J_Type Jbw_ListBox::LbxEvent(SDL_Event* Event)
{
	J_Type Answer = J_NULL;

	if (Visible == false || Enabled == false) {
		return Answer;
	}

	if (Event->type == SDL_MOUSEMOTION || Event->type == SDL_MOUSEBUTTONDOWN
		|| Event->type == SDL_MOUSEBUTTONUP) {

		// Get mouse position
		int msX, msY;
		SDL_GetMouseState(&msX, &msY);

		Answer = ListEvent(Event, msX, msY); // Events happening inside List Box area

		// Only Render the Slider stuff if there are more text lines than the Txtbox can show
		if (Cnt > Lines + 1) { 
			J_Type S_Return = Slider->SldrEvent(Event);
			 if (S_Return != J_NULL) {
				int Tmp = FromLine;
				FromLine = Slider->StepPos;
				if (FromLine != Tmp) { // Only render if changed - prevent flicker
					ToLine = FromLine + Lines + 1;
					RdrLbx();
				}
			}
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

