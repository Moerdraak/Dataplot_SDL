#include "Jbw_EditBox.h"


Jbw_EditBox::Jbw_EditBox(SDL_Renderer* Rdr, J_Type Type, int x, int y, int w, int h)
{
	Box.x = x + 1; Box.y = y + 1; Box.w = w - 2; Box.h = h - 2; // Creates a border of thickness 1
	Frame.x = x; Frame.y = y; Frame.w = w; Frame.h = h;
	//TxtType = Type;
	Trdr = Rdr;
	Text = ""; // Give default text otherwise it crashes
}

Jbw_EditBox::~Jbw_EditBox() {
	SDL_DestroyTexture(txtImage);
}

/*--------------------------------------------------------------------
	FUNCTION: Render
--------------------------------------------------------------------*/
void Jbw_EditBox::FitText(void)
{
	/* Cutting Text To Size*/
	int Clip_W = 0, Clip_H = 0;
	Xo = Box.x + 1;	
	Yo = Box.y + (Box.h - txtBox.h) / 2;

	ActTxtW = txtBox.w;
	if (txtBox.w > Box.w) {
		Clip_W = Box.w - 2; // If text is wider than box
	}
	else {
		Clip_W = txtBox.w; // If text is equal or narrower than box
	}
	if (txtBox.h > Box.h) {
		Clip_H = Box.h;      // If text is larger than box
	}
	else {
		Clip_H = txtBox.h;  // If text is smaller than box
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
		if (txtBox.w < Box.w) { // If text is longer than box don't centre but keep LEFT aligned.
			if (Angle == 90) {
				txtBox.x += txtBox.h;
				txtBox.y += (Box.w - txtBox.w) / 2;
			}
			else if (Angle == -90) {
				txtBox.x -= 2;   //Box.x - txtBox.w + txtBox.h;
				txtBox.y += txtBox.w + (Box.w - txtBox.w) / 2;
			}
			else {
				txtBox = { Xo + (Box.w - txtBox.w) / 2, Yo, Clip_W, Clip_H };
			}
		}
	}
	else if (Align == J_RIGHT) { // RIGHT ALIGN TEXT
		if (txtBox.w < Box.w) { // If text is longer than box don't right align but keep LEFT aligned.
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
}

/*--------------------------------------------------------------------
	FUNCTION: Render
--------------------------------------------------------------------*/
void Jbw_EditBox::Render(void)
{
	// If Editbox is vertical
	if (Angle == 90 || Angle == -90) {
		SDL_Rect Tmp = Frame;
		Frame.w = Tmp.h;
		Frame.h = Tmp.w;

		Tmp = Box;
		Box.w = Tmp.h;
		Box.h = Tmp.w;
	}
	SDL_SetRenderDrawColor(Trdr, FrameColor.b, FrameColor.g, FrameColor.r, FrameColor.a);
	SDL_RenderFillRect(Trdr, &Frame);

	// Create White inside of Edit box
	SDL_SetRenderDrawColor(Trdr, BackColor.b, BackColor.g, BackColor.r, BackColor.a);
	SDL_RenderFillRect(Trdr, &Box);

	SDL_RenderCopyEx(Trdr, txtImage, &txtClip, &txtBox, Angle, &RotPoint, Flip);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   SetX
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Jbw_EditBox::Set(std::string  Var, const char * Val)
{
	char* Next;
	// Text
	if (Var.compare("Text") == 0) { 
		Text.assign(Val);
	}
	// Box
	else if (Var.compare("Box") == 0) {
		Box.x = (int)strtod(Val, &Next);
		Box.y = (int)strtod(Next, &Next);
		Box.w = (int)strtod(Next, &Next);
		Box.h = (int)strtod(Next, &Next);
	}
	// FontSize
	else if (Var.compare("FontSize") == 0) { //
		FontSize = (int)strtod(Val, NULL);
	}
	// FontStyle Bold
	else if (Var.compare("F_Bold") == 0) { //
		F_Bold = (bool)strtod(Val, NULL);
	}
	// FontStyle Italic
	else if (Var.compare("F_Italic") == 0) { //
		F_Italic = (bool)strtod(Val, NULL);
	}
	// FontStyle Underline
	else if (Var.compare("F_UnderL") == 0) { //
		F_UnderL = (bool)strtod(Val, NULL);
	}
	// FontStyle Strike through
	else if (Var.compare("F_Strike") == 0) { //
		F_Strike = (bool)strtod(Val, NULL);
	}
	// TxtType
	//else if (Var.compare("TxtType") == 0) {
	//	if (strcmp(Val, "J_TEXT")) {
	//		TxtType = J_TEXT;
	//	}
	//	else if (strcmp(Val, "J_EDIT")) {
	//		TxtType = J_EDIT;
	//	}
	//}
	// Align
	else if (Var.compare("Align") == 0) {
		if (strcmp(Val, "J_LEFT") == 0) {
			Align = J_LEFT;
		}
		else if (strcmp(Val, "J_CENTRE") == 0) {
			Align = J_CENTRE;
		}
		else if (strcmp(Val, "J_RIGHT") == 0) {
			Align = J_RIGHT;
		}
	}
	else if (Var.compare("Angle") == 0) {
		Angle = (int)strtod(Val, NULL);
	}
	else if (Var.find("Flip") == 0) {
		if (strcmp(Val, "J_NONE") == 0) {
			Flip = SDL_FLIP_NONE;
		}
		else if (strcmp(Val, "J_HOR")) {
			Flip = SDL_FLIP_HORIZONTAL;
		}
		else if (strcmp(Val, "J_VER") == 0) {
			Flip = SDL_FLIP_VERTICAL;
		}
	}
	else if (Var.compare("TextColor") == 0) {
		FontColor.b = (int)strtod(Val, &Next);
		FontColor.g = (int)strtod(Next, &Next);
		FontColor.r = (int)strtod(Next, &Next);
	}
	else if (Var.compare("BackColor") == 0) {
		BackColor.b = (int)strtod(Val, &Next);
		BackColor.g = (int)strtod(Next, &Next);
		BackColor.r = (int)strtod(Next, &Next);
	}
	else if (Var.compare("FrameColor") == 0) {
		FrameColor.b = (int)strtod(Val, &Next);
		FrameColor.g = (int)strtod(Next, &Next);
		FrameColor.r = (int)strtod(Next, &Next);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   TextSet For setting text properties on one line
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void Jbw_EditBox::Set(std::string NewText, const char* Var1, int Val1, const char* Var2, int Val2,
//	const char* Var3, int Val3, const char* Var4, int Val4,
//	const char* Var5, int Val5, const char* Var6, int Val6)
//{
//	SetSub(Var1, Val1);
//	SetSub(Var2, Val2);
//	SetSub(Var3, Val3);
//	SetSub(Var4, Val4);
//	SetSub(Var5, Val5);
//	SetSub(Var6, Val6);
//	if (NewText.length() == 0) {
//		NewText.assign(" ");
//	}
//	New(NewText);
//
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Private function used by TextSet (For setting text properties on one line)
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void Jbw_EditBox::SetSub(const char* Var, int Val) {
//	if (strcmp(Var, "x") == 0) {
//		Box.x = Val;
//	}
//	if (strcmp(Var, "y") == 0) {
//		Box.y = Val;
//	}
//	if (strcmp(Var, "w") == 0) {
//		Box.w = Val;
//	}
//	if (strcmp(Var, "h") == 0) {
//		Box.h = Val;
//	}
//	if (strcmp(Var, "Align") == 0) {
//		Align = (J_TxtAlign)Val;
//	}
//	if (strcmp(Var, "FontSize") == 0) {
//		FontSize = Val;
//	}
//	if (strcmp(Var, "Angle") == 0) {
//		Angle = Val;
//	}
//	//	if (strcmp(Var, "TextColor") == 0) {
//	//		TxtObj->TextColor = Val;
//	//	}
//	if (strcmp(Var, "Text") == 0) {
//		Text = Val;
//	}
//}
void Jbw_EditBox::Event(SDL_Event* e)
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
				FrameColor = { 0, 0, 0, 255 };

				break;

			case SDL_MOUSEBUTTONDOWN:
				BackColor = { 0, 0, 0, 255 };

				break;

			case SDL_MOUSEBUTTONUP:
				BackColor = { 255, 255, 255, 255 };

				break;
			}
		}
		else {
			FrameColor = { 150, 150, 150, 255 };

		}
	}
}

