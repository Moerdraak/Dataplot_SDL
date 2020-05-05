#include "Jbw_Grid.h"
#include <typeinfo>

/*-----------------------------------------------------------------------------------------
CONSTRUCTOR: 
------------------------------------------------------------------------------------------*/
Jbw_Grid::Jbw_Grid(SDL_Renderer* Rdr, std::string GridName, int x, int y, int NumCol, int NumRow)
{
	Tag.assign(GridName);
	Jrdr = Rdr;

	GridX = x;
	GridY = y;
	RowCnt = NumRow;
	RowHeight = NumCol; // bit of Bullshit here using the FontSize variable for row Height

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
	FUNCTION: InitGrd
------------------------------------------------------------------------------------------*/
bool Jbw_Grid::InitGrd(SDL_Renderer* Rdr, std::string GridName, int x, int y, int NumRow) 
{
	J_Properties Prop;
	Prop.handles.JbwRdr = Rdr;
	Prop.Tag.assign(GridName);
	Prop.x = x;
	Prop.y = y;
	Prop.NumRow = NumRow;
	
	return InitGrd(&Prop);
}
/*-----------------------------------------------------------------------------------------
	FUNCTION: InitGrd
------------------------------------------------------------------------------------------*/
bool Jbw_Grid::InitGrd(J_Properties * Prop) 
{
	Id = Prop->Id;
	Tag.assign(Prop->Tag);
	Jrdr = Prop->handles.JbwRdr;

	GridX = Prop->x;
	GridY = Prop->y;
	RowCnt = Prop->NumRow;
	RowHeight = Prop->Fsize; // bit of Bullshit here using the FontSize variable for row Height
	
	// Frame
	FrameX = GridX;
	FrameY = GridY;

	return true;
}

/*-----------------------------------------------------------------------------------------
FUNCTION: 
------------------------------------------------------------------------------------------*/
void Jbw_Grid::AddCol(Jbw_Handles *handles, std::string Obj, std::string ColName, int Width, J_Type Type)
{
	J_Properties Prop;

	Prop.handles = *handles;
	Prop.x = GridX;
	Prop.y = GridY;
	Prop.w = Width;
	Prop.h = RowHeight;
	
	Prop.x = GridX + TotalW;
	TotalW += Width - 1;
	
	// Create Header
	Jbw_EditBox *TmpHeader = new Jbw_EditBox[ColCnt + 1];
	if (ColCnt > 0) {
		for (int I = 0; I < ColCnt; I++) {
			TmpHeader[I] = Header[I];
		}
		delete[] Header;	
	}
	Header = TmpHeader;

	Header[ColCnt].InitEbx(&Prop);
	Header[ColCnt].Text.assign(ColName);
	Header[ColCnt].TxtSize = 12;
	Header[ColCnt].F_Bold = false;
	Header[ColCnt].Align = J_CENTRE;
	Header[ColCnt].Border.FillColor = J_C_msOver;

	Jbw_EditBox* Eb = NULL; // Element[Row][Col]
	Jbw_ComboBox* Cb = NULL;

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

	void** TmpElement = new void* [ColCnt + 1]; // New memory space

	if (Type == J_EBX) {
		TmpElement[ColCnt] = static_cast<Jbw_EditBox*>(new Jbw_EditBox[RowCnt]);
		Eb = static_cast<Jbw_EditBox*>(TmpElement[ColCnt]);
		for (int I = 0; I < RowCnt; I++) {
			Prop.y += Prop.h - 1;
			Prop.w = Width;
			Eb[I].InitEbx(&Prop);
		}
	} 
	else { // Type == J_CBX
		TmpElement[ColCnt] = static_cast<Jbw_ComboBox*>(new Jbw_ComboBox[RowCnt]);
		Cb = static_cast<Jbw_ComboBox*>(TmpElement[ColCnt]);
		for (int I = 0; I < RowCnt; I++) {
			Prop.y += Prop.h - 1;
			Prop.w = Width;
			Prop.BoolVal = true;
			Cb[I].InitCbx(&Prop);
			Cb[I].CbxEdit.Enabled = false;
		}
	}
	
	if (ColCnt > 0) {
		for (int I = 0; I < ColCnt; I++) {
			TmpElement[I] = Element[I];
		}
		delete Element;
	}

	Element = TmpElement;
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
	Ebox[Row][Col].Border.FillColor = Color;
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
			Ebox[I][Col].Border.FrameW = w;
		}
		for (int I = Col + 1; I < ColCnt; I++) {
			for (int J = 0; J < RowCnt; J++) {
					Ebox[J][I].TbxH += Wdiff - 1;
					Ebox[J][I].Border.FrameX += Wdiff - 1;
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
				Ebox[I][J].Border.FrameH = h + 1;
				Ebox[I][J].Border.FrameY = Ys;
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
			Ebox[Row][I].Border.FrameH = h;
		}
		for (int I = Row + 1; I < RowCnt; I++) {
			for (int J = 0; J < ColCnt; J++) {
				Ebox[I][J].TbxY += Hdiff;
				Ebox[I][J].Border.FrameY += Hdiff;
			}
		}
	}
	CreatePts();
}

/*-----------------------------------------------------------------------------------------
FUNCTION: Render Grid
------------------------------------------------------------------------------------------*/
void Jbw_Grid::RdrGrd(Jbw_Handles* h)
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
				Cb[J].RdrCbx(h);
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
void Jbw_Grid::Event(Jbw_Handles* Handles)
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
				Cb[J].CbxEvent(Handles);
			}
		}
	}
}