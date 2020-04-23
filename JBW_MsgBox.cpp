#include "Jbw_MsgBox.h"

Jbw_MsgBox::Jbw_MsgBox(std::string Title, std::string Msg, J_MsgAck InType, int x, int y, int w, int h)
{
	Window_w = w;
	Window_h = h;
	Type = InType;

	Font = TTF_OpenFont("fonts/arial.ttf", 12);
	TTF_SetFontHinting(Font, TTF_HINTING_LIGHT); // TTF_HINTING_NORMAL TTF_HINTING_MONO TTF_HINTING_LIGHT

	// Get Window Size
	Parser(Title, false);
	Parser(Msg, false);

	//Create User Window
	MsgWindow = SDL_CreateWindow(Title.c_str(), x, y, Window_w, Window_h, SDL_WINDOW_OPENGL
		| SDL_WINDOW_BORDERLESS);
	// Create renderer for User window
	Render = SDL_CreateRenderer(MsgWindow, -1, SDL_RENDERER_ACCELERATED);

	// Create own Border
	Border.w = Window_w; Border.h = Window_h;

	// Create Header
	edHeader = new Jbw_EditBox(Render, J_EDIT, 0, 0, Window_w, 18);
	edHeader->Set(Title.c_str(), "Align", J_CENTRE, "FontSize", 12);

	SDL_SetRenderDrawColor(Render, 230, 230, 230, 255);
	SDL_RenderClear(Render);

	RenderBox();
	Parser(Msg, true);
}
Jbw_MsgBox::~Jbw_MsgBox()
{
	SDL_DestroyWindow(MsgWindow);
	SDL_DestroyRenderer(Render);
	SDL_DestroyTexture(txtImage);
	TTF_CloseFont(Font);

	delete edHeader;
	delete btnAck;
	delete btnNo;

	MsgWindow = NULL;
	Render = NULL;
	txtImage = NULL;
	edHeader = NULL;
	btnAck = NULL;
	btnNo = NULL;
}


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
}

void Jbw_MsgBox::RenderMsg(std::string Msg, int Line, bool DoRender) {
	
	txtSurf = TTF_RenderText_Blended(Font, Msg.c_str(), { 0, 0, 0, 255 });

	txtBox.x = 20; //(Window_w - txtSurf->w) / 2;
	txtBox.y = 30 + Line * 12;
	txtBox.w = txtSurf->w;
	txtBox.h = txtSurf->h;
	if (DoRender == true) {
		txtImage = SDL_CreateTextureFromSurface(Render, txtSurf);
		SDL_RenderCopyEx(Render, txtImage, 0, &txtBox, 0, 0, SDL_FLIP_NONE);
		SDL_RenderPresent(Render);
		SDL_DestroyTexture(txtImage);
	}
	else { // DON'T RENDER just Set MsgBox to correct size for all text
		if (Window_w < txtBox.w + 40) {
			Window_w = txtBox.w + 40;
		}
	}

	SDL_FreeSurface(txtSurf);
}

void Jbw_MsgBox::RenderBox(void) {
	// Outside part of creating Border
	SDL_SetRenderDrawColor(Render, 180, 180, 180, 255);
	SDL_RenderFillRect(Render, &Border);
	
	// Inside part of creating Border
	Border.x = Border.x + 1;
	Border.y = Border.y + 1;
	Border.w = Border.w -2;
	Border.h = Border.h -2;
	SDL_SetRenderDrawColor(Render, 230, 230, 230, 255);
	SDL_RenderFillRect(Render, &Border);
	SDL_RenderFillRect(Render, &Border);

	// Set Header Text / TITLE
	//edHeader->BackColor = 200;
	//edHeader->FrameColor = 180;
	//edHeader->Render();

	// Create Buttons
	int Btn_w = 40, Btn_h = 16, BtnSpace = 40, Btn_y = Window_h - 25;
	int BtnYes_x = Window_w - 60; //(Window_w - Btn_w) / 2;
	if (Type == J_YESNO) {
		int BtnYes_x = Window_w - 120; // (Window_w - 2 * Btn_w ) / 2 - BtnSpace/2;
		int BtnNo_x = Window_w - 60; //BtnYes_x + BtnSpace + Btn_w;
		btnAck = new Jbw_EditBox(Render, J_EDIT, BtnYes_x, Btn_y, Btn_w, Btn_h);
		btnAck->BackColor = { 200, 200, 200, 255 };
		btnAck->FrameColor = { 180, 180, 180, 255 }; 
		btnAck->Set("Yes", "Align", J_CENTRE, "FontSize", 12);

		btnNo = new Jbw_EditBox(Render, J_EDIT, BtnNo_x, Btn_y, Btn_w, Btn_h);
		btnNo->BackColor = { 200, 200, 200, 255 };
		btnNo->FrameColor = { 180, 180, 180, 255 };
		btnNo->Set("No", "Align", J_CENTRE, "FontSize", 12);
		btnNo->Render();
	}
	else {
		btnAck = new Jbw_EditBox(Render, J_EDIT, BtnYes_x, Btn_y, Btn_w, Btn_h);
		btnAck->BackColor = { 200, 200, 200, 255 };
		btnAck->FrameColor = { 180, 180, 180, 255 };
		if (Type == J_OK) {
			btnAck->Set("Okay", "Align", J_CENTRE, "FontSize", 12);
		}
		else{
			btnAck->Set("Yes", "Align", J_CENTRE, "FontSize", 12);
		}
	}
	btnAck->Render();

	SDL_RenderPresent(Render);
}

