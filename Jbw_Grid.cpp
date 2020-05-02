#include "Jbw_Grid.h"
#include <typeinfo>"
/*---------------------------------------------------------------
CONSTRUCTOR: 
------------------------------------------------------------------------------------------*/
Jbw_Grid::Jbw_Grid(SDL_Renderer* Rdr, std::string GridName, int x, int y, int ColCnt, int RowCnt)
{
	InitGrd(Rdr, GridName, x, y, ColCnt, RowCnt);
}

/*---------------------------------------------------------------
DESTRUCTOR:
------------------------------------------------------------------------------------------*/
Jbw_Grid::~Jbw_Grid()
{
	for (int I = 0; I < Rows; I++) {
			delete Ebox[I];
	}
	delete Ebox;
}

/*---------------------------------------------------------------
	FUNCTION: InitGrd
------------------------------------------------------------------------------------------*/
bool Jbw_Grid::InitGrd(SDL_Renderer* Rdr, std::string GridName, int x, int y, int ColCnt, int RowCnt) {
	
	J_Properties P;
	
	Tag = GridName;
	GridX = x;
	GridY = y;
	Rows = RowCnt;

	Jrdr = Rdr;
	
	
	P.x = GridX; 
	P.y = GridY; 
	P.w = 50; 
	P.h = 15;
	P.Fsize = 10;

	/*   Setting up the initial Frame  */
	FrameX = GridX;
	FrameY = GridY;
	FrameH = Rows * 15; // Starterkit

	return true;
}

/*---------------------------------------------------------------
FUNCTION: 
------------------------------------------------------------------------------------------*/
void Jbw_Grid::AddCol(SDL_Renderer* Rdr, std::string Obj, std::string ColName, int Width, J_Type Type)
{
	J_Properties StarterKit;

	StarterKit.Rdr = Rdr;
	StarterKit.x = GridX;
	StarterKit.y = GridY;
	StarterKit.w = Width;
	StarterKit.h = 15;

	static int TotalW = 0;
	
	StarterKit.x = GridX + TotalW;
	TotalW += Width;

	Jbw_EditBox* Eb = NULL; // Element[Row][Col]
	Jbw_ComboBox* Cb = NULL;

	J_Type* TmpTypeHolder = new J_Type[Cols + 1];

	if (Cols == 0) {
		TypeHolder = new J_Type;
	}
	else {
		for (int I = 0; I < Cols; I++) {
			TmpTypeHolder[I] = TypeHolder[I];
		}
		delete TypeHolder;
		TypeHolder = TmpTypeHolder;
	}
	TypeHolder[Cols] = Type;




	void** TmpElement = new void* [Cols + 1]; // New memory space
	

	if (Type == J_EBX) {
		TmpElement[Cols] = static_cast<Jbw_EditBox*>(new Jbw_EditBox[Rows]);
		Eb = static_cast<Jbw_EditBox*>(TmpElement[Cols]);
		for (int I = 0; I < Rows; I++) {
			StarterKit.y += StarterKit.h;
			StarterKit.w = Width;
			Eb[I].InitEbx(&StarterKit);
		}
	} 
	else { // Type == J_CBX
		TmpElement[Cols] = static_cast<Jbw_ComboBox*>(new Jbw_ComboBox[Rows]);
		Cb = static_cast<Jbw_ComboBox*>(TmpElement[Cols]);
		for (int I = 0; I < Rows; I++) {
			StarterKit.y += StarterKit.h;
			StarterKit.w = Width;
			Cb[I].InitCbx(&StarterKit);
		}
	}
	
	if (Cols > 0) {
		for (int I = 0; I < Cols; I++) {
			if (TypeHolder[I] == J_EBX) {
				TmpElement[I] = static_cast<Jbw_EditBox*>(Element[I]);
			}
			else {
				TmpElement[I] = static_cast<Jbw_ComboBox*>(Element[I]);
			}
		}
		delete Element;
	}

	Element = TmpElement;
	Jbw_EditBox* Eb1 = static_cast<Jbw_EditBox*>(Element[0]);
	Jbw_EditBox* Eb2 = static_cast<Jbw_EditBox*>(Element[1]);
	Jbw_EditBox* Eb3 = static_cast<Jbw_EditBox*>(Element[2]);
	Jbw_EditBox* Eb4 = static_cast<Jbw_EditBox*>(Element[3]);
	Jbw_EditBox* Eb5 = static_cast<Jbw_EditBox*>(Element[4]);
	Jbw_EditBox* Eb6 = static_cast<Jbw_EditBox*>(Element[5]);

	Jbw_ComboBox* Cb1 = static_cast<Jbw_ComboBox*>(Element[6]);
	Jbw_ComboBox* Cb2 = static_cast<Jbw_ComboBox*>(Element[7]);
	Jbw_ComboBox* Cb3 = static_cast<Jbw_ComboBox*>(Element[8]);
	Jbw_ComboBox* Cb4 = static_cast<Jbw_ComboBox*>(Element[9]);

	Jbw_EditBox* Eb7 = static_cast<Jbw_EditBox*>(Element[10]);
	Cols++;
}

