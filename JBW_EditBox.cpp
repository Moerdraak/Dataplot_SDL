#include "JBW_EditBox.h"


JBW_EditBox::JBW_EditBox(SDL_Renderer* Render, J_Type Type, int x, int y, int w, int h)
{
	Box.x = x + 1; Box.y = y + 1; Box.w = w - 2; Box.h = h - 2; // Creates a border of thickness 1
	Frame.x = x; Frame.y = y; Frame.w = w; Frame.h = h;
	Font = TTF_OpenFont("fonts/arial.ttf", FontSize); // Load the default font
	TxtType = Type;
	Renderer = Render;
}

JBW_EditBox::~JBW_EditBox() {
	SDL_DestroyTexture(txtImage);
	TTF_CloseFont(Font);

	Renderer = NULL; // SDL_DestroyRenderer(Renderer); I don't create it so I don't destroy it
	Font = NULL;
}

void JBW_EditBox::CreateTexture(void) {
	Font = TTF_OpenFont("fonts/arial.ttf", FontSize); // Load the default font

	
	TTF_SetFontHinting(Font, TTF_HINTING_LIGHT); // TTF_HINTING_NORMAL TTF_HINTING_MONO TTF_HINTING_LIGHT
	SDL_Surface* txtSurf = TTF_RenderText_Blended(Font, Text.c_str(), TextColor); 

	/*For each group of quality and functions you find “Text”, “UTF8”, “UNICODE” and “Glyph” in 
	the encoding part of the functions name right after “TTF_Render”. “Text”, “UTF8” and “UNICODE” 
	are three different types of encoding of the text. “Text” corresponds to Latin1 encoding, 
	“UTF8” to UTF-8 encoding and “UNICODE” to Unicode encoding. Which type to choose depends on 
	what type of characters (e.g. Cyrillic letters, Latin characters, Chinese characters) you are going to use. 
	If you are unsure which of these functions to use, go with the “UNICODE” version.*/
	
	// Free the previous txtImage
	SDL_DestroyTexture(txtImage); 
	txtImage = SDL_CreateTextureFromSurface(Renderer, txtSurf); // Move it from RAM to VRAM -> Graphics card which makes it much faster

	/* Cutting Text To Size*/
	int Clip_W = 0, Clip_H = 0, Xo = 0, Yo = 0;	Xo = Box.x + 1;	Yo = Box.y + (Box.h - txtSurf->h) / 2;
	ActTxtW = txtSurf->w;
	if (txtSurf->w > Box.w) {
		Clip_W = Box.w - 2; // If text is wider than box
	}
	else {
		Clip_W = txtSurf->w; // If text is equal or narrower than box
	}
	if (txtSurf->h > Box.h) {
		Clip_H = Box.h;      // If text is larger than box
	}
	else {
		Clip_H = txtSurf->h;  // If text is smaller than box
	}
	txtClip = { 0, 0, Clip_W, Clip_H };
	txtBox = { Xo, Yo , Clip_W, Clip_H };

	if (Align == J_LEFT) { // CENTRE ALIGN TEXT
		if (Angle == 90) {
			txtBox.x += txtBox.h;   //Box.x - txtBox.w + txtBox.h;
		}
		else if (Angle == -90) {
			txtBox.x -= 2;   //Box.x - txtBox.w + txtBox.h;
			txtBox.y += Clip_W + 2;
		}
	}
	else if (Align == J_CENTRE) { // CENTRE ALIGN TEXT
		if (txtSurf->w < Box.w) { // If text is longer than box don't centre but keep LEFT aligned.
			if (Angle == 90) {
				txtBox.x += txtBox.h;
				txtBox.y += (Box.w - txtSurf->w) / 2;
			}
			else if (Angle == -90) {
				txtBox.x -= 2;   //Box.x - txtBox.w + txtBox.h;
				txtBox.y += txtSurf->w + (Box.w - txtSurf->w) / 2;
			}
			else {
				txtBox = { Xo + (Box.w - txtSurf->w) / 2, Yo, Clip_W, Clip_H };
			}
		}
	}
	else if (Align == J_RIGHT) { // RIGHT ALIGN TEXT
		if (txtSurf->w < Box.w) { // If text is longer than box don't right align but keep LEFT aligned.
			if (Angle == 90) {
				txtBox.x += txtBox.h;   //Box.x - txtBox.w + txtBox.h;
				txtBox.y += (Box.w - Clip_W);  //Box.y + Box.w;
			}
			else if (Angle == -90) {
				txtBox.x -= 2;   //Box.x - txtBox.w + txtBox.h;
				txtBox.y += Box.w;
			}
			else {
				txtBox = { Xo + (Box.w - Clip_W), Yo, Clip_W, Clip_H };
			}
		}
	}
	SDL_FreeSurface(txtSurf); // Free the memory of SDL_Surface
}

