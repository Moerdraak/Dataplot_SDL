#include "Jbw_MsgBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/

Jbw_MsgBox::Jbw_MsgBox(std::string Title, std::string Msg, J_Type OkYesNo, int x, int y, int w, int h)
{
	//Jhandle = new Jbw_Handles;

	//Window_w = w;
	//Window_h = h;
	//MbxType = OkYesNo;

	//Font = TTF_OpenFont("fonts/arial.ttf", 12);
	//TTF_SetFontHinting(Font, TTF_HINTING_LIGHT); // TTF_HINTING_NORMAL TTF_HINTING_MONO TTF_HINTING_LIGHT

	//// Get Window Size
	//Parser(Title, false);
	//Parser(Msg, false);

	//// Create User Window
	//Jhandle->JbwGui = SDL_CreateWindow("MsgBox", x, y, Window_w, Window_h, SDL_WINDOW_OPENGL
	//	| SDL_WINDOW_BORDERLESS);

	//// Create renderer for User window
	//Jhandle->Rdr = SDL_CreateRenderer(Jhandle->JbwGui, -1, SDL_RENDERER_ACCELERATED);

	//// Create Border
	////FrameW = Window_w;
	////FrameH = Window_h;

	//// Create Header
	////J_Properties Prop;
	////Prop.handles.Rdr = Jrdr;
	////Prop.w = Window_w;
	////Prop.h = 18;
	//Header = new Jbw_EditBox(Jhandle, x, y, Window_w, 18);
	//Header->Text.assign(Title);

	//RenderBox();

	//// Set Viewport for Message	
	//SDL_Rect Window = { 0, 0, Window_w, Window_h };
	//SDL_RenderSetViewport(Jhandle->Rdr, &Window);
	//Parser(Msg, true);
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/

Jbw_MsgBox::~Jbw_MsgBox()
{
	Close();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Close
------------------------------------------------------------------------------------------*/
void Jbw_MsgBox::Close(void)
{
	if (btnNo != NULL) {
		delete btnNo; btnNo = NULL;
	}
	delete btnAck; btnAck = NULL;
	delete Header; Header = NULL;

	SDL_DestroyWindow(Jhandle->JbwGui); Jhandle->JbwGui = NULL;
	SDL_DestroyRenderer(Jhandle->Rdr); Jhandle->Rdr = NULL;
	SDL_DestroyTexture(txtImage); txtImage = NULL;
	TTF_CloseFont(Font); Font = NULL;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Parser
------------------------------------------------------------------------------------------*/

void Jbw_MsgBox::Parser(std::string Txt, bool DoRender) {
	int Cnt = 0;
	size_t Start = 0, Pos = 0;
	while (Pos < Txt.length()) { // Not good Need to find exact method
		Pos = Txt.find('\n', Start);
		RenderMsg(Txt.substr(Start, Pos - Start), Cnt++, DoRender);
		Start = Pos + 1;
	}
	if (Window_h < 110 + (Cnt - 4) * 12) {
		Window_h = 110 + (Cnt - 4) * 12;
	}
	SDL_RenderPresent(Jhandle->Rdr);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RenderMsg
------------------------------------------------------------------------------------------*/
void Jbw_MsgBox::RenderMsg(std::string Msg, int Line, bool DoRender) {
	
	txtSurf = TTF_RenderText_Blended(Font, Msg.c_str(), { 0, 0, 0, 255 });
	SDL_Rect txtBox;
	txtBox.x = 10; 
	txtBox.y = 30 + Line * 12;
	txtBox.w = txtSurf->w;
	txtBox.h = txtSurf->h;
	if (DoRender == true) {
		txtImage = SDL_CreateTextureFromSurface(Jhandle->Rdr, txtSurf);
		SDL_RenderCopyEx(Jhandle->Rdr, txtImage, 0, &txtBox, 0, 0, SDL_FLIP_NONE);
		SDL_DestroyTexture(txtImage);
	}
	else { // DON'T RENDER just Set MsgBox to correct size for all text
		if (Window_w < txtBox.w + 40) {
			Window_w = txtBox.w + 40;
		}
	}

	SDL_FreeSurface(txtSurf);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RenderBox
------------------------------------------------------------------------------------------*/
void Jbw_MsgBox::RenderBox(void) {
	
	SDL_SetRenderDrawColor(Jhandle->Rdr, 230, 230, 230, 255);
	SDL_RenderClear(Jhandle->Rdr);

	// Render Frame
	MsgFrame->RdrFrame();

	// Render Header
	Header->Border->LineColor = J_C_Frame;
	Header->Border->FillColor = J_C_Frame;
	Header->Align = J_CENTRE;
	Header->CreateTexture();
	Header->RdrEbx();

	// Create Buttons
	int Btn_w = 40, Btn_h = 16, BtnSpace = 20, Btn_y = Window_h - 25;

	if (MbxType == J_YESNO) {
		// YES Button
		btnAck = new Jbw_Button(Jhandle, Window_w - 100, Btn_y, Btn_w, Btn_h, "Yes", 12);
		// NO Button
		btnNo = new Jbw_Button(Jhandle, Window_w - 50, Btn_y, Btn_w, Btn_h, "No", 12);
		btnNo->RdrBtn();
	}
	else {
		if (MbxType == J_OK) {
			btnAck = new Jbw_Button(Jhandle, Window_w - 50, Btn_y, Btn_w, Btn_h, "Okay", 12);
		}
		else{
			btnAck = new Jbw_Button(Jhandle, Window_w - 50, Btn_y, Btn_w, Btn_h, "Yes", 12);
		}
	}
	btnAck->RdrBtn();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MsgBox
------------------------------------------------------------------------------------------*/
J_Type Jbw_MsgBox::MsgBox(std::string Title, std::string Msg, J_Type OkYesNo,
	int x, int y, int w , int h )
{
	J_Type Answer = J_NULL;
	Jhandle = new Jbw_Handles;
	Window_w = w;
	Window_h = h;
	MbxType = OkYesNo;

	Font = TTF_OpenFont("fonts/arial.ttf", 12);
	TTF_SetFontHinting(Font, TTF_HINTING_LIGHT); // TTF_HINTING_NORMAL TTF_HINTING_MONO TTF_HINTING_LIGHT

	// Get Window Size
	Parser(Title, false);
	Parser(Msg, false);

	// Create User Window
	Jhandle->JbwGui = SDL_CreateWindow("MsgBox", x, y, Window_w, Window_h, SDL_WINDOW_OPENGL
		| SDL_WINDOW_BORDERLESS);

	// Create renderer for User window
	Jhandle->Rdr = SDL_CreateRenderer(Jhandle->JbwGui, -1, SDL_RENDERER_ACCELERATED);

	// Create Border
	MsgFrame = new Jbw_Frame(Jhandle, 0, 0, Window_w, Window_h, true);
	MsgFrame->LineColor = { 180, 180, 180, 255 };
	MsgFrame->FillColor = J_C_Window;
	MsgFrame->CreatePts();

	Header = new Jbw_EditBox(Jhandle, 0, 0, Window_w, 18);
	Header->Text.assign(Title);

	RenderBox();

	// Set Viewport for Message	
	SDL_Rect Window = { 0, 0, Window_w, Window_h };
	SDL_RenderSetViewport(Jhandle->Rdr, &Window);
	Parser(Msg, true);
	
	int Flag = false;

	while (SDL_WaitEvent(&Jhandle->Event) != 0) {

		// Check When Buttons are Clicked
		if (btnAck->BtnEvent(Jhandle) == J_BTN_CLICK) {
			Answer = J_YES;
			break;
		}
		if (btnNo != NULL) {
			if (btnNo->BtnEvent(Jhandle) == J_BTN_CLICK) {
				Answer = J_NO;
				break;
			}
		}
	}
	Close();
	return Answer;
}