#pragma once
#include "Jbw_Frame.h"
#include "Jbw_ListBox.h"
class Jbw_Frame;
class Jbw_ListBox;

class Jbw_Debug : private Jbw_ListBox {
public:
	SDL_Rect Area = { 0, 0, 0, 0 };
	SDL_Window* Gui = NULL;
	SDL_Renderer* Rdr = NULL;

	Jbw_Button* btnActive;
	Jbw_Button* btnClear;
	bool Active = true;

	Jbw_Debug(int x, int y, int w, int h);

	void NewLine(std::string NewTxt);
	void NewLine(std::string NewTxt, bool Thing);
	void NewLine(std::string NewTxt, double Thing);
	void NewLine(std::string NewTxt, std::string Thing);
	void AddWord(std::string NewTxt);
	void Clear(void);

	void dbgEvent(SDL_Event* Event);
	void btnActive_Callback(void);
};

