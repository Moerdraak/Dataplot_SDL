#pragma once
#include <stdio.h>
#include <string>
#include "Jbw_Base.h"
#include "Jbw_EditBox.h"
#include "Jbw_ComboBox.h"
#include "Jbw_ListBox.h"
#include "Jbw_MsgBox.h"
#include "Jbw_Text.h"
#include "Jbw_Grid.h"
#include <typeinfo>





/******************************************************************************************
						 CLASS: Jbw_FrameWork                    
******************************************************************************************/
class Jbw_FrameWork : public Jbw_Button {
public:

	SDL_Rect ScreenArea;

	// These Pointers to keep track of all the Objects 
	// by the Base Object
	Jbw_Text* TxtPtr = NULL;
	Jbw_EditBox* EbxPtr = NULL;
	Jbw_ListBox* LbxPtr = NULL;
	Jbw_ComboBox* CbxPtr = NULL;
	Jbw_Button* BtnPtr = NULL;
	Jbw_Grid* GrdPtr = NULL;


	SDL_Point FlashingI[2] = { {500, 500},{ 500, 550} };

	short int TxtCnt = 0;
	short int EbxCnt = 0;
	short int LbxCnt = 0;
	short int CbxCnt = 0;
	short int BtnCnt = 0;
	short int GrdCnt = 0;

	bool Flash = false;
	
	// Give some random default screen size to ease the pain for first time Hello World use
	SDL_Rect GuiArea = { 100, 100, 500, 700 }; 

	Jbw_Handles handles; // Remove the pointer DAMMIT

/*-----------------------------------------------------------------------------------------
		CONSTRUCTORS / DESTRUCTORS
------------------------------------------------------------------------------------------*/
public:
	Jbw_FrameWork(void);
	~Jbw_FrameWork();

/*-----------------------------------------------------------------------------------------
	FUNCTIONS
------------------------------------------------------------------------------------------*/
	void lbxClear(std::string Tag);
	Jbw_MsgBox msg;
	void MsgBox(std::string Title, std::string Msg, int x, int y, int w = 150, int h = 100);

/*-----------------------------------------------------------------------------------------
	CREATE FUNCTIONS
------------------------------------------------------------------------------------------*/
public:
	bool Create(Jbw_Handles* handles, int ObjType, std::string Tag,
		int Xpos, int Ypos, int WidthOrNumCol, int HeightOrNumRowCnt,
		int FontSize = 12, std::string Caption = "");
	bool CreateTxt(J_Properties* Prop);
	bool CreateEbx(J_Properties* Prop);
	bool CreateLbx(J_Properties* Prop);
	bool CreateCbx(J_Properties* Prop);
	bool CreateBtn(J_Properties* Prop);
	bool CreateGrd(J_Properties* Prop);

/*-----------------------------------------------------------------------------------------
	GET / SET FUNCTIONS          
------------------------------------------------------------------------------------------*/
	int Get(std::string Obj, int Type);

	bool Set(std::string Obj, std::string  Prop1, const char* Val1,
		std::string  Prop2 = "NULL", const char* Val2 = "",
		std::string  Prop3 = "NULL", const char* Val3 = "",
		std::string  Prop4 = "NULL", const char* Val4 = "",
		std::string  Prop5 = "NULL", const char* Val5 = "");

	bool GrdSet(std::string Obj, int Row, int Col,
		std::string Prop1,			const char* Val1,
		std::string Prop2 = "NULL", const char* Val2 = "",
		std::string Prop3 = "NULL", const char* Val3 = "",
		std::string Prop4 = "NULL", const char* Val4 = "",
		std::string Prop5 = "NULL", const char* Val5 = "");

	bool GrdAdd(std::string Obj, int RowCol, int Number = 1, std::string ColName = "", int Objtype = J_TXT);


/*-----------------------------------------------------------------------------------------
		FREE FUNCTIONS
------------------------------------------------------------------------------------------*/
	void Free(void);  // Free all Instances

	template<class TmplObj>
	TmplObj FreeSub(TmplObj Obj, TmplObj TmpObj, short int *Size, std::string Tag);

	bool isTag(int Type, int Id, std::string Tag); 
};

