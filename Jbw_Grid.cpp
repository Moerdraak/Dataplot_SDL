#include "Jbw_Grid.h"
#include <typeinfo>

/*-----------------------------------------------------------------------------------------
CONSTRUCTOR: 
------------------------------------------------------------------------------------------*/
Jbw_Grid::Jbw_Grid(Jbw_Handles* handles, int x, int y, int NumRow, int RowH)
{
	Jhandle = handles;
	GridX = x;
	GridY = y;
	RowCnt = NumRow;
	RowHeight = RowH; // bit of Bullshit here using the FontSize variable for row Height

	// Frame
	FrameX = GridX;
	FrameY = GridY;
}

/*-----------------------------------------------------------------------------------------
DESTRUCTOR:
------------------------------------------------------------------------------------------*/
Jbw_Grid::~Jbw_Grid()
{
	delete[] Header;
	delete[] ColType;

	Jbw_EditBox* a;

	for (int I = 0; I < ColCnt; I++) {
		a = static_cast<Jbw_EditBox*>(Element[I]);
//		delete a;
	}
	delete[] Element;
}

/*-----------------------------------------------------------------------------------------
FUNCTION: 
------------------------------------------------------------------------------------------*/
void Jbw_Grid::AddCol(Jbw_Handles *handles, std::string Obj, std::string ColName, int Width, 
	J_Type Type)
{
	// Add Header for the collumn
	Jbw_EditBox *TmpHeader = new Jbw_EditBox[ColCnt + 1];
	if (ColCnt > 0) {
		for (int I = 0; I < ColCnt; I++) {
			TmpHeader[I] = Header[I]; // Copy previous headers
		}
		delete[] Header;	
	}
	Header = TmpHeader;

	Header[ColCnt].InitEbx(handles, GridX + TotalW, GridY, Width, RowHeight, 12);
	Header[ColCnt].Text.assign(ColName);
	Header[ColCnt].F_Bold = false;
	Header[ColCnt].Align = J_CENTRE;
	Header[ColCnt].Border->FillColor = J_C_msOver;


	// Keep record of the Collumn Type
	J_Type* TmpColType = new J_Type[ColCnt + 1];

	if (ColCnt == 0) {
		ColType = TmpColType; // new J_Type;
	}
	else {
		for (int I = 0; I < ColCnt; I++) {
			TmpColType[I] = ColType[I];
		}
		delete[] ColType;
		ColType = TmpColType;
	}
	ColType[ColCnt] = Type;

	// Now create the rows for each collumn
	Jbw_EditBox* Eb = NULL; // Element[Col][Row]
	Jbw_ComboBox* Cb = NULL;

	void** TmpElement = new void* [ColCnt + 1]; // New memory space

	if (Type == J_EBX) {
		TmpElement[ColCnt] = static_cast<Jbw_EditBox*>(new Jbw_EditBox[RowCnt]);
		Eb = static_cast<Jbw_EditBox*>(TmpElement[ColCnt]);
		for (int I = 0; I < RowCnt; I++) {
			Eb[I].InitEbx(handles, GridX + TotalW, GridY + (I + 1) * (RowHeight - 1), 
				Width, RowHeight);
		}
	} 
	else { // Type == J_CBX
		TmpElement[ColCnt] = static_cast<Jbw_ComboBox*>(new Jbw_ComboBox[RowCnt]);
		Cb = static_cast<Jbw_ComboBox*>(TmpElement[ColCnt]);
		for (int I = 0; I < RowCnt; I++) {
			Cb[I].InitCbx(handles, GridX + TotalW, GridY + (I + 1) * (RowHeight - 1), 
				Width, RowHeight, true);
			Cb[I].CbxEdit->Enabled = false;
		}
	}
	
	if (ColCnt > 0) {
		for (int I = 0; I < ColCnt; I++) {
			TmpElement[I] = Element[I];
		}
		delete Element;
	}

	Element = TmpElement;

	TotalW += Width - 1;
	ColCnt++;
}

/*-----------------------------------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
void Jbw_Grid::AddRow(int Num)
{

}

/*-----------------------------------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
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
		for (int I = 0; I < RowCnt; I++) {
			for (int J = 0; J < ColCnt; J++) {
				SetCellTxtSize(I, J, TxtSize);
			}
		}
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetCellTxtSize(int Row, int Col, int TxtSize)
{
	Ebox[Row][Col].TxtSize = TxtSize;
}

/*-----------------------------------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetCellFontType(int Row, int Col, int TxtSize)
{
	Ebox[Row][Col].TxtSize = TxtSize;
}

/*-----------------------------------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetCellTxtColor(int Row, int Col, SDL_Color Color)
{
	Ebox[Row][Col].TxtColor = Color;
}

/*-----------------------------------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetCellBackColor(int Row, int Col, SDL_Color Color)
{
	Ebox[Row][Col].Border->FillColor = Color;
}

/*-----------------------------------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetVal(int Row, int Col, int Val)
{

}

/*-----------------------------------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetVal(int Row, int Col, std::string Val)
{
	int I = NULL;

}

/*-----------------------------------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
double Jbw_Grid::GetVal(int Row, int Col )
{
	return Ebox[Row][Col].Value;
}

/*-----------------------------------------------------------------------------------------
FUNCTION: GetTxt
------------------------------------------------------------------------------------------*/
std::string Jbw_Grid::GetTxt(int Row, int Col)
{
	return Ebox[Row][Col].Text;
}

