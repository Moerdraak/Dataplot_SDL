#include "Jbw_Grid.h"
#include <typeinfo>

/*-----------------------------------------------------------------------------------------
CONSTRUCTOR: 
------------------------------------------------------------------------------------------*/
Jbw_Grid::Jbw_Grid(Jbw_Handles* handles, int x, int y, int w, int h)
{
	GridArea.x = x + 1;
	GridArea.y = y + 1;
	GridArea.w = w - 2 - 14; // SliderW = 14
	GridArea.h = h - 2 - 14; // SliderH = 14

	Obj.x = x;
	Obj.y = y;
	Obj.w = w;
	Obj.h = h;
	CreateFrame();

	Jhandle = handles;
	RowHeight = 17; // Nice general value

	// Determine amount of rows that will fit in
	RowCnt = 1; // ALways have one blank row 
	// RowCnt =(short int)floor(h / RowHeight);
	
	// Creating Slider
	SliderV = new Jbw_Slider(handles, GridArea.x + GridArea.w, GridArea.y, 14, GridArea.h, 10, true);
	SliderH = new Jbw_Slider(handles, GridArea.x , GridArea.y + GridArea.h, GridArea.w, 14, 10, false);
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
		delete a;
	}
	delete[] Element;
}

/*-----------------------------------------------------------------------------------------
	COPY CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Grid::Jbw_Grid(const Jbw_Grid& cp) : Jbw_Frame(cp)
{

}

/*-----------------------------------------------------------------------------------------
	ASIGNMENT OPERATOR OVERLOAD
------------------------------------------------------------------------------------------*/
void Jbw_Grid::operator=(const Jbw_Grid& cp) {

}
/*-----------------------------------------------------------------------------------------
FUNCTION: 
------------------------------------------------------------------------------------------*/
void Jbw_Grid::AddCol(Jbw_Handles *handles, std::string Obj, std::string ColName, int Width, 
	J_Type Type)
{
	// Add Header for the Collumn
	Jbw_TextBox* TmpHeader = new Jbw_TextBox[ColCnt + 1];
	if (ColCnt > 0) {
		for (int I = 0; I < ColCnt; I++) {
			TmpHeader[I] = Header[I]; // Copy previous headers
		}
		delete[] Header;	
	}
	Header = TmpHeader;

	// Format the Header
	Header[ColCnt].InitTbx(handles, ColName, 0, 0, Width, RowHeight, 12);
	Header[ColCnt].F_Bold = false;
	Header[ColCnt].Align = J_CENTRE;
	Header[ColCnt].BorderColor(J_C_Frame);
	Header[ColCnt].BackColor(J_C_msOver);
	Header[ColCnt].FillOn = true;
	Header[ColCnt].FrameOn = true;

	// Add Collumn Type
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
	TotalH = RowHeight - 1; // For Header

	// Add New Elements for Collumn
	void** TmpElement = new void* [ColCnt + 1]; // New memory space

	if (Type == J_EBX) { // Create Edit Box
		TmpElement[ColCnt] = static_cast<Jbw_EditBox*>(new Jbw_EditBox[RowCnt]);
		Ebox = static_cast<Jbw_EditBox*>(TmpElement[ColCnt]);
		for (int I = 0; I < RowCnt; I++) {
			Ebox[I].InitEbx(handles, 0, 0, Width, RowHeight);
			TotalH += RowHeight - 1;
		}
	} 
	else { /// Create Combo Box
		TmpElement[ColCnt] = static_cast<Jbw_ComboBox*>(new Jbw_ComboBox[RowCnt]);
		Cbox = static_cast<Jbw_ComboBox*>(TmpElement[ColCnt]);
		for (int I = 0; I < RowCnt; I++) {
			Cbox[I].InitCbx(handles, 0, 0, Width, RowHeight, 12, true);
			Cbox[I].CbxEdit->Enabled = false; // Typically user can't change just select.
			TotalH += RowHeight - 1;
		}
	}
	
	// Copy previous Elements into TmpElement
	if (ColCnt > 0) {
		for (int I = 0; I < ColCnt; I++) {
			TmpElement[I] = Element[I];
		}
		delete[] Element;
	}

	Element = TmpElement;
	TotalW += Width - 1;
	
	// Setup Sliders
	SetSlider(TotalW, TotalH, true); // Set Vertical slider

	ColCnt++;

	/* Ebox and Cbox has done there jobs. The memory remains, which is now referenced by Element
		but for safety remove the references from Ebox and Cbox */
	Ebox = NULL;
	Cbox = NULL;
}


