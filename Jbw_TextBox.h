#pragma once
#include "Jbw_Base.h"
#include "Jbw_Text.h"
#include "Jbw_Frame.h"

class Jbw_TextBox : public Jbw_Text {
private:

public:
	bool FrameOn = false;
	bool FillOn = false;
	Jbw_Frame* Border = NULL;
	J_Type Align = J_LEFT;
	
/*-----------------------------------------------------------------------------------------
	CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_TextBox() {}; // 
	Jbw_TextBox(Jbw_Handles* handles, std::string TxtString, int x, int y, int w, int h = 14,
		int Fsize = 12);
	~Jbw_TextBox();

/*-----------------------------------------------------------------------------------------
	FUNCTIONS
------------------------------------------------------------------------------------------*/
public:
	void CreateTbx(void);
	void SetTbx(std::string NewText, int FontSize = -1);
	void SetTbx(SDL_Rect Area);
	void SetTbx(SDL_Rect Area, std::string NewText, int FontSize = -1);

	void InitTbx(Jbw_Handles* handles, std::string TxtString, int x, int y, int w, int h = 14,
		int Fsize = 12);

	void FitText(void);
	bool SetTbx(std::string* Var, const char* Val);
	void BackColor(SDL_Color Color);
	void BorderColor(SDL_Color Color);
	void RdrTbx();
};
