#pragma once

#include "Jbw_Base.h"
#include "Jbw_Text.h"
#include "Jbw_Frame.h"

class Jbw_EditBox : public Jbw_Text { 
private: 
	
public: 
	bool Focus = false;
	int EditX = 0;
	int	EditY = 0;
	int EditW = 0;
	int	EditH = 0;

	Jbw_Frame Border;
	J_Type Align = J_LEFT;

/*-----------------------------------------------------------------------------------------
	CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_EditBox() {}; // 
	Jbw_EditBox(SDL_Renderer* Rdr, int x, int y, int w, int h=14, int Fsize = 12);
	Jbw_EditBox(J_Properties *Prop);
	~Jbw_EditBox();

/*-----------------------------------------------------------------------------------------
	FUNCTIONS 
------------------------------------------------------------------------------------------*/
public:
	void InitEbx(J_Properties *Prop);
	void InitEbx(SDL_Renderer* Rdr, int x, int y, int w, int h = 14, int Fsize = 12);
	void FitText(void);
	bool SetEbx(std::string  *Var, const char* Val);
	void RdrEbx(void);
	void EbxEvent(Jbw_Handles* h);

	Uint32 static Flashy(Uint32 interval, void* param);

	static void my_function(void)
	{
		int a = 5;
	}

};