/*-----------------------------------------------------------------------------------------
FUNCTION: AddRow
------------------------------------------------------------------------------------------*/
void Jbw_Grid::AddRow(Jbw_Handles* handles, int Num, int Height)
{
	if (Height == -1) { // User didn't specify
		Height = RowHeight;
	}

	void** TmpElement = new void* [ColCnt]; 
	
	// First Copy all existing elements
	for (int I = 0; I < ColCnt; I++) {
		if (ColType[I] == J_EBX) {
			Ebox = static_cast<Jbw_EditBox*>(Element[I]);
			// Make space for Old Rows + New Rows
			TmpElement[I] = static_cast<Jbw_EditBox*>(new Jbw_EditBox[RowCnt + Num]); 
			Jbw_EditBox* TmpEbox = static_cast<Jbw_EditBox*>(TmpElement[I]);
			 
			// Copy all existing Rows
			for (int J = 0; J < RowCnt; J++) {
				TmpEbox[J] = Ebox[J];
			}
			
			// Initialise new Rows
			for (int J = 0; J < Num; J++) {
				TmpEbox[RowCnt + J].InitEbx(handles, 0, 0, Ebox[0].Obj.w, Height);
				// OR CONSIDER
				// TmpEbox[RowCnt + J] = Ebox[RowCnt - 1];
				TotalH += Height;
			}
			delete[] Ebox; // Free old memory
			Ebox = NULL;
		}
		else {
			Cbox = static_cast<Jbw_ComboBox*>(Element[I]);
			// Make space for Old Rows + New Rows
			TmpElement[I] = static_cast<Jbw_ComboBox*>(new Jbw_ComboBox[RowCnt + Num]);
			Jbw_ComboBox* TmpCbox = static_cast<Jbw_ComboBox*>(TmpElement[I]);

			// Copy all existing Rows
			for (int J = 0; J < RowCnt; J++) {
				TmpCbox[J] = Cbox[J];
			}

			// Initialise new Rows
			for (int J = 0; J < Num; J++) {
				TmpCbox[RowCnt + J] = TmpCbox[RowCnt - 1];
				TotalH += Height;
			}
			delete[] Cbox; // Free old memory
			Cbox = NULL;
		}	
	}
	delete[] Element;
	Element = TmpElement;
	RowCnt += Num;
}
/*-----------------------------------------------------------------------------------------
FUNCTION: SetSlider
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetSlider(int TotColW, int TotRowH, bool Vertical)
{
	// Horisontal Slider settings
	if (TotColW > Obj.w - SliderV->Obj.w - 2) {
		SliderHor = true;

		int ColOutside = (TotColW - (Obj.w - SliderV->Obj.w - 2)) / (TotColW / ColCnt) + 1;
	
		SliderH->Slider->Obj.w = SliderH->Obj.w / ColOutside;
		if (SliderH->Slider->Obj.w < 5) {
			SliderH->Slider->Obj.w = 5;

		}
		SliderH->StepSize = (float)(SliderH->Obj.w - 2 - SliderH->Slider->Obj.w) / (ColOutside + 1);
	}
	else {
		SliderHor = false;
	}

	// Vertical Slider settings
	if (TotRowH > Obj.h - SliderH->Obj.h - 2) {
		SliderVert = true;

		int RowOutside = (TotRowH - (Obj.h - SliderH->Obj.h - 2)) / (TotRowH / (RowCnt + 1)) + 1;

		SliderV->Slider->Obj.h = SliderV->Obj.h / RowOutside;
		if (SliderV->Slider->Obj.h < 5) {
			SliderV->Slider->Obj.h = 5;

		}
		SliderV->StepSize = (float)(SliderV->Obj.h - 2 - SliderV->Slider->Obj.h) / (RowOutside + 1);
	}
	else {
		SliderVert = false;
	}
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

	/* Ebox and Cbox has done there jobs. The memory remains, which is now referenced by Element
		but for safety remove the references from Ebox and Cbox */
	Ebox = NULL;
	Cbox = NULL;
}

