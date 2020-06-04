#pragma once
#include "Jbw_Base.h"

/******************************************************************************************
					             CLASS: Jbw_Text                  
******************************************************************************************/
class Jbw_Text : public Jbw_Base{
public:

	SDL_Texture* txtImage = NULL;
	
	int TxtX = 0;
	int TxtY = 0;

	int TxtSize = 0;
	int Angle = 0;
	SDL_RendererFlip Flip = SDL_FLIP_NONE;
	SDL_Point RotPoint = { 0, 0 };
	SDL_Color TxtColor = { 0, 0, 0, 255 };
	
	bool F_Bold = 0;
	bool F_Italic = 0;
	bool F_UnderL = 0;
	bool F_Strike = 0;
	
	std::string Text = "";
	double Value = 0;

	SDL_Rect txtBox = { 0,0,0,0 };
	SDL_Rect txtClip = { 0,0,0,0 };

/*-----------------------------------------------------------------------------------------
		CONSTRUCTORS / DESTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_Text() {};
	Jbw_Text(Jbw_Handles* handles, std::string NewText, int x, int y, int Fsize = 12, int TxtAngle = 0);
	~Jbw_Text();
	Jbw_Text(const Jbw_Text& cp);
	void operator=(const Jbw_Text& cp);

/*-----------------------------------------------------------------------------------------
		FUNCTIONS
------------------------------------------------------------------------------------------*/
public:
	//void InitTxt(SDL_Renderer* TRdr, std::string NewText, int x, int y, int Fsize = 12);
	bool SetTxt(std::string  *Var, const char* Val);
	void Add(std::string XtraText);
	void New(std::string NewText);
	void Del(void);
	void BackSpace(void);
	void CreateTexture(void);
	void RdrTxt(void);
	void TxtEvent(SDL_Event* e);
};

