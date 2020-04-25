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
	int ActTxtW = 0;
	int EditX;
	int	EditY;
	int EditW;
	int	EditH;
	J_TxtAlign Align = J_LEFT;
	SDL_Color BackColor = {255, 255, 255, 255}; // {Red, Green, Blue, Alpha}

	/*--------------------------------------------------------------------
		Jbw_EditBox: CONSTRUCTORS
	--------------------------------------------------------------------*/
	Jbw_EditBox() {}; // 
	Jbw_EditBox(SDL_Renderer* Rdr, int x, int y, int w, int h=14, int Fsize = 12);
	~Jbw_EditBox();

	/*--------------------------------------------------------------------
		Jbw_EditBox: PUBLIC FUNCTIONS 
	--------------------------------------------------------------------*/
	void InitEditBox(SDL_Renderer* Rdr, int x, int y, int w, int h = 15, int Fsize = 12);
	void FitText(void);
	void Set(std::string  Var, const char* Val);
	void Render(void);
	void Event(SDL_Event* e);
};

