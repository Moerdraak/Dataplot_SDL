#include "Jbw_TextBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_TextBox::Jbw_TextBox(Jbw_Handles* handles, std::string TxtString, int x, int y, int w, int h, int Fsize)
{
	Jhandle = handles;
	Obj.x = x;
	Obj.y = y;
	Obj.w = w;
	Obj.h = h;

	Text.assign(TxtString);
	TxtSize = Fsize;	
	CreateTbx();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: InitTbx
------------------------------------------------------------------------------------------*/
void Jbw_TextBox::InitTbx(Jbw_Handles* handles, std::string TxtString, int x, int y, int w, int h, int Fsize)
{
	Jhandle = handles;
	Obj.x = x;
	Obj.y = y;
	Obj.w = w;
	Obj.h = h;

	Text.assign(TxtString);
	TxtSize = Fsize;
	CreateTbx();

}
/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_TextBox::~Jbw_TextBox() 
{
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CreateTbx
------------------------------------------------------------------------------------------*/ 
void Jbw_TextBox::CreateTbx(void)
{
	if (Border == NULL) {

		Border = new Jbw_Frame(Jhandle, Obj.x, Obj.y, Obj.w, Obj.h, false);
	}
	else {
		Border->Obj = Obj;
		Border->CreateFrame();
	}
	CreateTexture();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: SetTbx
------------------------------------------------------------------------------------------*/
void Jbw_TextBox::SetTbx(std::string NewText, int FontSize)
{
	Text.assign(NewText);

	if (FontSize != -1) {
		TxtSize = FontSize;
	}
	CreateTbx();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: SetTbx
------------------------------------------------------------------------------------------*/
void Jbw_TextBox::SetTbx(SDL_Rect Area)
{
	Obj = Area;
	CreateTbx();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: SetTbx
------------------------------------------------------------------------------------------*/
void Jbw_TextBox::SetTbx(SDL_Rect Area, std::string NewText, int FontSize)
{
	Obj = Area;
	Text.assign(NewText);

	if (FontSize != -1) {
		TxtSize = FontSize;
	}
	CreateTbx();
}



/*-----------------------------------------------------------------------------------------
	FUNCTION: FitText
------------------------------------------------------------------------------------------*/
void Jbw_TextBox::FitText(void)
{
	/* Cutting Text To Size*/
	int Clip_W = 0, Clip_H = 0;

	Obj.x = 2;
	Obj.y = (Obj.h - txtBox.h) / 2 + 1; // To +1 OR Not To +1

	int ActTxtW = txtBox.w;
	if (txtBox.w > Obj.w) {
		Clip_W = Obj.w - 2; // If text is wider than box
	}
	else {
		Clip_W = txtBox.w; // If text is equal or narrower than box
	}
	if (txtBox.h > Obj.h) {
		Clip_H = Obj.h;      // If text is larger than box
	}
	else {
		Clip_H = txtBox.h;  // If text is smaller than box
	}
	txtClip = { 0, 0, Clip_W, Clip_H };
	txtBox = { Obj.x, Obj.y , Clip_W, Clip_H };

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
		if (txtBox.w < Obj.w) { // If text is longer than box don't centre but keep LEFT aligned.
			if (Angle == 90) {
				txtBox.x += txtBox.h;
				txtBox.y += (Obj.w - txtBox.w) / 2;
			}
			else if (Angle == -90) {
				txtBox.x -= 2;   //Box.x - txtBox.w + txtBox.h;
				txtBox.y += txtBox.w + (Obj.w - txtBox.w) / 2;
			}
			else {
				txtBox = { Obj.x - 1 + (Obj.w - txtBox.w) / 2, Obj.y, Clip_W, Clip_H };
			}
		}
	}
	else if (Align == J_RIGHT) { // RIGHT ALIGN TEXT
		if (txtBox.w < Obj.w) { // If text is longer than box don't right align but keep LEFT aligned.
			if (Angle == 90) {
				txtBox.x += txtBox.h;   //Box.x - txtBox.w + txtBox.h;
				txtBox.y += (Obj.w - Clip_W);  //Box.y + Obj.w;
			}
			else if (Angle == -90) {
				txtBox.x -= 2;   //Box.x - txtBox.w + txtBox.h;
				txtBox.y += Obj.w;
			}
			else {
				txtBox = { Obj.x + (Obj.w - Clip_W), Obj.y, Clip_W, Clip_H };
			}
		}
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION: BackColor
------------------------------------------------------------------------------------------*/
void Jbw_TextBox::BackColor(SDL_Color Color)
{
	Border->FillColor = Color;
}

/*-----------------------------------------------------------------------------------------
FUNCTION: BorderColor
------------------------------------------------------------------------------------------*/
void Jbw_TextBox::BorderColor(SDL_Color Color)
{
	Border->LineColor = Color;
}

/*-----------------------------------------------------------------------------------------
FUNCTION: Set
------------------------------------------------------------------------------------------*/
bool Jbw_TextBox::SetTbx(std::string* Var, const char* Val)
{
	bool Flag = false;
	char* Next;

	// Text
	if (Var->compare("Text") == 0) {
		Text.assign(Val);
	}
	// Box
	else if (Var->compare("Box") == 0) {
		Obj.x = (int)strtod(Val, &Next);
		Obj.y = (int)strtod(Next, &Next);
		Obj.w = (int)strtod(Next, &Next);
		Obj.h = (int)strtod(Next, &Next);
		Flag = true;
	}
	// Align
	else if (Var->compare("Align") == 0) {
		if (strcmp(Val, "J_LEFT") == 0) {
			Align = J_LEFT;
			Flag = true;
		}
		else if (strcmp(Val, "J_CENTRE") == 0) {
			Align = J_CENTRE;
			Flag = true;
		}
		else if (strcmp(Val, "J_RIGHT") == 0) {
			Align = J_RIGHT;
			Flag = true;
		}
	}
	//	BackColor
	else if (Var->compare("BackColor") == 0) {
		Border->FillColor.b = (int)strtod(Val, &Next);
		Border->FillColor.g = (int)strtod(Next, &Next);
		Border->FillColor.r = (int)strtod(Next, &Next);
		Flag = true;
	}
	else if (Var->compare("LineColor") == 0) {
		Border->LineColor.b = (int)strtod(Val, &Next);
		Border->LineColor.g = (int)strtod(Next, &Next);
		Border->LineColor.r = (int)strtod(Next, &Next);
		Flag = true;
	}
	return Flag;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrTbx
------------------------------------------------------------------------------------------*/
void Jbw_TextBox::RdrTbx()
{
	// If Tbxbox is vertical
	if (Angle == 90 || Angle == -90) {
		int Tmp = Border->Obj.w;
		Border->Obj.w = Border->Obj.h;
		Border->Obj.h = Tmp;
	}

	// Check current To Fill or Not Too Fill the Border
	if (FillOn == true) {
		Border->Fill = true; // Fill frame with BackColor
	}
	else {
		Border->Fill = false;
	}
	// Size and Set Frame for Rendering
	if (FrameOn == true) {
		Border->RdrFrame(); // Render frame
	}

	// Set Viewport area
	SDL_Rect Viewport = { Border->Obj.x, Border->Obj.y, Border->Obj.w, Border->Obj.h };
	SDL_RenderSetViewport(Jhandle->Rdr, &Viewport);

	// Size and Set Text for Rendering
	FitText();
	SDL_RenderCopyEx(Jhandle->Rdr, txtImage, &txtClip, &txtBox, Angle, &RotPoint, Flip);

	// Render to screen
	SDL_RenderPresent(Jhandle->Rdr);
}

