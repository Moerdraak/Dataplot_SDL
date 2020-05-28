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
	J_BTN_CLICK, J_UP, J_DOWN// Callback events
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

const SDL_Color J_C_Window = { 230, 230, 230, 255 };
const SDL_Color J_C_Frame = { 150, 150, 150, 255 };
const SDL_Color J_C_BtnGrey = { 220, 220, 220, 255 };
const SDL_Color J_C_Grey = { 240, 240, 240, 255 };
const SDL_Color J_C_LGrey = { 245, 245, 245, 255 };
const SDL_Color J_C_msOver = { 210, 210, 210, 255 };
const SDL_Color J_C_BtnDwn = { 150, 150, 150, 255 };

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

struct Jbw_Handles {
	SDL_Rect GuiArea = { 0, 0, 0, 0 };
	SDL_Window* JbwGui = NULL;
	SDL_Renderer* Rdr = NULL;
	SDL_Event Event;
	void** Jbw_Obj;

};

/******************************************************************************************
								 CLASS: Jbw_Base
******************************************************************************************/
class Jbw_Base{
public:	
	short int Id = 0;
	std::string Tag = "";
	Jbw_Handles *Jhandle;

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
	Jbw_Base() {};
	~Jbw_Base() {};
};