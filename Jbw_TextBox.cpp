#include "Jbw_TextBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_TextBox::Jbw_TextBox(Jbw_Handles* handles, std::string Text, int x, int y, int w, int h, int Fsize)
{
	Jhandle = handles;
	Text.assign(Text);
	TbxX = x + 1; 
	TbxY = y + 1; 
	TbxW = w - 2; 
	TbxH = h - 2;

	Border = new Jbw_Frame(handles, x, y, w, h, false);
	TxtSize = Fsize;
	CreateTexture();
}

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
//Jbw_TextBox::Jbw_TextBox(J_Properties* Prop)
//{
//	InitTbx(Prop);
//}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_TextBox::~Jbw_TextBox() {

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: InitTbx
------------------------------------------------------------------------------------------*/
void Jbw_TextBox::InitTbx(Jbw_Handles* handles, std::string Text, int x, int y, int w, int h, int Fsize)
{
	Jhandle = handles;
	Text.assign(Text);
	TbxX = x + 1;
	TbxY = y + 1;
	TbxW = w - 2;
	TbxH = h - 2;

	Border = new Jbw_Frame(handles, x, y, w, h, false);
	TxtSize = Fsize;
	CreateTexture();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: FitText
------------------------------------------------------------------------------------------*/
void Jbw_TextBox::FitText(void)
{
	/* Cutting Text To Size*/
	int Clip_W = 0, Clip_H = 0;

	TxtX = 2;
	TxtY = (TbxH - txtBox.h) / 2 + 1; // To +1 OR Not To +1

	int ActTxtW = txtBox.w;
	if (txtBox.w > TbxW) {
		Clip_W = TbxW - 2; // If text is wider than box
	}
	else {
		Clip_W = txtBox.w; // If text is equal or narrower than box
	}
	if (txtBox.h > TbxH) {
		Clip_H = TbxH;      // If text is larger than box
	}
	else {
		Clip_H = txtBox.h;  // If text is smaller than box
	}
	txtClip = { 0, 0, Clip_W, Clip_H };
	txtBox = { TxtX, TxtY , Clip_W, Clip_H };

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
		if (txtBox.w < TbxW) { // If text is longer than box don't centre but keep LEFT aligned.
			if (Angle == 90) {
				txtBox.x += txtBox.h;
				txtBox.y += (TbxW - txtBox.w) / 2;
			}
			else if (Angle == -90) {
				txtBox.x -= 2;   //Box.x - txtBox.w + txtBox.h;
				txtBox.y += txtBox.w + (TbxW - txtBox.w) / 2;
			}
			else {
				txtBox = { TxtX - 1 + (TbxW - txtBox.w) / 2, TxtY, Clip_W, Clip_H };
			}
		}
	}
	else if (Align == J_RIGHT) { // RIGHT ALIGN TEXT
		if (txtBox.w < TbxW) { // If text is longer than box don't right align but keep LEFT aligned.
			if (Angle == 90) {
				txtBox.x += txtBox.h;   //Box.x - txtBox.w + txtBox.h;
				txtBox.y += (TbxW - Clip_W);  //Box.y + TbxW;
			}
			else if (Angle == -90) {
				txtBox.x -= 2;   //Box.x - txtBox.w + txtBox.h;
				txtBox.y += TbxW;
			}
			else {
				txtBox = { TxtX + (TbxW - Clip_W), TxtY, Clip_W, Clip_H };
			}
		}
	}
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
		TbxX = (int)strtod(Val, &Next);
		TbxY = (int)strtod(Next, &Next);
		TbxW = (int)strtod(Next, &Next);
		TbxH = (int)strtod(Next, &Next);
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
void Jbw_TextBox::RdrTbx(void)
{
	// If Tbxbox is vertical
	if (Angle == 90 || Angle == -90) {
		int Tmp = Border->FrameW;
		Border->FrameW = Border->FrameH;
		Border->FrameH = Tmp;
	}

	// Size and Set Frame for Rendering
	if (ShowFrame == true) {
		Border->RdrFrame(); // Render frame
	}

	// Set Viewport area
	SDL_Rect Viewport = { Border->FrameX, Border->FrameY, Border->FrameW, Border->FrameH };
	SDL_RenderSetViewport(Jhandle->Rdr, &Viewport);

	// Size and Set Text for Rendering
	FitText();
	SDL_RenderCopyEx(Jhandle->Rdr, txtImage, &txtClip, &txtBox, Angle, &RotPoint, Flip);

	// Render to screen
	SDL_RenderPresent(Jhandle->Rdr);
}