/*---------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
void Jbw_Grid::AddRow(int Num)
{
	Jbw_EditBox** Tmp = new Jbw_EditBox * [Rows + Num];

	Ebox = new Jbw_EditBox * [Rows];
	for (int I = 0; I < Rows; I++) {
		Ebox[I] = new Jbw_EditBox[Cols];
		for (int J = 0; J < Cols; J++) {
			Ebox[I][J].Jrdr = Jrdr;
			Ebox[I][J].Border.LineColor = { 200, 200, 200, 255 };
		}
	}
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::GrdSet(std::string  *Var, const char* Val)
{
	char* Next;
	// Row Color
	if (Var->compare("RowColor") == 0) {
		RowColor.b = (int)strtod(Val, &Next);
		RowColor.g = (int)strtod(Next, &Next);
		RowColor.r = (int)strtod(Next, &Next);
	}
	// Alternative Row Color
	else if (Var->compare("ARowColor") == 0) {
		RowColor.b = (int)strtod(Val, &Next);
		RowColor.g = (int)strtod(Next, &Next);
		RowColor.r = (int)strtod(Next, &Next);
	}
	// Header Row Color
	else if (Var->compare("ARowColor") == 0) {
		RowColor.b = (int)strtod(Val, &Next);
		RowColor.g = (int)strtod(Next, &Next);
		RowColor.r = (int)strtod(Next, &Next);
	}
	// Set TxtSize for All Cells
	else if (Var->compare("CellTxtSize") == 0) { 
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
	Ebox[Row][Col].TxtSize = TxtSize;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellFontType(int Row, int Col, int TxtSize)
{
	Ebox[Row][Col].TxtSize = TxtSize;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellTxtColor(int Row, int Col, SDL_Color Color)
{
	Ebox[Row][Col].TxtColor = Color;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellBackColor(int Row, int Col, SDL_Color Color)
{
	Ebox[Row][Col].Border.FillColor = Color;
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
	return Ebox[Row][Col].Value;
}

/*---------------------------------------------------------------
FUNCTION: GetTxt
---------------------------------------------------------------*/
std::string Jbw_Grid::GetTxt(int Row, int Col)
{
	return Ebox[Row][Col].Text;
}

/*---------------------------------------------------------------
FUNCTION: RowTxtSize
---------------------------------------------------------------*/
void Jbw_Grid::RowTxtSize(int Row, int FontSize)
{
	for (int I = 0; I < Cols; I++) {
		Ebox[Row][I].TxtSize = FontSize;
	}
}

/*---------------------------------------------------------------
FUNCTION: RowTxtSize
---------------------------------------------------------------*/
void Jbw_Grid::TxtSize(int Row, int Col, int FontSize)
{
	for (int I = 0; I < Cols; I++) {
		Ebox[Row][I].TxtSize = FontSize;
	}
}

/*---------------------------------------------------------------
FUNCTION: SetColWidth
---------------------------------------------------------------*/
void Jbw_Grid::SetColWidth(int Col, int w)
{
	int Wdiff = w - Ebox[0][Col].EditW;

	if (Col == -1){ //Set all Column's the same

	}
	else { // Set Specific Column width
		FrameW += Wdiff - 1; // Set outside Frame with

		for (int I = 0; I < Rows; I++) {
			Ebox[I][Col].EditW = w - 2;
			Ebox[I][Col].Border.FrameW = w;
		}
		for (int I = Col + 1; I < Cols; I++) {
			for (int J = 0; J < Rows; J++) {
					Ebox[J][I].EditX += Wdiff - 1;
					Ebox[J][I].Border.FrameX += Wdiff - 1;
			}
		}
	}
	CreatePts(); // Set Outside Grid frame
}

/*---------------------------------------------------------------
FUNCTION: SetRowHeight
---------------------------------------------------------------*/
void Jbw_Grid::SetRowHeight(int Row, int h)
{
	int Ys = Ebox[0][0].EditY;

	if (Row == -1) { //Set all Row's the same
		for (int I = 0; I < Rows; I++) {

			for (int J = 0; J < Cols; J++) {
				Ebox[I][J].EditH = h;
				Ebox[I][J].EditY = Ys;
				Ebox[I][J].Border.FrameH = h + 1;
				Ebox[I][J].Border.FrameY = Ys;
			}
			Ys += h + 1 ;
		}
		FrameH = (Rows) * h + Rows  ;
	}
	else { // Set Specific Column width
		int Hdiff = h - Ebox[Row][0].EditH - 2;
		FrameH += Hdiff + 1; // Set outside Frame Height

		for (int I = 0; I < Cols; I++) {
			Ebox[Row][I].EditH = h - 2;
			Ebox[Row][I].Border.FrameH = h;
		}
		for (int I = Row + 1; I < Rows; I++) {
			for (int J = 0; J < Cols; J++) {
				Ebox[I][J].EditY += Hdiff;
				Ebox[I][J].Border.FrameY += Hdiff;
			}
		}
	}
	CreatePts();
}

/*---------------------------------------------------------------
FUNCTION: Render Grid
---------------------------------------------------------------*/
void Jbw_Grid::RdrGrd(void)
{
	Jbw_EditBox* Eb = NULL; // [Col][Row]
	Jbw_ComboBox* Cb = NULL;

	Jbw_Handles h;
	h.JbwRdr = Jrdr;

	for (int I = 0; I < Cols; I++) {
		if (TypeHolder[I] == J_EBX) {
			Eb = static_cast<Jbw_EditBox*>(Element[I]);
			for (int J = 0; J < Rows; J++) {
				Eb[J].RdrEbx();
			}
		}
		else {
			Cb = static_cast<Jbw_ComboBox*>(Element[I]);
			for (int J = 0; J < Rows; J++) {
				Cb[J].RdrCbx(h);
			}
		}
	}

	RdrFrame();
}

/*---------------------------------------------------------------
FUNCTION: Event
---------------------------------------------------------------*/
void Jbw_Grid::Event(SDL_Event* e)
{
	for (int I = Rows - 1; I >= 0; I--) { // So that Heading is Rendered last
		for (int J = 0; J < Cols; J++) {
			Ebox[I][J].EbxEvent(e);
		}
	}
}