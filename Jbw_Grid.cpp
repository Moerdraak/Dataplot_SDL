#include "Jbw_Grid.h"

/*---------------------------------------------------------------
CONSTRUCTOR: 
---------------------------------------------------------------*/
Jbw_Grid::Jbw_Grid(SDL_Renderer* Rdr, std::string GridName, int x, int y, int ColNum, int RowNum)
{
	Tag = GridName;
	Xo = x;
	Yo = y;
	if (ColNum > 99) {
		ColNum = 99; // This is way past ridiculous
	}
	Cols = ColNum;
	Rows = RowNum;
	Prdr = Rdr;

	Header = new Jbw_EditBox[ColNum];

	int Xs = Xo;
	int Ys = Yo;
	int w = 50; // Startup values To Be Deleted
	int h = 15; // Startup values To Be Deleted
	
	/*   Setting up the initial Frame  */
	CreateFrame(Rdr, Xo, Yo, 
		ColNum * w - ColNum,
		(RowNum + 1) * h - (RowNum + 1));

//	Frame( 0, 0, 1, 1, 2, 2, 3, 3, 4, 4)

	char TmpName[] = "Col 99 ";
	for (int I = 0; I < ColNum; I++) {
		
		Header[I].Trdr = Rdr;
		Header[I].FontSize = 12;
		Header[I].Align = J_CENTRE; 
		Header[I].BackColor = { 220, 220, 220, 255 };
		Header[I].FrameColor = { 150, 150, 150, 255 };

		// Startup values To Be Deleted
		Header[I].Box.x = Xs+1; Header[I].Box.y = Ys+1; Header[I].Box.w = w-2; Header[I].Box.h = h-2;
		Header[I].Frame.x = Xs; Header[I].Frame.y = Ys; Header[I].Frame.w = w; Header[I].Frame.h = h;
		Xs += w-1;

		sprintf_s(TmpName, "Col %02d", I);
		Header[I].New(TmpName);
	}

	Element = new Jbw_EditBox *[Rows];
	for (int I = 0; I < Rows; I++) {
		Element[I] = new Jbw_EditBox[Cols];
		Ys += h-1;
		Xs = Xo;
		for (int J = 0; J < Cols; J++) {
			Element[I][J].Trdr = Rdr;
			Element[I][J].FontSize = 10;
			Element[I][J].FrameColor = { 200, 200, 200, 255 };
			Element[I][J].Box.x = Xs+1; Element[I][J].Box.y = Ys+1; // Startup values To Be Deleted
			Element[I][J].Box.w = w-2;  Element[I][J].Box.h = h-2; // Startup values To Be Deleted				
			Xs += w-1;
		}
	}
}

/*---------------------------------------------------------------
DESTRUCTOR:
---------------------------------------------------------------*/
Jbw_Grid::~Jbw_Grid()
{
	for (int I = 0; I < Rows; I++) {
			delete Element[I];
	}
	delete Element;
}

/*---------------------------------------------------------------
FUNCTION: 
---------------------------------------------------------------*/
void Jbw_Grid::AddCol(std::string ColName, int Type, int w, int h)
{

}



/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::AddRow(int Num)
{
	Jbw_EditBox** Tmp = new Jbw_EditBox * [Rows + Num];

	Element = new Jbw_EditBox * [Rows];
	for (int I = 0; I < Rows; I++) {
		Element[I] = new Jbw_EditBox[Cols];
//		Ys += h - 1;
//		Xs = Xo;
		for (int J = 0; J < Cols; J++) {
			Element[I][J].Trdr = Prdr;
	//		Element[I][J].TxtType = J_EDIT; // Must be Edit box
			Element[I][J].FrameColor = { 200, 200, 200, 255 };
//			Element[I][J].Box.x = Xs + 1; Element[I][J].Box.y = Ys + 1; // Startup values To Be Deleted
//			Element[I][J].Box.w = w - 2; Element[I][J].Box.h = h - 2; // Startup values To Be Deleted		
//			Xs += w - 1;
		}
	}
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::Set(std::string  Var, const char* Val)
{
	char* Next;
	// Row Color
	if (Var.compare("RowColor") == 0) {
		RowColor.b = (int)strtod(Val, &Next);
		RowColor.g = (int)strtod(Next, &Next);
		RowColor.r = (int)strtod(Next, &Next);
	}
	// Alternative Row Color
	else if (Var.compare("ARowColor") == 0) {
		RowColor.b = (int)strtod(Val, &Next);
		RowColor.g = (int)strtod(Next, &Next);
		RowColor.r = (int)strtod(Next, &Next);
	}
	// Header Row Color
	else if (Var.compare("ARowColor") == 0) {
		RowColor.b = (int)strtod(Val, &Next);
		RowColor.g = (int)strtod(Next, &Next);
		RowColor.r = (int)strtod(Next, &Next);
	}
	// Set FontSize for All Cells
	else if (Var.compare("CellFontSize") == 0) { //
		int FontSize = (int)strtod(Val, NULL);
		for (int I = 0; I < Rows; I++) {
			for (int J = 0; J < Cols; J++) {
				SetCellFontSize(I, J, FontSize);
			}
		}
	}
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellFontSize(int Row, int Col, int FontSize)
{
	Element[Row][Col].FontSize = FontSize;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellFontType(int Row, int Col, int FontSize)
{
	Element[Row][Col].FontSize = FontSize;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellFontColor(int Row, int Col, SDL_Color Color)
{
	Element[Row][Col].FontColor = Color;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellBackColor(int Row, int Col, SDL_Color Color)
{
	Element[Row][Col].BackColor = Color;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetVal(int Row, int Col, int Val)
{

}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetVal(int Row, int Col, std::string Val)
{

}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
std::string Jbw_Grid::Getval(int Row, int Col )
{
	std::string Value;

	return Value;
}

/*---------------------------------------------------------------
FUNCTION: Render Grid
---------------------------------------------------------------*/
void Jbw_Grid::Render(void)
{
	for (int I = 0; I < Rows; I++) {
		for (int J = 0; J < Cols; J++) {
			Element[I][J].Render();
		}
	}	
	for (int I = 0; I < Cols; I++) {
		Header[I].CreateTexture();
		Header[I].FitText();
		Header[I].Render();
	}

	FrameRdr();
}
