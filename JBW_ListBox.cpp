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
	delete[] TextList;
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
	Jbw_Text* NewList = new Jbw_Text[Cnt + 1];

	for (int I = 0; I < Cnt; I++) {
		NewList[I] = TextList[I]; // Copy all current TxtPtrs		
	}
	NewList[Cnt].InitTxt(Jrdr, NewTxt, FrameX + 3, FrameY + 3, FontSize);

	if (Cnt > 0) {
		delete[] TextList;
	}
	TextList = NewList;
	Cnt++;
	RdrLbx();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Clear
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::Clear(void)
{
	delete[] TextList;
	TextList = NULL;
	Cnt = 0;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Create
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::RdrLbx(void)
{	
	SDL_Rect RdrBox = { FrameX, FrameY, FrameW, FrameH };
	SDL_RenderSetViewport(Jrdr, &RdrBox);
	
	// Render Frame of ListBox
	RdrFrame(); 

	// Get number of lines that will fit into the ListBox display
	int Lines = (int)floor(FrameH / (FontSize + 1));
	int FromLine = 0;
	int ToLine = Cnt;
	if (Cnt > Lines) {
		FromLine = Cnt - Lines;
		ToLine = FromLine + Lines;
		SliderBox->RdrFrame(); // Render frame
		SldrBtnUp->RdrBtn(); // Render
		SldrBtnDwn->RdrBtn(); // Render
		
		int Pos = (int)floor(FromLine * (SliderBox->FrameH) / (Cnt)) - Lines;
		Slider->FrameY = SliderBox->FrameY +  Pos; // Set Slider Position
		Slider->FrameH = SliderBox->FrameH - (Slider->FrameY - SliderBox->FrameY) - 1;
		Slider->CreatePts();
		Slider->RdrFrame();
	}

	// Render Text Inside ListBox
	if (TextList != NULL) {
		for (int I = FromLine; I < ToLine; I++) {
			TextList[I].TxtY = FrameY + 3 + (I - FromLine) * (FontSize + 1);
			TextList[I].CreateTexture();
			TextList[I].RdrTxt();
		}
	}

	SDL_RenderPresent(Jrdr); // Render to screen
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER
------------------------------------------------------------------------------------------*/
void Jbw_ListBox::LbxEvent(SDL_Event* e)
{
	//bool Flag = false;
	////If mouse event happened
	//if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
	//	// Get mouse position
	//	int x, y;
	//	SDL_GetMouseState(&x, &y);

	//	// Mouse pointer inside Drpdown Button 
	//	if (x > EditX&& x < EditX + EditW && y > EditY&& y < EditY + EditH)
	//	{
	//		switch (e->type)
	//		{
	//		case SDL_MOUSEMOTION:
	//			Border.LineColor = { 0, 0, 0, 255 };
	//			break;

	//		case SDL_MOUSEBUTTONDOWN:
	//			//	BackColor = { 0, 0, 0, 255 };
	//			Focus = true;
	//			//		SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, &Dp);
	//			break;

	//		case SDL_MOUSEBUTTONUP:
	//			//	BackColor = { 255, 255, 255, 255 };
	//			break;
	//		}
	//	}
	//	else {
	//		Border.LineColor = J_C_Frame;
	//		if (e->type == SDL_MOUSEBUTTONDOWN) {
	//			Focus = false;
	//		}
	//	}
	//}

	//if (Focus == false) {
	//	return;
	//}
	//else if (e->type == SDL_TEXTINPUT) {
	//	Add(e->text.text);
	//	//		RdrEbx();
	//}
	//else if (e->type == SDL_KEYDOWN)
	//{
	//	if (e->key.keysym.sym == SDLK_BACKSPACE) {
	//		BackSpace();
	//		//	RdrEbx();
	//	}
	//	else if (e->key.keysym.sym == SDLK_DELETE) {
	//	}
	//	else if (e->key.keysym.sym) {
	//	}
	//}
	//if (0) {
	//	if (e->type == SDL_USEREVENT) {
	//		e->user.data1;
	//		my_function();
	//		//	Uint32* AAA{ static_cast<Uint32*>(e->user.data1) };
	//		//	void (*A) (void*) = e->type.user.data2;
	//		//	*A();


	//	}
	//}



	RdrLbx();
}