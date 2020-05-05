#include "Jbw_Text.h"

/*---------------------------------------------------------------
	CONSTRUCTOR:
---------------------------------------------------------------*/
Jbw_Text::Jbw_Text(SDL_Renderer* Rdr, std::string NewText, int x, int y, int Fsize)
{
	InitTxt(Rdr, NewText, x, y, Fsize);
}

/*---------------------------------------------------------------
	DESTRUCTOR:
---------------------------------------------------------------*/
Jbw_Text::~Jbw_Text()
{
//	SDL_DestroyTexture(txtImage);// Copy all current TxtPtrs		
								// DANGER DANGER If you delete txtImage like you should with Destructor
								// This does not copy well - Write a copy constructor to ensure new 
								// Memory space is created for stuff inside TxtPtr 
								// THIS WILL become important when I start fixing all my memory leaks.
	Font = NULL;
	txtImage = NULL;
}

/*---------------------------------------------------------------
	FUNCTION: Initialise Text
---------------------------------------------------------------*/
void Jbw_Text::InitTxt(SDL_Renderer* Rdr, std::string NewText, int x, int y, int Fsize)
{
	J_Properties Prop;
	Prop.handles.JbwRdr = Rdr;
	Prop.Caption.assign(NewText);
	Prop.x = x;
	Prop.y = y;
	Prop.Fsize = Fsize;
	InitTxt(&Prop);
}

/*---------------------------------------------------------------
FUNCTION: Initialise Text
---------------------------------------------------------------*/
void Jbw_Text::InitTxt(J_Properties* Prop) 
{
	Id = Prop->Id;
	Tag.assign(Prop->Tag);
	Jrdr = Prop->handles.JbwRdr;
	Text.assign(Prop->Caption);
	TxtX = Prop->x;
	TxtY = Prop->y;
	TxtSize = Prop->Fsize;
	CreateTexture();
}

/*---------------------------------------------------------------
FUNCTION: Create Texture
---------------------------------------------------------------*/
void Jbw_Text::CreateTexture(void) {

	Font = TTF_OpenFont("fonts/arial.ttf", TxtSize); // Load the default font	
	TTF_SetFontHinting(Font, TTF_HINTING_LIGHT); // TTF_HINTING_NORMAL TTF_HINTING_MONO TTF_HINTING_LIGHT

	// Build font Style	
	int FontStyle = 0;
	if (F_Bold == 1) {
		FontStyle = FontStyle | TTF_STYLE_BOLD;
	}
	if (F_Italic == 1) {
		FontStyle = FontStyle | TTF_STYLE_ITALIC;
	}
	if (F_UnderL == 1) {
		FontStyle = FontStyle | TTF_STYLE_UNDERLINE;
	}
	if (F_Strike == 1) {
		FontStyle = FontStyle | TTF_STYLE_STRIKETHROUGH;
	}
	TTF_SetFontStyle(Font, FontStyle);
	SDL_Surface* txtSurf;
	if (Text.empty()) {
		txtSurf = TTF_RenderText_Blended(Font, " ", TxtColor);
	}
	else {
		txtSurf = TTF_RenderText_Blended(Font, Text.c_str(), TxtColor);
	}
	TTF_CloseFont(Font);

	// Free the previous txtImage
	SDL_DestroyTexture(txtImage);
	txtImage = SDL_CreateTextureFromSurface(Jrdr, txtSurf); // Move it from RAM to VRAM -> Graphics card which makes it much faster

	txtClip = { 0, 0, txtSurf->w, txtSurf->h };
	txtBox = { 0, 0 , txtSurf->w, txtSurf->h };

	SDL_FreeSurface(txtSurf); // Free the memory of SDL_Surface
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Text::Add(std::string XtraText)
{
	Text.append(XtraText);
	CreateTexture();
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Text::New(std::string NewText)
{
	Text.assign(NewText);
	CreateTexture();
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Text::Del(void)
{

}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Text::BackSpace(void)
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

/*---------------------------------------------------------------
FUNCTION: SetTxt
---------------------------------------------------------------*/
bool Jbw_Text::SetTxt(std::string  *Var, const char* Val)
{
	bool Flag = false;
	char* Next;
	// Text
	if (Var->compare("Text") == 0) {
		Text.assign(Val);
		Flag = true;
	}
	// TxtSize
	else if (Var->compare("TxtSize") == 0) { //
		TxtSize = (int)strtod(Val, NULL);
		Flag = true;
	}
	// FontStyle Bold
	else if (Var->compare("F_Bold") == 0) { //
		F_Bold = (bool)strtod(Val, NULL);
		Flag = true;
	}
	// FontStyle Italic
	else if (Var->compare("F_Italic") == 0) { //
		F_Italic = (bool)strtod(Val, NULL);
		Flag = true;
	}
	// FontStyle Underline
	else if (Var->compare("F_UnderL") == 0) { //
		F_UnderL = (bool)strtod(Val, NULL);
		Flag = true;
	}
	// FontStyle Strike through
	else if (Var->compare("F_Strike") == 0) { //
		F_Strike = (bool)strtod(Val, NULL);
		Flag = true;
	}
	// Angle
	else if (Var->compare("Angle") == 0) {
		Angle = (int)strtod(Val, NULL);
		Flag = true;
	}
	// Flip
	else if (Var->find("Flip") == 0) {
		if (strcmp(Val, "J_NONE") == 0) {
			Flip = SDL_FLIP_NONE;
			Flag = true;
		}
		else if (strcmp(Val, "J_HOR")) {
			Flip = SDL_FLIP_HORIZONTAL;
			Flag = true;
		}
		else if (strcmp(Val, "J_VER") == 0) {
			Flip = SDL_FLIP_VERTICAL;
			Flag = true;
		}
	}
	// TextColor
	else if (Var->compare("TextColor") == 0) {
		TxtColor.b = (int)strtod(Val, &Next);
		TxtColor.g = (int)strtod(Next, &Next);
		TxtColor.r = (int)strtod(Next, &Next);
		Flag = true;
	}
	CreateTexture();
	return Flag;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Text::RdrTxt(void)
{
	SDL_Rect RdrArea = { TxtX, TxtY, txtBox.w, txtBox.h };
	SDL_RenderSetViewport(Jrdr, &RdrArea);

	SDL_RenderCopyEx(Jrdr, txtImage, &txtClip, &txtBox, Angle, &RotPoint, Flip);
}

/*---------------------------------------------------------------
FUNCTION: Event Handler (Mouse Over Only)
---------------------------------------------------------------*/
void Jbw_Text::TxtEvent(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Mouse is left of the button
		if (x > txtBox.x&& x < txtBox.x + txtBox.w && y > txtBox.y&& y < txtBox.y + txtBox.h)
		{
			// ToolTip
			int a = 0;
		}

	}
}