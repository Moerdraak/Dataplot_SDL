#include "Jbw_Grid.h"

/*---------------------------------------------------------------
CONSTRUCTOR: 
---------------------------------------------------------------*/
Jbw_Grid::Jbw_Grid(SDL_Renderer* Rdr, std::string GridName, int x, int y, int ColNum, int RowNum)
{
	Tag = GridName;
	GridX = x;
	GridY = y;
	if (ColNum > 99) {
		ColNum = 99; // This is way past ridiculous
	}
	Cols = ColNum;
	Rows = RowNum+1;
	Prdr = Rdr;

//	Header = new Jbw_EditBox[ColNum];

	int Xs = GridX;
	int Ys = GridY;
	int w = 50; // Startup values To Be Deleted
	int h = 15; // Startup values To Be Deleted
	
	/*   Setting up the initial Frame  */
	CreateFrame(Rdr, GridX, GridY, ColNum * (w - 2) + 1 , (RowNum + 1) * h - (RowNum + 1));

	char TmpName[] = "Col 99 ";
	//for (int I = 0; I < ColNum; I++) {
	//	Header[I].InitEditBox(Rdr, Xs, Ys, w, h, 10);
	//	Header[I].Align = J_CENTRE; 
	//	Header[I].BackColor = { 220, 220, 220, 255 };
	//	Header[I].LineColor = { 150, 150, 150, 255 };
	//	sprintf_s(TmpName, "Col %02d", I);
	//	Header[I].New(TmpName);
	//	Xs += w - 2;
	//}

	//Ys += h - 1;
	//Xs = GridX;

	Element = new Jbw_EditBox* [Rows + 1]; // Xtra 1 for heading
	// Do Heading - Row 0
	Element[0] = new Jbw_EditBox[Cols];
	for (int I = 0; I < ColNum; I++) {
		Element[0][I].InitEditBox(Rdr, Xs, Ys, w, h, 10);
		Element[0][I].Align = J_CENTRE;
		Element[0][I].BackColor = { 220, 220, 220, 255 };
		Element[0][I].LineColor = { 100, 100, 100, 255 };

		sprintf_s(TmpName, "Col %02d", I);
		Element[0][I].New(TmpName);
		Xs += w - 2;
	}

	//  Element = new Jbw_EditBox *[Rows];
	for (int I = 1; I < Rows; I++) {
		Element[I] = new Jbw_EditBox[Cols];
		Ys += h - 1;
		Xs = GridX;
		for (int J = 0; J < Cols; J++) {
			Element[I][J].InitEditBox(Rdr, Xs, Ys, w, h, 10);
			Element[I][J].LineColor = { 200, 200, 200, 255 };
			Element[I][J].LineColor = { 0, 0, 225, 255 };
			Xs += w - 2;
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
			Element[I][J].LineColor = { 200, 200, 200, 255 };
//			Element[I][J].EditX = Xs + 1; Element[I][J].EditY = Ys + 1; // Startup values To Be Deleted
//			Element[I][J].EditW = w - 2; Element[I][J].EditH = h - 2; // Startup values To Be Deleted		
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
	// Set TxtSize for All Cells
	else if (Var.compare("CellTxtSize") == 0) { //
		int TxtSize = (int)strtod(Val, NULL);
		for (int I = 0; I < Rows; I++) {
			for (int J = 0; J < Cols; J++) {
				SetCellTxtSize(I, J, TxtSize);
			}
		}
	}
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellTxtSize(int Row, int Col, int TxtSize)
{
	Element[Row][Col].TxtSize = TxtSize;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellFontType(int Row, int Col, int TxtSize)
{
	Element[Row][Col].TxtSize = TxtSize;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellTxtColor(int Row, int Col, SDL_Color Color)
{
	Element[Row][Col].TxtColor = Color;
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
	int I = NULL;

}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
double Jbw_Grid::GetVal(int Row, int Col )
{
	return Element[Row][Col].Value;
}

/*---------------------------------------------------------------
FUNCTION: GetTxt
---------------------------------------------------------------*/
std::string Jbw_Grid::GetTxt(int Row, int Col)
{
	return Element[Row][Col].Text;
}

/*---------------------------------------------------------------
FUNCTION: SetColWidth
---------------------------------------------------------------*/
void Jbw_Grid::SetColWidth(int Col, int w)
{
	int Wdiff = w - Element[0][Col].EditW;

	if (Col == -1){ //Set all Column's the same

	}
	else { // Set Specific Column width
		FrameW += Wdiff - 1; // Set outside Frame with

		for (int I = 0; I < Rows; I++) {
			Element[I][Col].EditW = w - 2;
			Element[I][Col].FrameW = w;

		//	Header[Col].EditW = w - 2;
		//	Header[Col].FrameW = w;
		}
		for (int I = Col + 1; I < Cols; I++) {
		//	Header[I].EditX += Wdiff - 1;
		//	Header[I].FrameX += Wdiff - 1;

			for (int J = 0; J < Rows; J++) {
					Element[J][I].EditX += Wdiff - 1;
					Element[J][I].FrameX += Wdiff - 1;
			}
		}
	}
	SetFrame(); // Set Outside Grid frame
}

/*---------------------------------------------------------------
FUNCTION: SetRowHeight
---------------------------------------------------------------*/
void Jbw_Grid::SetRowHeight(int Row, int h)
{
	int Ys = Element[0][0].EditY;

	if (Row == -1) { //Set all Row's the same
		for (int I = 0; I < Rows; I++) {

			for (int J = 0; J < Cols; J++) {
				Element[I][J].EditH = h;
				Element[I][J].EditY = Ys;
				Element[I][J].FrameH = h + 1;
				Element[I][J].FrameY = Ys;
			}
			Ys += h + 1 ;
		}
		FrameH = (Rows) * h + Rows ;
	}
	else { // Set Specific Column width
		int Hdiff = h - Element[Row][0].EditH - 2;
		FrameH += Hdiff + 1; // Set outside Frame Height

		for (int I = 0; I < Cols; I++) {
			Element[Row][I].EditH = h - 2;
			Element[Row][I].FrameH = h;
		}
		for (int I = Row + 1; I < Rows; I++) {
			for (int J = 0; J < Cols; J++) {
				Element[I][J].EditY += Hdiff;
				Element[I][J].FrameY += Hdiff;
			}
		}
	}
}

/*---------------------------------------------------------------
FUNCTION: Render Grid
---------------------------------------------------------------*/
void Jbw_Grid::Render(void)
{
	for (int I = Rows - 1; I >= 0; I--) { // So that Heading is Rendered last
		for (int J = 0; J < Cols; J++) {
			Element[I][J].CreateTexture();
				Element[I][J].FitText();
			Element[I][J].Render();
		}
	}	
	for (int I = 0; I < Cols; I++) {
//		Header[I].CreateTexture();
//		Header[I].FitText();
//		Header[I].Render();
	}

FrameRdr();
}