/*-----------------------------------------------------------------------------------------
FUNCTION: RowTxtSize
------------------------------------------------------------------------------------------*/
void Jbw_Grid::RowTxtSize(int Row, int FontSize)
{
	for (int I = 0; I < ColCnt; I++) {
		Ebox[Row][I].TxtSize = FontSize;
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION: RowTxtSize
------------------------------------------------------------------------------------------*/
void Jbw_Grid::TxtSize(int Row, int Col, int FontSize)
{
	for (int I = 0; I < ColCnt; I++) {
		Ebox[Row][I].TxtSize = FontSize;
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION: SetColWidth
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetColWidth(int Col, int w)
{
	int Wdiff = w - Ebox[0][Col].TbxW;

	if (Col == -1){ //Set all Column's the same

	}
	else { // Set Specific Column width
		FrameW += Wdiff - 1; // Set outside Frame with

		for (int I = 0; I < RowCnt; I++) {
			Ebox[I][Col].TbxW = w - 2;
			Ebox[I][Col].Border->FrameW = w;
		}
		for (int I = Col + 1; I < ColCnt; I++) {
			for (int J = 0; J < RowCnt; J++) {
					Ebox[J][I].TbxH += Wdiff - 1;
					Ebox[J][I].Border->FrameX += Wdiff - 1;
			}
		}
	}
	CreatePts(); // Set Outside Grid frame
}

/*-----------------------------------------------------------------------------------------
FUNCTION: SetRowHeight
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetRowHeight(int Row, int h)
{
	int Ys = Ebox[0][0].TbxY;

	if (Row == -1) { //Set all Row's the same
		for (int I = 0; I < RowCnt; I++) {

			for (int J = 0; J < ColCnt; J++) {
				Ebox[I][J].TbxH = h;
				Ebox[I][J].TbxY = Ys;
				Ebox[I][J].Border->FrameH = h + 1;
				Ebox[I][J].Border->FrameY = Ys;
			}
			Ys += h + 1 ;
		}
		FrameH = (RowCnt) * h + RowCnt  ;
	}
	else { // Set Specific Column width
		int Hdiff = h - Ebox[Row][0].TbxH - 2;
		FrameH += Hdiff + 1; // Set outside Frame Height

		for (int I = 0; I < ColCnt; I++) {
			Ebox[Row][I].TbxH = h - 2;
			Ebox[Row][I].Border->FrameH = h;
		}
		for (int I = Row + 1; I < RowCnt; I++) {
			for (int J = 0; J < ColCnt; J++) {
				Ebox[I][J].TbxY += Hdiff;
				Ebox[I][J].Border->FrameY += Hdiff;
			}
		}
	}
	CreatePts();
}

/*-----------------------------------------------------------------------------------------
FUNCTION: Render Grid
------------------------------------------------------------------------------------------*/
void Jbw_Grid::RdrGrd(void)
{
	Jbw_EditBox* Eb = NULL; // [Col][Row]
	Jbw_ComboBox* Cb = NULL;

	for (int I = 0; I < ColCnt; I++) {
		if (ColType[I] == J_EBX) {
			Eb = static_cast<Jbw_EditBox*>(Element[I]);
			for (int J = 0; J < RowCnt; J++) {
				Eb[J].RdrEbx();
			}
		}
		else {
			Cb = static_cast<Jbw_ComboBox*>(Element[I]);
			for (int J = 0; J < RowCnt; J++) {
				Cb[J].RdrCbx();
			}
		}
	}
	for (int I = 0; I < ColCnt; I++) {
		Header[I].CreateTexture();
		Header[I].RdrEbx();
	}

	RdrFrame();
}

/*-----------------------------------------------------------------------------------------
FUNCTION: Event
------------------------------------------------------------------------------------------*/
void Jbw_Grid::GrdEvent(Jbw_Handles* Handles)
{
	for (int I = 0; I < ColCnt; I++) {
		if (ColType[I] == J_EBX) {
			Jbw_EditBox* Eb = static_cast<Jbw_EditBox*>(Element[I]);
			for (int J = 0; J < RowCnt; J++) {
				Eb[J].EbxEvent(Handles);
			}
		}
		else {
			Jbw_ComboBox* Cb = static_cast<Jbw_ComboBox*>(Element[I]);
			for (int J = 0; J < RowCnt; J++) {
				Cb[J].CbxEvent();
			}
		}
	}
}