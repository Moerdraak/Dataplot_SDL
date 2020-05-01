#pragma once
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
	J_TXT, J_EBX, J_LBX, J_CBX, J_BTN,  J_GRD, J_LEN, // ObjWork
	J_LEFT, J_CENTRE, J_RIGHT, // TxtBox
	J_OK, J_YES, J_YESNO, // MsgBox
	J_CLICK   // Callback events
};

const SDL_Color J_C_Frame = { 150, 150, 150, 255 };
const SDL_Color J_C_White = { 255, 255, 255, 255 };
const SDL_Color J_C_Black = { 0, 0, 0, 255 };
const SDL_Color J_C_BtnGrey = { 220, 220, 220, 255 };
const SDL_Color J_C_Grey = { 240, 240, 240, 255 };
const SDL_Color J_C_LGrey = { 245, 245, 245, 255 };
const SDL_Color J_C_msOver = { 210, 210, 210, 255 };
const SDL_Color J_C_BtnDwn = { 150, 150, 150, 255 };

/******************************************************************************************
								 STRUCT: J_Properties
******************************************************************************************/
struct J_Properties {
	SDL_Renderer* Rdr;
	int x = 0;
	int y = 0;
	int w = 100;
	int h = 15;
	int Fsize = 12;
	int ColCnt = 0;
	int RowCnt = 0;
	std::string Tag = "";
	std::string Caption = "";
	bool BoolVal = false;
};

/******************************************************************************************
								 CLASS: Jbw_Text
******************************************************************************************/
class Jbw_Base{
public:	
	short int Id = 0;
	std::string Tag = "";
	SDL_Renderer* Jrdr;
	
//	int ObjX = 0;
//	int ObjY = 0;

	bool Visible = true;
	bool enabled = true;

	bool msOver = false;

/*-----------------------------------------------------------------------------------------
	CONSTRUCTORS / DESTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_Base() {};
	~Jbw_Base() {};
};