#include "Jbw_EditBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_EditBox::Jbw_EditBox(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize)
{
	Jhandle = handles;
	Obj.x = x;
	Obj.y = y;
	Obj.w = w;
	Obj.h = h;
	TxtSize = Fsize;
	CreateEbx();
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_EditBox::~Jbw_EditBox() {

}

/*-----------------------------------------------------------------------------------------
	COPY CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_EditBox::Jbw_EditBox(const Jbw_EditBox& cp) : Jbw_Base(cp)
{
	TxtSize = cp.TxtSize;
	Tbx = new Jbw_TextBox(*cp.Tbx);
	
	/*   OR YOU CAN   */
	//	CreateEbx();
	//	*Tbx = *cp.Tbx;
}

/*-----------------------------------------------------------------------------------------
	ASIGNMENT OPERATOR OVERLOAD
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::operator=(const Jbw_EditBox& cp) 
{
	if (this != &cp)// Self assign check
	{
		Jbw_Base::operator=(cp);
		TxtSize = cp.TxtSize;

		delete Tbx;
		Tbx = new Jbw_TextBox;
		*Tbx = *cp.Tbx;
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: InitEbx
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::InitEbx(Jbw_Handles* handles, int x, int y, int w, int h, int Fsize)
{
	Jhandle = handles;
	Obj.x = x;
	Obj.y = y;
	Obj.w = w;
	Obj.h = h;
	TxtSize = Fsize;
	CreateEbx();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: ReSizeEbx
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::CreateEbx(void)
{
	if (Tbx == NULL) {
		Tbx = new Jbw_TextBox(Jhandle, "", Obj.x, Obj.y, Obj.w, Obj.h, TxtSize);
		Tbx->FrameOn = true;
		Tbx->FillOn = true;
	}
	else {
		Tbx->Obj = Obj;
		Tbx->CreateTbx();
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION: Set
------------------------------------------------------------------------------------------*/
bool Jbw_EditBox::SetEbx(std::string* Var, const char* Val)
{
	return Tbx->SetTbx(Var, Val);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrEbx
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::RdrEbx(void)
{
	if (Visible == false) {
		return;
	}
	Tbx->RdrTbx();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::EbxEvent(SDL_Event* Event)
{
	if (Visible == false || Enabled == false) {
		return;
	}

	bool Flag = false;
	//If mouse event happened
	if (Event->type == SDL_MOUSEMOTION || Event->type == SDL_MOUSEBUTTONDOWN || Event->type == SDL_MOUSEBUTTONUP){
		// Get mouse position
		int msX, msY;
		SDL_GetMouseState(&msX, &msY);

		// Mouse pointer inside Edit box
		if (msX > Obj.x && msX < Obj.x + Obj.w && msY > Obj.y && msY < Obj.y + Obj.h)
		{
			if (msOver == false) {
				msOver = true;
				Tbx->Border->LineColor = J_BLACK;
				DoRender = true;
			}

			switch (Event->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				if (Event->button.button == 1) {
					Focus = true;
				}
				else if (Event->button.button == 3) {
					Tbx->Add(SDL_GetClipboardText());
				}
				break;

			case SDL_MOUSEBUTTONUP:
				break;
			}
		}
		else {
			if (msOver == true) {
				msOver = false;
				Tbx->Border->LineColor = J_C_Frame;
				DoRender = true;
			}

			if (Event->type == SDL_MOUSEBUTTONDOWN) {
				Focus = false;
				Tbx->Border->LineColor = J_C_Frame;
			}
		}
	}

	if (Focus == true && Enabled == true) {
		if (Event->type == SDL_TEXTINPUT){
			Tbx->Add(Event->text.text);
			OnChange = true;
			DoRender = true;
		}
		else if (Event->type == SDL_KEYDOWN){
			if (Event->key.keysym.sym == SDLK_BACKSPACE) {
				Tbx->BackSpace();
				OnChange = true;
				DoRender = true;
			}
			else if (Event->key.keysym.sym == SDLK_DELETE) {
				OnChange = true;
				DoRender = true;
			}
		}
		Tbx->Border->LineColor = J_BLACK;
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
		Answer.assign(Tbx->Text);
	}
	else if (Property == "Something1") {

	}
	else if (Property == "Something2") {

	}
	else if (Property == "Something3") {

	}
	return Answer;
}
