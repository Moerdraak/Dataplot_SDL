#include "Jbw_EditBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_EditBox::Jbw_EditBox(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize)
{
	InitEbx(handles, x, y, w, h, Fsize);
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_EditBox::~Jbw_EditBox() {

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: InitEbx
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::InitEbx(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize)
{
	Jhandle = handles;
	TbxX = x + 1;
	TbxY = y + 1;
	TbxW = w - 2;
	TbxH = h - 2;
	TxtSize = Fsize;
	Border = new Jbw_Frame(handles, x, y, w, h, true);
}

/*-----------------------------------------------------------------------------------------
FUNCTION: Set
------------------------------------------------------------------------------------------*/
bool Jbw_EditBox::SetEbx(std::string* Var, const char* Val)
{
	return SetTbx(Var, Val);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrEbx
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::RdrEbx(void)
{
	FrameOn = true;
	FillOn = true;
	RdrTbx();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::EbxEvent(SDL_Event* Event)
{
	bool Flag = false;
	//If mouse event happened
	if (Event->type == SDL_MOUSEMOTION || Event->type == SDL_MOUSEBUTTONDOWN || Event->type == SDL_MOUSEBUTTONUP){
		// Get mouse position
		int msX, msY;
		SDL_GetMouseState(&msX, &msY);

		// Mouse pointer inside Edit box
		if (msX > TbxX && msX < TbxX + TbxW && msY > TbxY && msY < TbxY + TbxH)
		{
			if (msOver == false) {
				msOver = true;
				Border->LineColor = J_BLACK;
				DoRender = true;
			}

			switch (Event->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				if (Event->button.button == 1) {
					Focus = true;
				}
				else if (Event->button.button == 3) {
				Add(SDL_GetClipboardText());
				}
				break;

			case SDL_MOUSEBUTTONUP:
				break;
			}
		}
		else {
			if (msOver == true) {
				msOver = false;
				Border->LineColor = J_C_Frame;
				DoRender = true;
			}

			if (Event->type == SDL_MOUSEBUTTONDOWN) {
				Focus = false;
				Border->LineColor = J_C_Frame;
			}
		}
	}

	if (Focus == true && Enabled == true) {
		if (Event->type == SDL_TEXTINPUT){
			Add(Event->text.text);
			OnChange = true;
			DoRender = true;
		}
		else if (Event->type == SDL_KEYDOWN){
			if (Event->key.keysym.sym == SDLK_BACKSPACE) {
				BackSpace();
				OnChange = true;
				DoRender = true;
			}
			else if (Event->key.keysym.sym == SDLK_DELETE) {
				OnChange = true;
				DoRender = true;
			}
		}
		Border->LineColor = J_BLACK;
	}

	if (DoRender == true) {
		DoRender = false;
		RdrEbx();
	}
	
	return;
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

/*-----------------------------------------------------------------------------------------
	FUNCTION: GetS
------------------------------------------------------------------------------------------*/
std::string Jbw_EditBox::EboxGetS(std::string Property)
{
	std::string Answer = "";
	if (Property == "Text") {
		Answer.assign(Text);
	}
	else if (Property == "Something1") {

	}
	else if (Property == "Something2") {

	}
	else if (Property == "Something3") {

	}
	return Answer;
}
