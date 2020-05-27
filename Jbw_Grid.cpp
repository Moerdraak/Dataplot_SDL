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

	void** TmpElement = new void* [ColCnt + 1]; // New memory space

	if (Type == J_EBX) {
		TmpElement[ColCnt] = static_cast<Jbw_EditBox*>(new Jbw_EditBox[RowCnt]);
		Ebox = static_cast<Jbw_EditBox*>(TmpElement[ColCnt]);
		for (int I = 0; I < RowCnt; I++) {
			Ebox[I].InitEbx(handles, GridX + TotalW, GridY + (I + 1) * (RowHeight - 1),
				Width, RowHeight);
		}
	} 
	else { // Type == J_CBX
		TmpElement[ColCnt] = static_cast<Jbw_ComboBox*>(new Jbw_ComboBox[RowCnt]);
		Cbox = static_cast<Jbw_ComboBox*>(TmpElement[ColCnt]);
		for (int I = 0; I < RowCnt; I++) {
			Cbox[I].InitCbx(handles, GridX + TotalW, GridY + (I + 1) * (RowHeight - 1),
				Width, RowHeight, 12, true);
			Cbox[I].CbxEdit->Enabled = false; // Typically user can't change just select.

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
void Jbw_Grid::SetCellTxtSize(int TxtSize, int Col, int Row)
{
	PropVal.Number = TxtSize;
	SetCell(TXT_SIZE, PropVal, Col, Row);
}

/*-----------------------------------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetCellTxtAlign(J_Type TxtAlign, int Col, int Row)
{
	PropVal.Type = TxtAlign;
	SetCell(TXT_ALIGN, PropVal, Col, Row);
}

/*-----------------------------------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetCellFontProp(const char* Property, bool TrueFalse, int Col, int Row)
{
	PropVal.TrueFalse = TrueFalse;
	if (strcmp(Property, "Bold") == 0) {
		SetCell(TXT_BOLD, PropVal, Col, Row);
	}
	else if(strcmp(Property, "Italic") == 0) {
		SetCell(TXT_ITALIC, PropVal, Col, Row);
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetCellTxtColor(SDL_Color Color, int Col, int Row)
{
	PropVal.Color = Color;
	SetCell(TXT_COLOR, PropVal, Col, Row);
}

/*-----------------------------------------------------------------------------------------
FUNCTION: SetCellBackColor
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetCellBackColor(SDL_Color Color, int Col, int Row)
{
	PropVal.Color = Color;
	SetCell(BACK_COLOR, PropVal, Col, Row);
}

/*-----------------------------------------------------------------------------------------
FUNCTION: SetCell
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetCell(GridProp Property, GridVal Value, int Col, int Row)
{
	if (Col == -1) {
		for (int I = 0; I < ColCnt; I++) {
			if (ColType[I] == J_EBX) {
				Ebox = static_cast<Jbw_EditBox*>(Element[I]);
				if (Row == -1) {
					for (int J = 0; J < RowCnt; J++) {
						SetEbox(Ebox, Property, Value, J);
					}
				}
				else {
					SetEbox(Ebox, Property, Value, Row);
				}
			}
			else {
				Cbox = static_cast<Jbw_ComboBox*>(Element[I]);
				if (Row == -1) {
					for (int J = 0; J < RowCnt; J++) {
						SetCbox(Cbox, Property, Value, J);
					}
				}
				else {
					SetCbox(Cbox, Property, Value, Row);
				}
			}
		}
	}
	else {
		if (ColType[Col] == J_EBX) {
			Ebox = static_cast<Jbw_EditBox*>(Element[Col]);
			if (Row == -1) {
				for (int J = 0; J < RowCnt; J++) {
					SetEbox(Ebox, Property, Value, J);
				}
			}
			else {
				SetEbox(Ebox, Property, Value, Row);
			}
		}
		else {
			Cbox = static_cast<Jbw_ComboBox*>(Element[Col]);
			if (Row == -1) {
				for (int J = 0; J < RowCnt; J++) {
					SetCbox(Cbox, Property, Value, J);
				}
			}
			else {
				SetCbox(Cbox, Property, Value, Row);
			}
		}
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION: SetEbox
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetEbox(Jbw_EditBox* Eb, GridProp Property, GridVal Value, int Row)
{
	switch (Property) {
		case BACK_COLOR:
			Eb[Row].BackColor(Value.Color);
			break;
		case TXT_COLOR:
			Eb[Row].TxtColor = Value.Color;
			Eb[Row].CreateTexture();
			break;
		case TXT_ALIGN:
			Eb[Row].Align = Value.Type;
			break;
		case TXT_SIZE:
			Eb[Row].TxtSize = Value.Number;
			break;
		case TXT_BOLD:
			Eb[Row].F_Bold = Value.TrueFalse;
			break;
		case TXT_ITALIC:
			Eb[Row].F_Italic = Value.TrueFalse;
			break;
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION: void Jbw_Grid::SetCbox(Jbw_ComboBox* Cbox, GridProp Property, GridVal Value, int Row)

------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetCbox(Jbw_ComboBox* Cb, GridProp Property, GridVal Value, int Row)
{
	switch (Property) {
		case BACK_COLOR:
			Cb[Row].CbxEdit->BackColor(Value.Color);
			break;
		case TXT_COLOR:
			Cb[Row].CbxEdit->TxtColor = Value.Color;
			Cb[Row].CbxEdit->CreateTexture();
			break;
		case TXT_ALIGN:
			Cb[Row].CbxEdit->Align = Value.Type;
			break;
		case TXT_SIZE:
			Cb[Row].CbxEdit->TxtSize = Value.Number;
			break;
		case TXT_BOLD:
			Cb[Row].CbxEdit->F_Bold = Value.TrueFalse;
			break;
		case TXT_ITALIC:
			Cb[Row].CbxEdit->F_Italic = Value.TrueFalse;
			break;
	}
}

/*-----------------------------------------------------------------------------------------
void SetCellText(std::string Txt, int Col, int Row)
FUNCTION:
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetCellText(std::string Txt, int Col, int Row)
{
	if (ColType[Col] == J_EBX) { // Edit Box
		Ebox = static_cast<Jbw_EditBox*>(Element[Col]);
		Ebox[Row].Text.assign(Txt);
		Ebox[Row].CreateTexture();
		Ebox[Row].RdrEbx();
	}
	else { // Combo Box
		Cbox = static_cast<Jbw_ComboBox*>(Element[Col]);
		Cbox[Row].CbxList->Index =atoi(Txt.c_str());
		Cbox[Row].CbxEdit->Text.assign(Cbox[Row].CbxList->TxtList[atoi(Txt.c_str())].Text);
		Cbox[Row].CbxEdit->CreateTexture();
		Cbox[Row].CbxEdit->RdrEbx();
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION: Set
------------------------------------------------------------------------------------------*/
void Jbw_Grid::Set(int Col, int Row, double Val)
{
	if (ColType[Col] == J_EBX) { // Edit Box
		Ebox = static_cast<Jbw_EditBox*>(Element[Col]);
		Ebox[Row].Text.assign(std::to_string(Val));
		Ebox[Row].CreateTexture();
		Ebox[Row].RdrEbx();
	}
	else { // Combo Box
		Cbox = static_cast<Jbw_ComboBox*>(Element[Col]);
		Cbox[Row].CbxEdit->Text.assign(std::to_string(Val));
		Cbox[Row].CbxEdit->CreateTexture();
		Cbox[Row].CbxEdit->RdrEbx();
	}
}


/*-----------------------------------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
int Jbw_Grid::GetIndex(int Col, int Row)
{
	if (ColType[Col] == J_EBX) {
		return 0;
	}
	else
	{
		Cbox = static_cast<Jbw_ComboBox*>(Element[Col]);
		return Cbox[Row].CbxList->Index;
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION: GetTxt
------------------------------------------------------------------------------------------*/
std::string Jbw_Grid::GetTxt(int Col, int Row)
{
	std::string Answer = "";

	if (ColType[Col] == J_EBX) {
		Ebox = static_cast<Jbw_EditBox*>(Element[Col]);
		Answer.assign(Ebox[Row].Text);
	}
	else{
		Cbox = static_cast<Jbw_ComboBox*>(Element[Col]);
		Answer.assign(Cbox[Row].CbxEdit->Text);
	}
	return Answer;
}

/*-----------------------------------------------------------------------------------------
FUNCTION: RowTxtSize
------------------------------------------------------------------------------------------*/
void Jbw_Grid::RowTxtSize(int Row, int FontSize)
{
	for (int I = 0; I < ColCnt; I++) {
		//Ebox[Row][I].TxtSize = FontSize;
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION: RowTxtSize
------------------------------------------------------------------------------------------*/
void Jbw_Grid::TxtSize(int Col, int Row, int FontSize)
{
	for (int I = 0; I < ColCnt; I++) {
		//Ebox[Row][I].TxtSize = FontSize;
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION: SetColWidth
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetColWidth(int Col, int w)
{

}

/*-----------------------------------------------------------------------------------------
FUNCTION: SetRowHeight
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetRowHeight(int Row, int h)
{

}

/*-----------------------------------------------------------------------------------------
FUNCTION: AddCbxList
------------------------------------------------------------------------------------------*/
void Jbw_Grid::AddCbxList(std::string ColName, std::vector<std::string> List)
{
	for (int I = 0; I < ColCnt; I++) {
		if (Header[I].Text.compare(ColName) == 0) { // Find correct collumn
			if (ColType[I] == J_EBX) {
				// ERROR
			}
			else{
				Cbox = static_cast<Jbw_ComboBox*>(Element[I]);
				for (int J = 0; J < RowCnt; J++) {
					for (int K = 0; K < size(List); K++) {
						Cbox[J].AddRow(List[K]);
					}
				}
			}
		}
	}
}

/*-----------------------------------------------------------------------------------------
FUNCTION: RdrGrd
------------------------------------------------------------------------------------------*/
void Jbw_Grid::RdrGrd(void)
{
	for (int I = 0; I < ColCnt; I++) {
		if (ColType[I] == J_EBX) {
			Ebox = static_cast<Jbw_EditBox*>(Element[I]);
			for (int J = 0; J < RowCnt; J++) {
				Ebox[J].RdrEbx();
			}
		}
		else {
			Cbox = static_cast<Jbw_ComboBox*>(Element[I]);
			for (int J = 0; J < RowCnt; J++) {
				Cbox[J].RdrCbx();
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
FUNCTION: GrdEvent
------------------------------------------------------------------------------------------*/
Jbw_Grid::grdEvent Jbw_Grid::GrdEvent(Jbw_Handles* Handles)
{
	grdEvent Event;
	for (int I = 0; I < ColCnt; I++) {
		if (ColType[I] == J_EBX) {
			Ebox = static_cast<Jbw_EditBox*>(Element[I]);
			for (int J = 0; J < RowCnt; J++) {
				Ebox[J].EbxEvent(Handles);
				if (Ebox[J].OnChange == true) {
					Ebox[J].OnChange = false; // Has now been handled
					OnChange = true;
					Event.Col = I;
					Event.Row = J;
				}
			}
		}
		else {
			Cbox = static_cast<Jbw_ComboBox*>(Element[I]);
			for (int J = 0; J < RowCnt; J++) {
				Cbox[J].CbxEvent();

				if (Cbox[J].OnChange == true) {
					Cbox[J].OnChange = false; // Has now been handled
					OnChange = true;
					GridEvent.Col = I;
					GridEvent.Row = J;
				}
			}
		}
	}
	return Event;
}