#pragma once
#include <stdio.h>
#include <string>
#include "Jbw_EditBox.h"
#include "Jbw_ComboBox.h"
#include "Jbw_ListBox.h"
#include "Jbw_MsgBox.h"
#include "Jbw_Text.h"
#include "Jbw_Grid.h"
#include <typeinfo>

//#define tString = 0;
//#define tEdit = 1;
//#define tList = 2;
//#define tCombo = 3;
//#define tGrid = 4;


/*************************************************/
/*           Getter & Setter CONSTANTS           */
/*-----------------------------------------------*/

//enum Jbw_types : short int { tId, tSize, tEbox, tLbox, tCbox, tGrid };

struct tT {};
struct tE {};
struct tL {};
struct tC {};
struct tG {};
struct tS {};

const std::string tName = "Name";
const std::string tDescr = "Descr";
/*-----------------------------------------------*/
/*           Getter & Setter CONSTANTS           */
/*************************************************/


/*************************************************/
/*           CLASS: Jbw_Frame                    */
/*-----------------------------------------------*/
class Jbw_FrameWork {
public:
	// This Pointers to keep track of all the Objects created 
	// by the Base Object
	Jbw_Text** Jtext = NULL;
	Jbw_EditBox** Ebox = NULL; 
	Jbw_ListBox** Lbox = NULL;
	Jbw_ComboBox** Cbox = NULL;
	Jbw_Grid** Grid = NULL;

	short int Size_T = 0;
	short int Size_E = 0;
	short int Size_L = 0;
	short int Size_C = 0;
	short int Size_G = 0;

public:
	Jbw_EditBox EditBox;
	
	Jbw_FrameWork() {};		// constructor
	~Jbw_FrameWork() {
		Free();
	};	// Destructor

	/*************************************************/
	/*               Create Functions                */
	/*-----------------------------------------------*/
	
	Jbw_Text* Create(SDL_Renderer* Rdr, tT tType, std::string NewName,
		std::string TxtString, int x, int y, int Fsize);

	Jbw_EditBox* Create(SDL_Renderer* Rdr, tE tType, std::string NewName, J_Type EboxType,
		int x, int y, int w = 200, int h = 14);
	
	Jbw_ListBox* Create(SDL_Renderer* Rdr, tL tType, std::string NewName);
	
	Jbw_ComboBox* Create(SDL_Renderer* Rdr, tC tType, std::string NewName);

	Jbw_Grid* Create(SDL_Renderer* Rdr, tG tType, std::string GridName, 
		int x = 10, int y = 10, int ColNum = 5, int RowNum = 3);


	void Add(std::string Obj, int RowCol, int Number = 1, std::string ColName = "");

	/*************************************************/
	/*               Get / Set Functions             */
	/*-----------------------------------------------*/
	int Get(std::string Obj, int Type);

	bool Set(std::string Obj, std::string  Var1, const char* Val1,
		std::string  Var2 = "NULL", const char* Val2 = "",
		std::string  Var3 = "NULL", const char* Val3 = "",
		std::string  Var4 = "NULL", const char* Val4 = "",
		std::string  Var5 = "NULL", const char* Val5 = "");

	//void Set(std::string Obj,  std::string  Var1, const char* Val1,
	//	std::string  Var2 = "NULL", const char* Val2 = "",
	//	std::string  Var3 = "NULL", const char* Val3 = "",
	//	std::string  Var4 = "NULL", const char* Val4 = "",
	//	std::string  Var5 = "NULL", const char* Val5 = "");


	/*************************************************/
	/*               Render Functions                */
	/*-----------------------------------------------*/
	void Render(std::string Obj); // Individual Render


	/*************************************************/
	/*               Free Functions                */
	/*-----------------------------------------------*/
	void Free(void);  // Free all Instances
	void Free(tE T, std::string Tag); // Free Edit box Instance 
	void Free(tL T, std::string Tag); // Free Edit box Instance 
//	void Free(tM T, std::string Tag); // Free Edit box Instance 
	void Free(tC T, std::string Tag); // Free Edit box Instance 

	template<class TmplObj>
	TmplObj FreeSub(TmplObj Obj, TmplObj TmpObj, short int *Size, std::string Tag);

	void Free(int Id); // Free one of the Child Instances by Id

};

