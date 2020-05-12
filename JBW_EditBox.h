#pragma once

#include "Jbw_Base.h"
#include "Jbw_TextBox.h"
#include "Jbw_Frame.h"

class Jbw_EditBox : public Jbw_TextBox { 
private: 
	
public: 

/*-----------------------------------------------------------------------------------------
	CONSTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_EditBox() {}; // 
	Jbw_EditBox(Jbw_Handles* handles, int x, int y, int w, int h=14, int Fsize = 12);
	~Jbw_EditBox();

/*-----------------------------------------------------------------------------------------
	FUNCTIONS 
------------------------------------------------------------------------------------------*/
public:
	void InitEbx(Jbw_Handles* handles, int x, int y, int w, int h = 14, int Fsize = 12);
	bool SetEbx(std::string  *Var, const char* Val);
	void RdrEbx(void);
	void EbxEvent(Jbw_Handles* h);
	std::string EboxGetS(std::string Property);

	Uint32 static Flashy(Uint32 interval, void* param);

	static void my_function(void)
	{
		int a = 5;
	}

};

