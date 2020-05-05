#include "JBW_ListBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ListBox::Jbw_ListBox(SDL_Renderer* Rdr, int x, int y, int w, int h, int Fsize)
{
	J_Properties P;
	P.handles.JbwRdr = Rdr;
	P.x = x;
	P.y = y;
	P.w = w;
	P.h = h;
	P.Fsize = Fsize;
	InitLbx(&P);
}

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ListBox::Jbw_ListBox(J_Properties* Prop)
{
	delete SliderBox;
	delete[] TxtList;
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_ListBox::~Jbw_ListBox() {

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Init
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::InitLbx(J_Properties* Prop)
{
	Id = Prop->Id;
	Tag.assign(Prop->Tag);
	Jrdr = Prop->handles.JbwRdr;
	
	FrameX = Prop->x;
	FrameY = Prop->y;
	FrameW = Prop->w;
	FrameH = Prop->h;
	FontSize = Prop->Fsize;
	Fill = true;

	LineColor =  J_C_Frame; // Frame Color
	CreatePts(); // Build frame
		
	// Create SliderBox
	SliderBox = new Jbw_Frame(Jrdr, FrameX + FrameW-15, FrameY + 14, 15, FrameH - 28, true);
	SliderBox->LineColor = J_C_Frame;
	SliderBox->FillColor = J_C_LGrey;

	// Create Slider Thingy
	Slider = new Jbw_Frame(Jrdr, FrameX + FrameW - 15, FrameY + 20, 15, 5, true);
	Slider->LineColor = J_C_Frame;
	Slider->FillColor = J_C_BtnGrey;

	// Create SliderButtons
	SldrBtnUp = new Jbw_Button(Jrdr, FrameX + FrameW - 15, FrameY, 15, 15,"^");
	SldrBtnDwn = new Jbw_Button(Jrdr, FrameX + FrameW - 15, FrameY + FrameH - 15, 15, 15, "^");
	SldrBtnDwn->Flip = SDL_FLIP_VERTICAL;
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

	NList[Cnt].InitTbx(Jrdr, NewTxt, FrameX + 3, FrameY + 3, FrameW - 5, 15);
	NList[Cnt].Add(NewTxt);

	if (Cnt > 0) {
		delete[] TxtList;
	}
	TxtList = NList;
	Cnt++;
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
	FUNCTION: Create
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::RdrLbx(Jbw_Handles* h)
{	
	SDL_Rect RdrBox = { FrameX, FrameY, FrameW, FrameH };
	SDL_RenderSetViewport(Jrdr, &RdrBox);
	
	// Render Frame of ListBox
	RdrFrame(); 

	// Get number of lines that will fit into the ListBox display
	Lines = (int)floor(FrameH / (FontSize + 1));
	FromLine = 0;
	ToLine = Cnt;
	if (Cnt > Lines) {
		FromLine = Cnt - Lines;
		ToLine = FromLine + Lines;
		SliderBox->RdrFrame(); // Render frame
		SldrBtnUp->RdrBtn(); // Render
		SldrBtnDwn->RdrBtn(); // Render
		
		Slider->FrameY = SliderBox->FrameY + 
			(int)floor(FromLine * (SliderBox->FrameH) / (Cnt)) - Lines;
		Slider->FrameH = SliderBox->FrameH - (Slider->FrameY - SliderBox->FrameY) - 1;
		Slider->CreatePts();
		Slider->RdrFrame();
	}

	// Render Text Inside ListBox
	if (TxtList != NULL && TxtRendered == false) {
		TxtRendered = true;
		for (int I = FromLine; I < ToLine; I++) {
			TxtList[I].TbxY = FrameY + 3 + (I - FromLine) * (FontSize + 1);
			TxtList[I].Border.FrameY = FrameY + 3 + (I - FromLine) * (FontSize + 4);
			TxtList[I].Border.CreatePts();
			TxtList[I].ShowFrame = true;
			TxtList[I].Border.LineColor = J_C_White;
			TxtList[I].Border.FillColor = J_C_White;
			TxtList[I].CreateTexture();
			TxtList[I].RdrTbx();			
		}
	}
	SDL_RenderPresent(Jrdr); // Render to screen
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::LbxEvent(Jbw_Handles* h)
{
	if (h->Event.type == SDL_MOUSEMOTION || h->Event.type == SDL_MOUSEBUTTONDOWN 
		|| h->Event.type == SDL_MOUSEBUTTONUP) {
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Mouse pointer inside Edit box
		if (x > FrameX && x < FrameX + FrameW
			&& y > FrameY && y < FrameY + FrameH)
		{
			msOver = true;
			//	RdrLbx(h);
			if (TxtList != NULL) {
				//		TxtList[0].EbxEvent(h);
			}
			for (int I = FromLine; I < ToLine; I++) {
				
				if (x > TxtList[I].TbxX && x < TxtList[I].TbxX + TxtList[I].TbxW
					&& y > TxtList[I].TbxY + 6 && y < TxtList[I].TbxY + 7 + TxtList[I].TbxH) {
					
					if (TxtList[I].DoRender == false) {
						TxtList[I].msOver = true;
						TxtList[I].Border.FillColor = J_C_Grey;
						TxtList[I].RdrTbx();
						TxtList[I].DoRender = true;
					}
					// Mouse button Click
					if (h->Event.type == SDL_MOUSEBUTTONDOWN) {
						Index = I;
					}
				}
				else {

					if (TxtList[I].DoRender == true) {
						TxtList[I].msOver = false;
						TxtList[I].Border.FillColor = J_C_White;
						if (Index == I) {
							for (int J = FromLine; J < ToLine; J++) {
								TxtList[J].Border.LineColor = J_C_White;
								TxtList[J].RdrTbx();
							}
							TxtList[I].Border.LineColor = J_C_BtnGrey;
						}
						TxtList[I].RdrTbx();
						TxtList[I].DoRender = false;
					}
				}
				
			}
			char TxtTxt[10];
			sprintf_s(TxtTxt, "I = %d", Index);
			h->EbxPtr[2].New(TxtTxt);
			h->EbxPtr[2].RdrEbx();
		}
	}
}
