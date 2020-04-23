#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

enum J_TxtAlign { J_LEFT, J_CENTRE, J_RIGHT };
enum J_Type { J_EDIT, J_TEXT, J_COMB, J_LIST };
enum J_MsgAck { J_OK, J_YES, J_YESNO };

class Jbw_EditBox{
private: 
	
public: 
	short int Id = 0;
	std::string Tag = "";

	SDL_Renderer* Renderer = NULL;
	TTF_Font* Font = NULL;
	SDL_Texture* txtImage = NULL;
	SDL_Rect Box = { 0,0,0,0 };
	SDL_Rect Frame = { 0,0,0,0 };
	std::string Text;	
	int FontSize = 10;
	SDL_Rect txtBox = { 0,0,0,0 };
	SDL_Rect txtClip = { 0,0,0,0 };
	J_Type TxtType = J_TEXT;
	SDL_RendererFlip Flip = SDL_FLIP_NONE;
	SDL_Point RotPoint = { 0, 0 };
	int Angle = 0;
	int ActTxtW = 0;
	J_TxtAlign Align = J_LEFT;
	SDL_Color TextColor = {0, 0, 0, 255};
	SDL_Color BackColor = {255, 255, 255, 255};//	Uint8 BackColor[4] = { 255, 255, 255, 255 };
	SDL_Color FrameColor = { 150, 150, 150, 255 };//	Uint8 FrameColor[4] = { 0, 0, 0, 255 };


	/*--------------------------------------------------------------------
		Jbw_EditBox: CONSTRUCTORS
	--------------------------------------------------------------------*/
	Jbw_EditBox() {}; // oivoirewvj
	Jbw_EditBox(SDL_Renderer* Render, J_Type Type, int x, int y, int w, int h=14);
	~Jbw_EditBox();

	/*--------------------------------------------------------------------
		Jbw_EditBox: PUBLIC FUNCTIONS 
	--------------------------------------------------------------------*/
	void CreateTexture(void);
	void Set(std::string NewText, const char* Prp1 = "~", int Val1 = 1, 
		const char* Prp2 = "~",	int Val2 = -1, 
		const char* Prp3 = "~", int Val3 = -1, 
		const char* Prp4 = "~", int Val4 = -1, 
		const char* Prp5 = "~", int Val5 = -1, 
		const char* Prp6 = "~", int Val6 = -1);
	void SetSub(const char* Var, int Val);
	void SetX(std::string  Var, const char* Val);
	void Render(void);
	void Add(std::string XtraText);
	void New(std::string NewText);
	void Del(void);
	void BackSpace(void);
	void Event(SDL_Event* e);
};

