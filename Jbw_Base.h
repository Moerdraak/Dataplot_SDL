#pragma once
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>


/******************************************************************************************
								ENUM / CONSTANTS
******************************************************************************************/

// ?!?!?! Too  ENUM CLASS or not Too ?!?!?!?!

enum class J : const short int {
	TXT, EBX, LBX, CBX, BTN, GRD, LEN, // ObjWork
	LEFT, CENTRE, RIGHT, // TxtBox
	OK, YES, YESNO // MsgBox
};

enum J_Type : const short int {
	J_NULL, J_TRUE, J_FALSE,
	J_TXT, J_EBX, J_LBX, J_CBX, J_BTN,  J_GRD, J_LEN, // ObjWork
	J_LEFT, J_CENTRE, J_RIGHT, // TxtBox
	J_OK, J_YES, J_NO, J_YESNO, // MsgBox
	J_CLICK, 
	J_UP, J_DOWN, // Callback events
	J_ITEM, J_MENU // Menu 
};

enum J_Event : const short int {
	J_E_NULL, 
	J_MS_LCLICK, J_MS_RCLICK, J_MS_OVER
};


const SDL_Color J_WHITE = { 255, 255, 255, 255 };
const SDL_Color J_BLACK = { 0, 0, 0, 255 };
const SDL_Color J_GREY = { 128, 128, 128, 255 };
const SDL_Color J_SILVER = { 192, 192, 192, 255 };

const SDL_Color J_RED = { 255, 0, 0, 255 };
const SDL_Color J_LIME = { 0, 255, 0, 255 };
const SDL_Color J_BLUE = { 0, 0, 255, 255 };

const SDL_Color J_CYAN = { 0, 255, 255, 255 };
const SDL_Color J_MAGENTA = { 255, 0, 255, 255 };
const SDL_Color J_YELLOW = { 255, 255, 0, 255 };

const SDL_Color J_MAROON = { 128, 0, 0, 255 };
const SDL_Color J_GREEN = { 0, 128, 0, 255 };
const SDL_Color J_NAVY = { 0, 0, 128, 255 };

const SDL_Color J_TEAL = { 0, 128, 128, 255 };
const SDL_Color J_OLIVE = { 128, 128, 0, 255 };
const SDL_Color J_PURPLE = { 128, 0, 128, 255 };

const SDL_Color J_C_Frame = { 150, 150, 150, 255 };
const SDL_Color J_C_BtnDwn = { 150, 150, 150, 255 };
const SDL_Color J_C_Header = { 200, 200, 200, 255 };
const SDL_Color J_C_msOver = { 210, 210, 210, 255 };
const SDL_Color J_C_BtnGrey = { 220, 220, 220, 255 };
const SDL_Color J_C_Window = { 230, 230, 230, 255 };
const SDL_Color J_C_Grey = { 240, 240, 240, 255 };
const SDL_Color J_C_LGrey = { 245, 245, 245, 255 };

/******************************************************************************************
						 STRUCT holding Jbw Handles
******************************************************************************************/
// Forward declarations for Jbw_Handles 
class Jbw_Text;
class Jbw_EditBox;
class Jbw_ListBox;
class Jbw_ComboBox;
class Jbw_Button;
class Jbw_Grid;
class Jbw_Slider;
class Jbw_Debug;

struct Jbw_Handles {
	bool WindowActive = true;
	SDL_Rect GuiArea = { 0, 0, 0, 0 };
	SDL_Window* Gui = NULL;
	SDL_Renderer* Rdr = NULL;
	SDL_Event Event;
	void** Jbw_Obj;
	Jbw_Debug* Debug;
};

struct Jbw_Return {
	bool ReturnType = false;
	std::string ErrMessage = "";
};

/******************************************************************************************
								 CLASS: Jbw_Base
******************************************************************************************/
class Jbw_Base{
public:	
	short int Id = 0;
	std::string Tag = "";

	/* I don't "new" jhandle - therefore I do not create memory for it 
	and therefore do not need to have a copy or assignment constructor*/
	Jbw_Handles *Jhandle = NULL; 

	SDL_Rect Obj = { -1, -1, -1, -1 }; 

	bool Visible = true;
	bool Enabled = true;
	bool Focus = false;
	bool msOver = false;
	bool DoRender = false;
	bool OnChange = false;

/*-----------------------------------------------------------------------------------------
	CONSTRUCTORS / DESTRUCTORS
------------------------------------------------------------------------------------------*/
public:
//	Jbw_Base() {};
//	~Jbw_Base();
/* I don't "new" jhandle - therefore I do not create memory for it
	and therefore do not need to have a copy or assignment constructor*/

/*-----------------------------------------------------------------------------------------
	FUNCTIONS
------------------------------------------------------------------------------------------*/
	SDL_Texture* CopyArea(Jbw_Handles* handles, int x, int y, int w, int h);
	void PasteArea(Jbw_Handles* handles, SDL_Texture* Image, int x = -1, int y = -1, int w = -1, int h = -1);
	void FreeArea(SDL_Texture* Image);

//	Jbw_Base(Jbw_Base& cp);
//	void operator=(Jbw_Base& cp);
};

