#include "Jbw_EditBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_EditBox::Jbw_EditBox(SDL_Renderer* Rdr, int x, int y, int w, int h, int Fsize)
{
	InitEbx(Rdr, x, y, w, h);
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_EditBox::~Jbw_EditBox() {
	SDL_DestroyTexture(txtImage);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Create
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::InitEbx(SDL_Renderer* Rdr, int x, int y, int w, int h, int Fsize)
{
	EditX = x + 1; EditY = y + 1; EditW = w - 2; EditH = h - 2;
	CreateFrame(Rdr, x, y, w, h);
	Trdr = Rdr;
	TxtSize = Fsize;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: FitText
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::FitText(void)
{
	/* Cutting Text To Size*/
	int Clip_W = 0, Clip_H = 0;

//	TxtX = EditX + 1;
	TxtX = 2;
//	TxtY = EditY + (EditH - txtBox.h) / 2 + 1; // To +1 OR Not To +1
	TxtY = (EditH - txtBox.h) / 2 + 2; // To +1 OR Not To +1

	int ActTxtW = txtBox.w;
	if (txtBox.w > EditW) {
		Clip_W = EditW - 2; // If text is wider than box
	}
	else {
		Clip_W = txtBox.w; // If text is equal or narrower than box
	}
	if (txtBox.h > EditH) {
		Clip_H = EditH;      // If text is larger than box
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
		if (txtBox.w < EditW) { // If text is longer than box don't centre but keep LEFT aligned.
			if (Angle == 90) {
				txtBox.x += txtBox.h;
				txtBox.y += (EditW - txtBox.w) / 2;
			}
			else if (Angle == -90) {
				txtBox.x -= 2;   //Box.x - txtBox.w + txtBox.h;
				txtBox.y += txtBox.w + (EditW - txtBox.w) / 2;
			}
			else {
				txtBox = { TxtX + (EditW - txtBox.w) / 2, TxtY, Clip_W, Clip_H };
			}
		}
	}
	else if (Align == J_RIGHT) { // RIGHT ALIGN TEXT
		if (txtBox.w < EditW) { // If text is longer than box don't right align but keep LEFT aligned.
			if (Angle == 90) {
				txtBox.x += txtBox.h;   //Box.x - txtBox.w + txtBox.h;
				txtBox.y += (EditW - Clip_W);  //Box.y + EditW;
			}
			else if (Angle == -90) {
				txtBox.x -= 2;   //Box.x - txtBox.w + txtBox.h;
				txtBox.y += EditW;
			}
			else {
				txtBox = { TxtX + (EditW - Clip_W), TxtY, Clip_W, Clip_H };
			}
		}
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION: Set
------------------------------------------------------------------------------------------*/
bool Jbw_EditBox::SetEbx(std::string  *Var, const char * Val)
{  
	bool Flag = false;
	char* Next;

	// Text
	if (Var->compare("Text") == 0) { 
	//	Text.assign(Val);
	}
	// Box
	else if (Var->compare("Box") == 0) {
		EditX = (int)strtod(Val, &Next);
		EditY = (int)strtod(Next, &Next);
		EditW = (int)strtod(Next, &Next);
		EditH = (int)strtod(Next, &Next);
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
		BackColor.b = (int)strtod(Val, &Next);
		BackColor.g = (int)strtod(Next, &Next);
		BackColor.r = (int)strtod(Next, &Next);
		Flag = true;
	}
	else if (Var->compare("LineColor") == 0) {
		LineColor.b = (int)strtod(Val, &Next);
		LineColor.g = (int)strtod(Next, &Next);
		LineColor.r = (int)strtod(Next, &Next);
		Flag = true;
	}
	return Flag;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Render
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::Render(void)
{
	// If Editbox is vertical
	if (Angle == 90 || Angle == -90) {
		int Tmp = FrameW;
		FrameW = FrameH;
		FrameH = Tmp;

		Tmp = EditW;
		EditW = EditH;
		EditH = Tmp;
	}

	SDL_Rect Viewport = { FrameX, FrameY, FrameW, FrameH };

	// Set Viewport area	
	SDL_RenderSetViewport(Trdr, &Viewport); 
	
	// Size and Set Frame for Rendering
	SetFrame(); // Build frame
	FrameRdr(); // Render frame

	// Size and Set white area inside of Edit box for Rendering
	SDL_SetRenderDrawColor(Trdr, BackColor.b, BackColor.g, BackColor.r, BackColor.a);
	SDL_Rect Box = { 1, 1, EditW, EditH };
	SDL_RenderFillRect(Trdr, &Box);
	
	// Size and Set Text for Rendering
	FitText();
	SDL_RenderCopyEx(Trdr, txtImage, &txtClip, &txtBox, Angle, &RotPoint, Flip);
	
	SDL_RenderPresent(Trdr); // Render to screen
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::Event(SDL_Event* e)
{
	bool Flag = false;
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Mouse pointer inside Edit box
		if (x > EditX && x < EditX + EditW && y > EditY && y < EditY + EditH)
		{
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				LineColor = { 0, 0, 0, 255 };
				break;

			case SDL_MOUSEBUTTONDOWN:
			//	BackColor = { 0, 0, 0, 255 };
				Focus = true;
		//		SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, &Dp);
				break;

			case SDL_MOUSEBUTTONUP:
			//	BackColor = { 255, 255, 255, 255 };
				break;
			}
		}
		else {
			LineColor = { 150, 150, 150, 255 };
			if (e->type == SDL_MOUSEBUTTONDOWN) {
				Focus = false;
			}
		}
	}

	if (Focus == false) {
		return;
	}
	else if (e->type == SDL_TEXTINPUT) 	{
		Add(e->text.text);
//		Render();
	}
	else if (e->type == SDL_KEYDOWN)
	{
		if (e->key.keysym.sym == SDLK_BACKSPACE) {
			BackSpace();
		//	Render();
		}
		else if (e->key.keysym.sym == SDLK_DELETE) {
		}
		else if (e->key.keysym.sym) {
		}
	}
	if (0) {
		if (e->type == SDL_USEREVENT) {
			e->user.data1;
			my_function();
			//	Uint32* AAA{ static_cast<Uint32*>(e->user.data1) };
			//	void (*A) (void*) = e->type.user.data2;
			//	*A();


		}
	}

	//Uint32 delay = (330 / 10) * 10; // To round it down to the nearest 10 ms 
//SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, &Dp);
//	Uint32 delay = (3300 / 10) * 10; // To round it down to the nearest 10 ms 

//	SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, Trdr);
	
	Render();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: FLASHY
------------------------------------------------------------------------------------------*/
Uint32 Jbw_EditBox::Flashy(Uint32 interval, void* param)
{
	SDL_Event event;
	SDL_UserEvent userevent;

	userevent.type = SDL_USEREVENT;
	userevent.code = 0;
	userevent.data1 = &my_function;
	userevent.data2 = param;

	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);
	return(interval);
}
