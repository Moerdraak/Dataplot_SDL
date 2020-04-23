#pragma once
#include <stdio.h>
#include <string>
#include "Jbw_EditBox.h"
#include "Jbw_ComboBox.h"
#include "Jbw_ListBox.h"
#include "Jbw_MsgBox.h"
#include <typeinfo>
/*************************************************/
/*           Getter & Setter CONSTANTS           */
/*-----------------------------------------------*/

enum Jbw_types : short int { tId, tSize, tEbox, tLbox, tMbox, tCbox };

struct tE {};
struct tL {};
struct tM {};
struct tC {};



const std::string tName = "Name";
const std::string tDescr = "Descr";
/*-----------------------------------------------*/
/*           Getter & Setter CONSTANTS           */
/*************************************************/


/*************************************************/
/*           CLASS: Jbw_Frame                    */
/*-----------------------------------------------*/
class Jbw_Frame {
public:
	Jbw_EditBox** Ebox = NULL; // This Pointer will keep track of all the Objects created by the Base Object
	Jbw_ListBox** Lbox = NULL;
	Jbw_MsgBox** Mbox = NULL;
	Jbw_ComboBox** Cbox = NULL;

	short int Size_E = 0;
	short int Size_L = 0;
	short int Size_M = 0;
	short int Size_C = 0;

public:
	Jbw_EditBox EditBox;
	
	Jbw_Frame() {};		// constructor
	~Jbw_Frame() {
		Free();
	};	// Destructor

	/*************************************************/
	/*               Create Functions                */
	/*-----------------------------------------------*/
	
	Jbw_EditBox* Create(SDL_Renderer* Rdr, tE tType, std::string NewName, J_Type EboxType,
		int x, int y, int w = 200, int h = 14);
	Jbw_ListBox* Create(SDL_Renderer* Rdr, tL tType, std::string NewName);
	Jbw_ComboBox* Create(SDL_Renderer* Rdr, tC tType, std::string NewName);

	/*************************************************/
	/*               Get / Set Functions                */
	/*-----------------------------------------------*/
	int Get(std::string Obj, int Type);

	bool Set(std::string Obj, std::string  Var1, const char* Val1,
		std::string  Var2 = "NULL", const char* Val2 = "",
		std::string  Var3 = "NULL", const char* Val3 = "",
		std::string  Var4 = "NULL", const char* Val4 = "",
		std::string  Var5 = "NULL", const char* Val5 = "");

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
	int Get(int Type) { // Returns the number of Child Instances for the Base Instance
		if (Type == tSize) {
			return Size_E;
		}
	}
};

