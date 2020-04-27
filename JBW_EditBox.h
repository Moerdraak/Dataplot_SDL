#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Jbw_Text.h"
#include "Jbw_Frame.h"
//#include "Jbw_FrameWork.h" 
#include <string>

enum J_TxtAlign { J_LEFT, J_CENTRE, J_RIGHT };
enum J_Type { J_EDIT, J_TEXT, J_COMB, J_LIST };
enum J_MsgAck { J_OK, J_YES, J_YESNO };

class Jbw_EditBox : public Jbw_Text, public Jbw_Frame { // This cause 2 x Id ?!?
private: 
	
public: 
//	Jbw_FrameWork *J;


	bool Focus = false;
	int EditX = 0;
	int	EditY = 0;
	int EditW = 0;
	int	EditH = 0;

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
	void InitEbx(SDL_Renderer* Rdr, int x, int y, int w, int h = 15, int Fsize = 12);
	void FitText(void);
	bool SetEbx(std::string  *Var, const char* Val);
	void Render(void);
	void Event(SDL_Event* e);




	Uint32 static Flashy(Uint32 interval, void* param);

	static void my_function(void)
	{
		int a = 5;
	}

};

