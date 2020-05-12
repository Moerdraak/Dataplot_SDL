#pragma once
#include "Jbw_Base.h"
#include "Jbw_Text.h"
#include "Jbw_Frame.h"

class Jbw_TextBox : public Jbw_Text {
private:

public:
	int TbxX = 0;
	int	TbxY = 0;
	int TbxW = 0;
	int	TbxH = 0;
	
	bool ShowFrame = false;
	Jbw_Frame* Border;
	J_Type Align = J_LEFT;
	
/*-----------------------------------------------------------------------------------------
	CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_TextBox() {}; // 
	Jbw_TextBox(Jbw_Handles* handles, std::string Text, int x, int y, int w, int h = 14,
		int Fsize = 12);
//	Jbw_TextBox(J_Properties* Prop);
	~Jbw_TextBox();

/*-----------------------------------------------------------------------------------------
	FUNCTIONS
------------------------------------------------------------------------------------------*/
public:
//	void InitTbx(J_Properties* Prop);
	void InitTbx(Jbw_Handles* handles, std::string Text, int x, int y, int w, int h = 14,
		int Fsize = 12);
	void FitText(void);
	bool SetTbx(std::string* Var, const char* Val);
	void RdrTbx(void);
};