/*-----------------------------------------------------------------------------------------
FUNCTION: SetEbox
------------------------------------------------------------------------------------------*/
void Jbw_Grid::SetEbox(Jbw_EditBox* Eb, GridProp Property, GridVal Value, int Row)
{
	switch (Property) {
		case BACK_COLOR:
			Eb[Row].Tbx->BackColor(Value.Color);
			break;
		case TXT_COLOR:
			Eb[Row].Tbx->TxtColor = Value.Color;
			Eb[Row].Tbx->CreateTexture();
			break;
		case TXT_ALIGN:
			Eb[Row].Tbx->Align = Value.Type;
			break;
		case TXT_SIZE:
			Eb[Row].Tbx->TxtSize = Value.Number;
			break;
		case TXT_BOLD:
			Eb[Row].Tbx->F_Bold = Value.TrueFalse;
			break;
		case TXT_ITALIC:
			Eb[Row].Tbx->F_Italic = Value.TrueFalse;
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
			Cb[Row].CbxEdit->Tbx->BackColor(Value.Color);
			break;
		case TXT_COLOR:
			Cb[Row].CbxEdit->Tbx->TxtColor = Value.Color;
			Cb[Row].CbxEdit->Tbx->CreateTexture();
			break;
		case TXT_ALIGN:
			Cb[Row].CbxEdit->Tbx->Align = Value.Type;
			break;
		case TXT_SIZE:
			Cb[Row].CbxEdit->Tbx->TxtSize = Value.Number;
			break;
		case TXT_BOLD:
			Cb[Row].CbxEdit->Tbx->F_Bold = Value.TrueFalse;
			break;
		case TXT_ITALIC:
			Cb[Row].CbxEdit->Tbx->F_Italic = Value.TrueFalse;
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
		Ebox[Row].Tbx->Text.assign(Txt);
		Ebox[Row].Tbx->CreateTexture();
		Ebox[Row].RdrEbx();
	}
	else { // Combo Box
		Cbox = static_cast<Jbw_ComboBox*>(Element[Col]);
		Cbox[Row].CbxList->Index =atoi(Txt.c_str());
		Cbox[Row].CbxEdit->Tbx->Text.assign(Cbox[Row].CbxList->TxtList[atoi(Txt.c_str())].Text);
		Cbox[Row].CbxEdit->Tbx->CreateTexture();
		Cbox[Row].CbxEdit->RdrEbx();
	}
	/* Ebox and Cbox has done there jobs. For safety remove the references from Ebox and Cbox */
	Ebox = NULL;
	Cbox = NULL;
}

