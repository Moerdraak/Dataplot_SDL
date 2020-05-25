#pragma once
#include "Jbw_Base.h"
#include "Jbw_Editbox.h"
#include "Jbw_ComboBox.h"

class Jbw_Grid : public Jbw_Frame {
private:

public:

	int GridX = 0;
	int GridY = 0;

	short int RowCnt = 0;
	short int ColCnt = 0;
	short int RowHeight = 0;
	short int TotalW = 0;

	J_Type* ColType = NULL;

//	Jbw_EditBox** Ebox = NULL; // DELETE
//	Jbw_ComboBox** Cbox = NULL; // DELETE

	Jbw_EditBox* Header = NULL;
	void** Element = NULL;

	SDL_Color RowColor = { 255, 255, 255, 255 }; // Red, Green, Blue, Alpha}
	SDL_Color ARowColor = { 245, 245, 245, 255 };
	SDL_Color HdrColor = { 220, 220, 220, 255 };
	SDL_Color HdrTxtColor = { 220, 220, 220, 255 };

	/*************************************************/
	/*          Constructors / Destructors           */
	/*-----------------------------------------------*/
	Jbw_Grid() {};
	Jbw_Grid(Jbw_Handles* handles, int x, int y, int NumCol, int NumRowCnt);
	~Jbw_Grid();

	/*************************************************/
	/*               Create Functions                */
	/*-----------------------------------------------*/
	void AddCol(Jbw_Handles* handles, std::string Obj, std::string ColName, int Width = 40, J_Type Type = J_EBX);
	void AddRow(int Num = 1);
	void Set(int Col, int Row, double Val);
	void AddCbxList(std::string ColName, std::vector<std::string> List);
	//void AddCbxList(std::string ColName, std::string* List, int Num);

	void SetVal(int Col, int Row, std::string Val);
	void GrdSet(std::string  *Var, const char* Val);
	void SetCellTxtSize(int Col, int Row, int TxtSize);
	void SetCellFontType(int Col, int Row, int TxtSize);
	void SetCellTxtColor(int Col, int Row, SDL_Color Color);
	void SetCellBackColor(int Col, int Row, SDL_Color Color);
	void SetColWidth(int Col, int w);
	void SetRowHeight(int Row, int h);
	void RowTxtSize(int Row, int FontSize);
	void TxtSize(int Col, int Row, int FontSize);
//	double GetVal(int Col, int Row);
	std::string GetTxt(int Col, int Row);
	void GrdEvent(Jbw_Handles *Handles);
	void RdrGrd(void);
};