void JBW_EditBox::Render(void)
{
	// Create Grey Border around Edit box 
	if (TxtType == J_EDIT) {

		if (Angle == 90 || Angle == -90) {
			SDL_Rect Tmp = Frame;
			Frame.w = Tmp.h;
			Frame.h = Tmp.w;

			Tmp = Box;
			Box.w = Tmp.h;
			Box.h = Tmp.w;
		}
		SDL_SetRenderDrawColor(Renderer, FrameColor, FrameColor, FrameColor, 255);
		SDL_RenderFillRect(Renderer, &Frame);

		// Create White inside of Edit box
		SDL_SetRenderDrawColor(Renderer, BackColor, BackColor, BackColor, 255);
		SDL_RenderFillRect(Renderer, &Box);
	}

	SDL_RenderCopyEx(Renderer, txtImage, &txtClip, &txtBox, Angle, &RotPoint, Flip);
}

void JBW_EditBox::Add(std::string XtraText)
{
	Text.append(XtraText);
	CreateTexture();
	//	Render();
}
void JBW_EditBox::New(std::string NewText) {
	Text.assign(NewText);
	CreateTexture();
}

void JBW_EditBox::Del(void)
{

}
void JBW_EditBox::BackSpace(void)
{
	if (Text.length() > 1) {
		Text.pop_back();
		CreateTexture();
	}
	else if (Text.length() > 0) {
		Text.assign(" ");
		CreateTexture();
		Text.clear();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   TextSet For setting text properties on one line
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void JBW_EditBox::Set(std::string NewText, const char* Var1, int Val1, const char* Var2, int Val2,
	const char* Var3, int Val3, const char* Var4, int Val4,
	const char* Var5, int Val5, const char* Var6, int Val6)
{
	SetSub(Var1, Val1);
	SetSub(Var2, Val2);
	SetSub(Var3, Val3);
	SetSub(Var4, Val4);
	SetSub(Var5, Val5);
	SetSub(Var6, Val6);
	if (NewText.length() == 0) {
		NewText.assign(" ");
	}
	New(NewText);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Private function used by TextSet (For setting text properties on one line)
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void JBW_EditBox::SetSub(const char* Var, int Val) {
	if (strcmp(Var, "x") == 0) {
		Box.x = Val;
	}
	if (strcmp(Var, "y") == 0) {
		Box.y = Val;
	}
	if (strcmp(Var, "w") == 0) {
		Box.w = Val;
	}
	if (strcmp(Var, "h") == 0) {
		Box.h = Val;
	}
	if (strcmp(Var, "Align") == 0) {
		Align = (J_TxtAlign)Val;
	}
	if (strcmp(Var, "FontSize") == 0) {
		FontSize = Val;
	}
	if (strcmp(Var, "Angle") == 0) {
		Angle = Val;
	}
	//	if (strcmp(Var, "TextColor") == 0) {
	//		TxtObj->TextColor = Val;
	//	}
	if (strcmp(Var, "Text") == 0) {
		Text = Val;
	}
}
void JBW_EditBox::Event(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Mouse is left of the button
		if (x > Box.x&& x < Box.x + Box.w && y > Box.y&& y < Box.y + Box.h)
		{
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				FrameColor = 0;

				break;

			case SDL_MOUSEBUTTONDOWN:
				BackColor = 0;

				break;

			case SDL_MOUSEBUTTONUP:
				BackColor = 255;

				break;
			}
		}
		else {
			FrameColor = 150;

		}
	}
}