/*-----------------------------------------------------------------------------------------
FUNCTION: Set
------------------------------------------------------------------------------------------*/
void Jbw_Grid::Set(int Col, int Row, double Val)
{
	if (ColType[Col] == J_EBX) { // Edit Box
		Ebox = static_cast<Jbw_EditBox*>(Element[Col]);
		Ebox[Row].Tbx->Text.assign(std::to_string(Val));
		Ebox[Row].Tbx->CreateTexture();
		Ebox[Row].RdrEbx();
	}
	else { // Combo Box
		Cbox = static_cast<Jbw_ComboBox*>(Element[Col]);
		Cbox[Row].CbxEdit->Tbx->Text.assign(std::to_string(Val));
		Cbox[Row].CbxEdit->Tbx->CreateTexture();
		Cbox[Row].CbxEdit->RdrEbx();
	}
	/* Ebox and Cbox has done there jobs. For safety remove the references from Ebox and Cbox */
	Ebox = NULL;
	Cbox = NULL;
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
		Answer.assign(Ebox[Row].Tbx->Text);
	}
	else{
		Cbox = static_cast<Jbw_ComboBox*>(Element[Col]);
		Answer.assign(Cbox[Row].CbxEdit->Tbx->Text);
	}

	/* Ebox and Cbox has done there jobs. For safety remove the references from Ebox and Cbox */
	Ebox = NULL;
	Cbox = NULL;

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
void Jbw_Grid::SetRowHeight(int h, int Row)
{	
	RowHeight = h;

	for (int I = 0; I < ColCnt; I++) {
		if (ColType[I] == J_EBX) {
			Ebox = static_cast<Jbw_EditBox*>(Element[I]);
			if (Row == -1) {
				for (int J = 0; J < RowCnt; J++) {
					Ebox[J].Obj.h = RowHeight;
					Ebox[J].CreateEbx();
				}
			}
			else {
				Ebox[Row].Obj.h = RowHeight;
				Ebox[Row].CreateEbx();
			}
		}
		else {
			Cbox = static_cast<Jbw_ComboBox*>(Element[I]);
			if (Row == -1) {
				for (int J = 0; J < RowCnt; J++) {
					Cbox[J].Obj.h = RowHeight;
					Cbox[J].CreateCbx();
				}
			}
			else {
				Cbox[Row].Obj.h = RowHeight;
				Cbox[Row].CreateCbx();
			}
		}
	}

	/* Ebox and Cbox has done there jobs. For safety remove the references from Ebox and Cbox */
	Ebox = NULL;
	Cbox = NULL;
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
	int TotW = 0;
	for (int I = StartCol; I < ColCnt; I++) {
		int TotH = Header[0].Obj.h - 1;

		if (ColType[I] == J_EBX) {
			Ebox = static_cast<Jbw_EditBox*>(Element[I]);
			if (TotW + Ebox[0].Tbx->Obj.w <= Obj.w - 2 - 14) {
				for (int J = StartRow; J < RowCnt; J++) {
					if (TotH + Ebox[J].Tbx->Obj.h <= Obj.h - 2 - 14) {
						Ebox[J].Obj.x = Obj.x + 1 + TotW;
						Ebox[J].Obj.y = Obj.y + 1 + TotH;
						Ebox[J].CreateEbx();
						TotH += Ebox[J].Tbx->Obj.h - 1;
						Ebox[J].RdrEbx(); // Now Render this box
					}
					else if (TotH <= Obj.h - 2 - 14) { // Adjust height of this box to fit
						Ebox[J].Obj.x = Obj.x + 1 + TotW;
						Ebox[J].Obj.y = Obj.y + 1 + TotH;
						Ebox[J].Obj.h = (Obj.h - 14) - TotH - 1;
						Ebox[J].CreateEbx();
						Ebox[J].RdrEbx(); // Now Render this box
						break;
					}
				}
			}
			else {
				for (int J = StartRow; J < RowCnt; J++) {
					if (TotH + Ebox[J].Tbx->Obj.h <= Obj.h - 2 - 14) {
						Ebox[J].Obj.x = Obj.x + 1 + TotW;
						Ebox[J].Obj.y = Obj.y + 1 + TotH;
						Ebox[J].Obj.w = (Obj.w - 14) - TotW - 1;
						Ebox[J].CreateEbx();
						TotH += Ebox[J].Tbx->Obj.h - 1;
						Ebox[J].RdrEbx(); // Now Render this box
					}
					else if (TotH <= Obj.h - 2 - 14) { // Adjust height of this box to fit
						Ebox[J].Obj.x = Obj.x + 1 + TotW;
						Ebox[J].Obj.y = Obj.y + 1 + TotH;
						Ebox[J].Obj.w = (Obj.w - 14) - TotW - 1;
						Ebox[J].Obj.h = (Obj.h - 14) - TotH - 1;
						Ebox[J].CreateEbx();
						Ebox[J].RdrEbx(); // Now Render this box
						break;
					}
				}
			}
			TotW += Ebox[0].Tbx->Obj.w - 1;
		}
		else {
			Cbox = static_cast<Jbw_ComboBox*>(Element[I]);
			if (TotW + Cbox[0].Obj.w <= Obj.w - 2 - 14) {
				for (int J = StartRow; J < RowCnt; J++) {
					if (TotH + Cbox[J].Obj.h <= Obj.h - 2 - 14) {
						Cbox[J].Obj.x = Obj.x + 1 + TotW;
						Cbox[J].Obj.y = Obj.y + 1 + TotH;
						Cbox[J].CreateCbx();
						TotH += Cbox[J].Obj.h - 1;
						Cbox[J].RdrCbx(); // Now Render this box
					}
					else if (TotH <= Obj.h - 2 - 14) { // Adjust height of this box to fit
						Cbox[J].Obj.x = Obj.x + 1 + TotW;
						Cbox[J].Obj.y = Obj.y + 1 + TotH;
						Cbox[J].Obj.h = (Obj.h - 14) - TotH - 1;
						Cbox[J].CreateCbx();
						Cbox[J].RdrCbx(); // Now Render this box
						break;
					}
				}
			}
			else {
				for (int J = StartRow; J < RowCnt; J++) {
					if (TotH + Cbox[J].Obj.h <= Obj.h - 2 - 14) {
						Cbox[J].Obj.x = Obj.x + 1 + TotW;
						Cbox[J].Obj.y = Obj.y + 1 + TotH;
						Cbox[J].Obj.w = (Obj.w - 14) - TotW - 1;
						Cbox[J].CreateCbx();
						TotH += Cbox[J].Obj.h - 1;
						Cbox[J].RdrCbx(); // Now Render this box
					}
					else if (TotH <= Obj.h - 2 - 14) { // Adjust height of this box to fit
						Cbox[J].Obj.x = Obj.x + 1 + TotW;
						Cbox[J].Obj.y = Obj.y + 1 + TotH;
						Cbox[J].Obj.w = (Obj.w - 14) - TotW - 1;
						Cbox[J].Obj.h = (Obj.h - 14) - TotH - 1;
						Cbox[J].CreateCbx();
						Cbox[J].RdrCbx(); // Now Render this box
						break;
					}
				}
			}
			TotW += Cbox[0].Obj.w - 1;
		}
	}

	// Render the Header
	TotW = 0;
	int TotH = 0;
	for (int I = 0; I < ColCnt; I++) {
		if (TotW + Header[I].Obj.w <= Obj.w - 2 - 14) {
			Header[I].Obj.x = Obj.x + 1 + TotW;
			Header[I].Obj.y = Obj.y + 1;
			Header[I].CreateTbx();
			TotW += Header[I].Obj.w - 1;
			Header[I].RdrTbx();// Now Render this box
		}
		else if (TotW <= Obj.w - 2 - 14) { // Adjust height of this box to fit
			Header[I].Obj.x = Obj.x + 1 + TotW;
			Header[I].Obj.y = Obj.y + 1 + TotH;
			Header[I].Obj.w = (Obj.w - 14) - TotW - 1;
			Header[I].CreateTbx();
			Header[I].RdrTbx(); // Now Render this box
			break;
		}
		Header[I].CreateTexture();
		Header[I].RdrTbx();
	}
	if (SliderVert == true) {
		SliderV->RdrSldr();
	}
	if (SliderHor == true) {
		SliderH->RdrSldr();
	}
	
	/* Ebox and Cbox has done there jobs. For safety remove the references from Ebox and Cbox */
	Ebox = NULL;
	Cbox = NULL;

	RdrFrame();
}

