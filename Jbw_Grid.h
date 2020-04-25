#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Jbw_Editbox.h"
#include "Jbw_Frame.h"
#include <string>

class Jbw_Grid : public Jbw_Frame {
private:

public:

	short int Id = 0;
	std::string Tag = "";
	int GridX = 0;
	int GridY = 0;

	short int Rows = 0;
	short int Cols = 0;


	Jbw_EditBox** Element = NULL; // Element[Row][Col]
//	Jbw_EditBox* Header = NULL;

	SDL_Color RowColor = { 255, 255, 255, 255 }; // Red, Green, Blue, Alpha}
	SDL_Color ARowColor = { 245, 245, 245, 255 };
	SDL_Color HdrColor = { 220, 220, 220, 255 };
	SDL_Color HdrTxtColor = { 220, 220, 220, 255 };

	/*************************************************/
	/*          Constructors / Destructors           */
	/*-----------------------------------------------*/
//	Jbw_Grid() {};
	Jbw_Grid(SDL_Renderer* Rdr, std::string GridName, int x, int y, int ColNum, int RowNum);
	~Jbw_Grid();

	/*************************************************/
	/*               Create Functions                */
	/*-----------------------------------------------*/
	void AddCol(std::string ColName, int Type = J_TEXT, int w = 50, int h = 15);
	void AddRow(int Num = 1);
	void SetVal(int Row, int Col, int Val);
	void SetVal(int Row, int Col, std::string Val);
	void Set(std::string  Var, const char* Val);
	void SetCellTxtSize(int Row, int Col, int TxtSize);
	void SetCellFontType(int Row, int Col, int TxtSize);
	void SetCellTxtColor(int Row, int Col, SDL_Color Color);
	void SetCellBackColor(int Row, int Col, SDL_Color Color);
	void SetColWidth(int Col, int w);
	void SetRowHeight(int Row, int h);
	double GetVal(int Row, int Col);
	std::string GetTxt(int Row, int Col);

	void Render(void);
};

