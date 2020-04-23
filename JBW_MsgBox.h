#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Jbw_EditBox.h"
#include <string>

class Jbw_MsgBox
{
public:
	SDL_Window* MsgWindow = NULL; 
	SDL_Renderer* Render = NULL; 
	TTF_Font* Font = NULL;
	SDL_Texture* txtImage = NULL;
	Jbw_EditBox* edHeader = NULL;
	Jbw_EditBox *btnAck = NULL;
	Jbw_EditBox* btnNo = NULL;
	SDL_Surface* txtSurf = NULL;
	J_MsgAck Type;

	int Window_w;
	int Window_h;
	int FontSize = 10;

	SDL_Rect Border = { 0,0,0,0 };
	SDL_Rect txtBox = { 0,0,0,0 };
	SDL_Rect txtClip = { 0,0,0,0 };

	Jbw_MsgBox(std::string Title, std::string Msg, J_MsgAck Type,
		int x, int y, int w = 150, int h = 100);
	~Jbw_MsgBox();
	
	void RenderMsg(std::string Msg, int Line, bool DoRender);
	void RenderBox(void);
	void Parser(std::string Txt, bool DoRender);
//	void Free(void);
};