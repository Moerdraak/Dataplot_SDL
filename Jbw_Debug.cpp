#include "Jbw_Debug.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Debug::Jbw_Debug(int x, int y, int w, int h) 
{
	Area.x = 0;
	Area.y = 0;
	Area.w = w;
	Area.h = h;

	Jhandle = new Jbw_Handles;

	Jhandle->Gui = SDL_CreateWindow("DEBUG WINDOW", x, y, w, h, SDL_WINDOW_OPENGL);
	Jhandle->Rdr = SDL_CreateRenderer(Jhandle->Gui, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(Jhandle->Rdr, J_WHITE.r, J_WHITE.g, J_WHITE.b, J_WHITE.a);
	SDL_RenderFillRect(Jhandle->Rdr, &Area);
	SDL_RenderPresent(Jhandle->Rdr);

	// Display Area coordinates
	Obj.x = 0;
	Obj.y = 20; // Leave space for buttons
	Obj.w = w - 2;
	Obj.h = h - 2;
	FontSize = 10;
	TxtBoxH = FontSize + 4; // For Arial the Box height is generaly 2 points bigger than the font size
							// Then add a gap at the top and at the bottom so add 4
	Fill = true;

	LineColor = J_C_Frame; // Frame Color
	CreateFrame(); // Build frame
	Slider = new Jbw_Slider(Jhandle, Obj.x + Obj.w - 15, Obj.y, 15, Obj.h, 5/* random start value */, true);

	// Add buttons
	btnActive = new Jbw_Button(Jhandle, Obj.x + Obj.w - 120, 0, 50, 16, "ACTIVE", 12);
	btnActive->CreateButton();
	btnActive->RdrBtn();

	btnClear = new Jbw_Button(Jhandle, Obj.x + Obj.w - 60, 0, 50, 16, "CLEAR", 12);
	btnClear->CreateButton();
	btnClear->RdrBtn();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: NewLine
------------------------------------------------------------------------------------------*/
void Jbw_Debug::NewLine(std::string NewTxt)
{
	if (Active) {
		AddText(NewTxt);
		if (Cnt > Lines) {
			FromLine = Cnt - Lines;
			ToLine = Cnt;
		}

		RdrLbx();
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: NewLine
------------------------------------------------------------------------------------------*/
void Jbw_Debug::NewLine(std::string NewTxt, bool Thing)
{
	if (Active) {
		AddText(NewTxt);

		TxtList[Cnt - 1].Text.append(std::to_string(Thing));
		TxtList[Cnt - 1].CreateTexture();

		if (Cnt > Lines) {
			FromLine = Cnt - Lines;
			ToLine = Cnt;
		}
		RdrLbx();
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: NewLine
------------------------------------------------------------------------------------------*/
void Jbw_Debug::NewLine(std::string NewTxt, int Thing)
{
	if (Active) {
		AddText(NewTxt);

		TxtList[Cnt - 1].Text.append(std::to_string(Thing));
		TxtList[Cnt - 1].CreateTexture();

		if (Cnt > Lines) {
			FromLine = Cnt - Lines;
			ToLine = Cnt;
		}
		RdrLbx();
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: NewLine
------------------------------------------------------------------------------------------*/
void Jbw_Debug::NewLine(std::string NewTxt, double Thing)
{
	if (Active) {
		AddText(NewTxt);

		TxtList[Cnt - 1].Text.append(std::to_string(Thing));
		TxtList[Cnt - 1].CreateTexture();

		if (Cnt > Lines) {
			FromLine = Cnt - Lines;
			ToLine = Cnt;
		}
		RdrLbx();
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: NewLine
------------------------------------------------------------------------------------------*/
void Jbw_Debug::NewLine(std::string NewTxt, std::string Thing)
{
	if (Active) {
		AddText(NewTxt);

		TxtList[Cnt - 1].Text.append(Thing);
		TxtList[Cnt - 1].CreateTexture();

		if (Cnt > Lines) {
			FromLine = Cnt - Lines;
			ToLine = Cnt;
		}
		RdrLbx();
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: AddWord
------------------------------------------------------------------------------------------*/
void Jbw_Debug::AddWord(std::string NewTxt)
{
	if (Active) {
		TxtList[Cnt - 1].Text.append(NewTxt);
		TxtList[Cnt - 1].CreateTexture();
		RdrLbx();
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Clear
------------------------------------------------------------------------------------------*/
void Jbw_Debug::Clear(void)
{
	Jbw_ListBox::Clear();
	RdrLbx();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: dbgEvent
------------------------------------------------------------------------------------------*/
void Jbw_Debug::dbgEvent(SDL_Event* Event)
{

	if (Event->type == SDL_QUIT /*256*/ || Event->window.event == SDL_WINDOWEVENT_CLOSE /* 14 */)
	{
		
		if (SDL_GetWindowID(Jhandle->Gui) == Event->window.windowID) {
			Active = false;
			SDL_DestroyRenderer(Jhandle->Rdr);
			SDL_DestroyWindow(Jhandle->Gui);
		}
	}

	// Check if Window is active
	if ((SDL_GetWindowID(Jhandle->Gui) == Event->window.windowID) && Event->window.event == SDL_WINDOWEVENT_ENTER) {
		msOver = true;
	}
	else if ((SDL_GetWindowID(Jhandle->Gui) == Event->window.windowID) && Event->window.event == SDL_WINDOWEVENT_LEAVE) {
		msOver = false;
	}
	if (msOver == true) {
		LbxEvent(Event);
		if (btnActive->BtnEvent(Event) == J_MS_LCLICK) {
			btnActive_Callback();
		}

		if (btnClear->BtnEvent(Event) == J_MS_LCLICK) {
			Clear();
		}
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Clear
------------------------------------------------------------------------------------------*/
void Jbw_Debug::btnActive_Callback(void)
{
	if (btnActive->Caption == "OFF") {
		btnActive->Caption = "ACTIVE";
		btnActive->CreateButton();
		btnActive->RdrBtn();
	}
	else {
		btnActive->Caption = "OFF";
		btnActive->CreateButton();
		btnActive->RdrBtn();
	}
}