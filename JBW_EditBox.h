#pragma once

#include "Jbw_Base.h"
#include "Jbw_TextBox.h"
#include "Jbw_Frame.h"

class Jbw_EditBox : public Jbw_Base { 
private: 
	
public: 

	Jbw_TextBox* Tbx = NULL;
	int TxtSize = 12;


/*-----------------------------------------------------------------------------------------
	CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_EditBox() {}; // 
	Jbw_EditBox(Jbw_Handles* handles, int x, int y, int w, int h=14, int Fsize = 12);
	~Jbw_EditBox();

	Jbw_EditBox(const Jbw_EditBox& cp);
	void operator=(const Jbw_EditBox& cp);

/*-----------------------------------------------------------------------------------------
	FUNCTIONS 
------------------------------------------------------------------------------------------*/
public:
	void InitEbx(Jbw_Handles* handles, int x, int y, int w, int h = 14, int Fsize = 12);
	void CreateEbx(void);
	bool SetEbx(std::string  *Var, const char* Val);
	void RdrEbx();
	void EbxEvent(SDL_Event* Event);
	std::string EboxGetS(std::string Property);

	Uint32 static Flashy(Uint32 interval, void* param);

	static void my_function(void)
	{
		int a = 5;
	}

};

