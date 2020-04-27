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


/*************************************************/
/*           CLASS: Jbw_Frame                    */
/*-----------------------------------------------*/
class Jbw_FrameWork : public Jbw_Base{
public:

	// These Pointers to keep track of all the Objects 
	// by the Base Object
	Jbw_Text* TxtPtr = NULL;
	Jbw_EditBox* EbxPtr = NULL;
	Jbw_ListBox* LbxPtr = NULL;
	Jbw_ComboBox* CbxPtr = NULL;
	Jbw_Grid* GrdPtr = NULL;

	SDL_Event *e = new SDL_Event;
	SDL_Point FlashingI[2] = { {500, 500},{ 500, 550} };

	short int TxtCnt = 0;
	short int EbxCnt = 0;
	short int LbxCnt = 0;
	short int CbxCnt = 0;
	short int GrdCnt = 0;

	bool Flash = false;

	SDL_Renderer* J_Rdr = NULL;

	/*************************************************/
	/*           CONSTRUCTOR / DESTRUCTOR            */
	/*-----------------------------------------------*/
	Jbw_FrameWork(void);
	~Jbw_FrameWork() {
	//	Free();
	};	

	/*************************************************/
	/*               Create Functions                */
	/*-----------------------------------------------*/
	bool Create(SDL_Renderer* Rdr, int ObjType, std::string Tag,
		int Xpos, int Ypos, int WidthOrColCnt, int HeightOrRowCnt,
		int FontSize = 12, std::string Caption = "");
	bool CreateTxt(J_Properties* Prop);
	bool CreateEbx(J_Properties* Prop);
	bool CreateLbx(J_Properties* Prop);
	bool CreateCbx(J_Properties* Prop);
	bool CreateGrd(J_Properties* Prop);

	/*************************************************/
	/*               Get / Set Functions             */
	/*-----------------------------------------------*/
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


	/*************************************************/
	/*               Free Functions                */
	/*-----------------------------------------------*/
	void Free(void);  // Free all Instances

	template<class TmplObj>
	TmplObj FreeSub(TmplObj Obj, TmplObj TmpObj, short int *Size, std::string Tag);

	bool isTag(int Type, int Id, std::string Tag) {
		bool Flag = false;

		switch (Type){
			case J_TXT:
				if (Tag.compare(TxtPtr[Id].Tag) == 0) {
					Flag =  true;
				}
				break;
			case J_EBX:
				if (Tag.compare(EbxPtr[Id].Tag) == 0) {
					Flag = true;
				}
				break;
			case J_LBX:
				if (Tag.compare(LbxPtr[Id].Tag) == 0) {
					Flag = true;	
				}
				break;
			case J_CBX:
				if (Tag.compare(CbxPtr[Id].Tag) == 0) {
					Flag = true;
				}
				break;
			case J_GRD:
				if (Tag.compare(GrdPtr[Id].Tag) == 0) {
					Flag = true;	
				}
				break;
			default:
				return false;
		}
		return Flag;
	}
};

