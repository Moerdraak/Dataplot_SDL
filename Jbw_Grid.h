#pragma once
//#include "Jbw_Base.h"
#include "Jbw_Editbox.h"
#include "Jbw_ComboBox.h"
#include "Jbw_Slider.h"

class Jbw_Grid : public Jbw_Frame {
private:
	enum GridProp{ BACK_COLOR, TXT_COLOR, TXT_ALIGN, TXT_SIZE, TXT_BOLD, TXT_ITALIC};
	struct GridVal {
		SDL_Color Color = { 0, 0, 0, 0 };
		J_Type Type = J_NULL;
		int Number = -1;
		bool TrueFalse = false;
	} PropVal;

	Jbw_EditBox* Ebox = NULL;
	Jbw_ComboBox* Cbox = NULL;
	short int RowHeight = 0;

public:
	struct grdEvent {
		int Col = -1;
		int Row = -1;
		J_Type Type = J_NULL;
	} GridEvent;

	Jbw_Slider* SliderV = NULL;
	Jbw_Slider* SliderH = NULL;
	SDL_Rect GridArea = { 0, 0, 0, 0 }; // !!!!!  TO BE DELETED  !!!!!!!!!

	bool SliderVert = false;
	bool SliderHor = false;

	int RdrStartRow = 0;
	int RdrEndRow = 0;
	int RdrStartCol = 0;
	int RdrEndCol = 0;

	short int RowCnt = 0;
	short int ColCnt = 0;
	
	short int TotalW = 0;
	short int TotalH = 0;

	J_Type* ColType = NULL;

	Jbw_TextBox* Header = NULL;
	void** Element = NULL;

	SDL_Color RowColor = { 255, 255, 255, 255 }; // Red, Green, Blue, Alpha}
	SDL_Color ARowColor = { 245, 245, 245, 255 };
	SDL_Color HdrColor = { 220, 220, 220, 255 };
	SDL_Color HdrTxtColor = { 220, 220, 220, 255 };

	/*************************************************/
	/*          Constructors / Destructors           */
	/*-----------------------------------------------*/
	Jbw_Grid() {};
	Jbw_Grid(Jbw_Handles* handles, int x, int y, int w, int h);
	~Jbw_Grid();

//	Jbw_Grid(const Jbw_Grid& cp); // Copy constructor
//	Jbw_Grid& cp operator=(const Jbw_Grid& cp); // Assignment constructor

	/*************************************************/
	/*               Create Functions                */
	/*-----------------------------------------------*/
	void AddCol(Jbw_Handles* handles, std::string Obj, std::string ColName, int Width = 40, J_Type Type = J_EBX);
	void AddRow(Jbw_Handles* handles, int Num = 1, int Height = -1);
	void SetSlider(int TotColW, int TotRowH, bool Vertical);
	void Set(int Col, int Row, double Val);
	void AddCbxLbx(std::string ColName, std::vector<std::string> List);
	//void AddCbxLbx(std::string ColName, std::string* List, int Num);

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
	void SetRowHeight(int h, int Row);
	void RowTxtSize(int Row, int FontSize);
	void TxtSize(int Col, int Row, int FontSize);
	int GetIndex(int Col, int Row);
	std::string GetTxt(int Col, int Row);
	void RdrGrd(void);

	grdEvent GrdEvent(SDL_Event* Event);
};

