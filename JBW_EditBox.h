#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Jbw_Text.h"
#include "Jbw_Frame.h"
#include <string>

enum J_TxtAlign { J_LEFT, J_CENTRE, J_RIGHT };
enum J_Type { J_EDIT, J_TEXT, J_COMB, J_LIST };
enum J_MsgAck { J_OK, J_YES, J_YESNO };

class Jbw_EditBox : public Jbw_Text, public Jbw_Frame { // This cause 2 x Id ?!?
private: 
	
public: 
	//short int Id = 0;
	//std::string Tag = "";

	//SDL_Renderer* Renderer = NULL;
	//TTF_Font* Font = NULL;
	//bool F_Bold = 0;
	//bool F_Italic = 0;
	//bool F_UnderL = 0;
	//bool F_Strike = 0;
	//SDL_Texture* txtImage = NULL;
	
	//std::string Text = " ";	
	//double Value = 0;
	//int FontSize = 10;
	//SDL_Rect txtBox = { 0,0,0,0 };
	//SDL_Rect txtClip = { 0,0,0,0 };
	//J_Type TxtType = J_TEXT;
	//SDL_RendererFlip Flip = SDL_FLIP_NONE;
	//SDL_Point RotPoint = { 0, 0 };
	//int Angle = 0;
	int ActTxtW = 0;
	SDL_Rect Box = { 0,0,0,0 };
	SDL_Rect Frame = { 0,0,0,0 };
	J_TxtAlign Align = J_LEFT;
	SDL_Color BackColor = {255, 255, 255, 255}; // {Red, Green, Blue, Alpha}
	SDL_Color FrameColor = { 150, 150, 150, 255 };


	/*--------------------------------------------------------------------
		Jbw_EditBox: CONSTRUCTORS
	--------------------------------------------------------------------*/
	Jbw_EditBox() {}; // 
	Jbw_EditBox(SDL_Renderer* Rdr, J_Type Type, int x, int y, int w, int h=14);
	~Jbw_EditBox();

	/*--------------------------------------------------------------------
		Jbw_EditBox: PUBLIC FUNCTIONS 
	--------------------------------------------------------------------*/
	void FitText(void);
	//void Set(std::string NewText, const char* Prp1 = "~", int Val1 = 1, 
	//	const char* Prp2 = "~",	int Val2 = -1, 
	//	const char* Prp3 = "~", int Val3 = -1, 
	//	const char* Prp4 = "~", int Val4 = -1, 
	//	const char* Prp5 = "~", int Val5 = -1, 
	//	const char* Prp6 = "~", int Val6 = -1);
//	void SetSub(const char* Var, int Val);
	void Set(std::string  Var, const char* Val);
	void Render(void);
	void Event(SDL_Event* e);
};

