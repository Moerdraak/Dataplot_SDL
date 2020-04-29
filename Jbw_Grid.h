#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Jbw_Base.h"
#include "Jbw_Editbox.h"
#include "Jbw_Frame.h"
#include <string>

class Jbw_Grid : public Jbw_Frame {
private:

public:

	int GridX = 0;
	int GridY = 0;

	short int Rows = 0;
	short int Cols = 0;

	Jbw_EditBox** Element = NULL; // Element[Row][Col]

	SDL_Color RowColor = { 255, 255, 255, 255 }; // Red, Green, Blue, Alpha}
	SDL_Color ARowColor = { 245, 245, 245, 255 };
	SDL_Color HdrColor = { 220, 220, 220, 255 };
	SDL_Color HdrTxtColor = { 220, 220, 220, 255 };

	/*************************************************/
	/*          Constructors / Destructors           */
	/*-----------------------------------------------*/
	Jbw_Grid() {};
	Jbw_Grid(SDL_Renderer* Rdr, std::string GridName, int x, int y, int ColCnt, int RowCnt);
	~Jbw_Grid();

	/*************************************************/
	/*               Create Functions                */
	/*-----------------------------------------------*/
	bool InitGrd(SDL_Renderer* Rdr, std::string GridName, int x, int y, int ColCnt, int RowCnt);

	void AddCol(std::string ColName, int Type = J_TXT, int w = 50, int h = 15);
	void AddRow(int Num = 1);
	void SetVal(int Row, int Col, int Val);
	void SetVal(int Row, int Col, std::string Val);
	void GrdSet(std::string  *Var, const char* Val);
	void SetCellTxtSize(int Row, int Col, int TxtSize);
	void SetCellFontType(int Row, int Col, int TxtSize);
	void SetCellTxtColor(int Row, int Col, SDL_Color Color);
	void SetCellBackColor(int Row, int Col, SDL_Color Color);
	void SetColWidth(int Col, int w);
	void SetRowHeight(int Row, int h);
	void RowTxtSize(int Row, int FontSize);
	void TxtSize(int Row, int Col, int FontSize);
	double GetVal(int Row, int Col);
	std::string GetTxt(int Row, int Col);
	void Event(SDL_Event* e);
	void RdrGrd(void);
};