/*-----------------------------------------------------------------------------------------
FUNCTION: GrdEvent
------------------------------------------------------------------------------------------*/
Jbw_Grid::grdEvent Jbw_Grid::GEvent(SDL_Event * Event)
{
	grdEvent Ev;

	// Test if mouse is inside Grid Window
	if (Event->window.event == SDL_WINDOWEVENT_ENTER && 
		Event->window.windowID == SDL_GetWindowID(grdHandles.JbwGui)){
		msOver = true;
		return Ev; 
	}
	else if (Event->window.event == SDL_WINDOWEVENT_LEAVE &&
		Event->window.windowID == SDL_GetWindowID(grdHandles.JbwGui)) {
		msOver = false;
		return Ev; 
	}
	if (Event->type == SDL_MOUSEMOTION && msOver == false) { 
	//	return Ev; // Don't bother any further
	}

	for (int I = 0; I < ColCnt; I++) {
		if (ColType[I] == J_EBX) {
			Ebox = static_cast<Jbw_EditBox*>(Element[I]);
			for (int J = 0; J < RowCnt; J++) {
				Ebox[J].EbxEvent(Event);
				if (Ebox[J].OnChange == true) {
					Ebox[J].OnChange = false; // Has now been handled
					OnChange = true;
					GridEvent.Col = I;
					GridEvent.Row = J;
				}
			}
		}
		else {
			Cbox = static_cast<Jbw_ComboBox*>(Element[I]);
			for (int J = 0; J < RowCnt; J++) {
				Cbox[J].CbxEvent(Event);
				if (Cbox[J].OnChange == true) {
					Cbox[J].OnChange = false; // Has now been handled
					OnChange = true;
					GridEvent.Col = I;
					GridEvent.Row = J;
				}
			}
		}
	}
	SliderV->SldrEvent(Event);
	SliderH->SldrEvent(Event);

	/* Ebox and Cbox has done there jobs. For safety remove the references from Ebox and Cbox */
	Ebox = NULL;
	Cbox = NULL;

	return Ev;
}