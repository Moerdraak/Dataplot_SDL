#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

class Jbw_Text{
public:
	short int Id = 0;
	std::string Tag = "";
	SDL_Renderer* Trdr = NULL;

	TTF_Font* Font = NULL;
	SDL_Texture* txtImage = NULL;
	
	int FontSize = 0;
	int Xo = 0;
	int Yo = 0;
	int Angle = 0;
	SDL_RendererFlip Flip = SDL_FLIP_NONE;
	SDL_Point RotPoint = { 0, 0 };
	SDL_Color FontColor = { 0, 0, 0, 255 };
	
	bool F_Bold = 0;
	bool F_Italic = 0;
	bool F_UnderL = 0;
	bool F_Strike = 0;
	
	std::string Text = "";
	double Value = 0;

	SDL_Rect txtBox = { 0,0,0,0 };
	SDL_Rect txtClip = { 0,0,0,0 };

	/*--------------------------------------------------------------------
	CONSTRUCTORS / DESTRUCTORS
	--------------------------------------------------------------------*/
	Jbw_Text() {};
	Jbw_Text(SDL_Renderer* Rdr, std::string NewText, int x, int y, int FSize = 12);

	/*--------------------------------------------------------------------
	FUNCTIONS
	--------------------------------------------------------------------*/
	void SetTxt(std::string  Var, const char* Val);
	void Add(std::string XtraText);
	void New(std::string NewText);
	void Del(void);
	void BackSpace(void);
	void CreateTexture(void);
	void Render(void);
	void TxtEvent(SDL_Event* e);

};

