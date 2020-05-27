#pragma once
#include "Jbw_Base.h"
#include "Jbw_Editbox.h"
#include "Jbw_ComboBox.h"

class Jbw_Grid : public Jbw_Frame {
private:
	enum GridProp{ BACK_COLOR, TXT_COLOR, TXT_ALIGN, TXT_SIZE, TXT_BOLD, TXT_ITALIC};
	struct GridVal {
		SDL_Color Color;
		J_Type Type;
		int Number;
		bool TrueFalse;
	} PropVal;

	Jbw_EditBox* Ebox = NULL;
	Jbw_ComboBox* Cbox = NULL;

public:
	struct grdEvent {
		int Col = -1;
		int Row = -1;
		J_Type Type = J_NULL;
	} GridEvent;

	int GridX = 0;
	int GridY = 0;

	short int RowCnt = 0;
	short int ColCnt = 0;
	short int RowHeight = 0;
	short int TotalW = 0;

	J_Type* ColType = NULL;

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

//	void TxtAlign(J_Type TxtAlign, int Col = -1, int Row = -1);
	void GrdSet(std::string  *Var, const char* Val);

	void SetCellText(std::string Txt, int Col, int Row);

private:
	void SetCell(GridProp Property, GridVal Value, int Col = -1, int Row = -1);
	void SetEbox(Jbw_EditBox* Eb, GridProp Property, GridVal Value, int Row);
	void SetCbox(Jbw_ComboBox* Cb, GridProp Property, GridVal Value, int Row);

public:
	void SetCellTxtSize(int TxtSize, int Col, int Row );
	void SetCellFontProp(const char* Property, bool TrueFalse, int Col, int Row );
	void SetCellTxtAlign(J_Type TxtAlign, int Col, int Row );
	void SetCellTxtColor(SDL_Color Color, int Col, int Row);
	void SetCellBackColor(SDL_Color Color, int Col, int Row);


	void SetColWidth(int Col, int w);
	void SetRowHeight(int Row, int h);
	void RowTxtSize(int Row, int FontSize);
	void TxtSize(int Col, int Row, int FontSize);
	int GetIndex(int Col, int Row);
	std::string GetTxt(int Col, int Row);
	grdEvent GrdEvent(Jbw_Handles *Handles);
	void RdrGrd(void);
};

