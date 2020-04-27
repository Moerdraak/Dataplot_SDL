#include "Jbw_FrameWork.h"

/*------------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_FrameWork::Jbw_FrameWork(void)
{
	// Initialise all the Framework Base pointers.
	TxtPtr = new Jbw_Text; 
	EbxPtr = new Jbw_EditBox;
	LbxPtr = new Jbw_ListBox;
	CbxPtr = new Jbw_ComboBox;
	GrdPtr = new Jbw_Grid;
}

/*------------------------------------------------------------------------------------------
	FUNCTION: Create
				The MAIN CREATE function used by the Coder.
------------------------------------------------------------------------------------------*/
bool Jbw_FrameWork::Create(SDL_Renderer* Rdr, int ObjType, std::string Tag, int Xpos, int Ypos,
	int WidthOrColCnt, int HeightOrRowCnt, int FontSize, std::string Caption)
{
	J_Properties Prop;
	Prop.Rdr = Rdr;
	Prop.x = Xpos;
	Prop.y = Ypos;
	Prop.w = WidthOrColCnt;			// For most Objects
	Prop.h = HeightOrRowCnt;		// For most Objects
	Prop.ColCnt = WidthOrColCnt;	// For Grid Object
	Prop.RowCnt = HeightOrRowCnt;	// For Grid Object
	Prop.Fsize = FontSize;
	Prop.Caption = Caption;
	Prop.Tag = Tag;

	bool Flag = false;
	switch (ObjType) {
	case J_TXT:
		Flag = CreateTxt(&Prop);
		break;
	case J_EBX:
		Flag = CreateEbx(&Prop);
		break;
	case J_LBX:

		break;
	case J_CBX:

		break;
	case J_GRD:
		Flag = CreateGrd(&Prop);
		break;
	default:
		return false;
	}

	return true;
}

/*------------------------------------------------------------------------------------------
	FUNCTION: CreateTxt
------------------------------------------------------------------------------------------*/
bool Jbw_FrameWork::CreateTxt(J_Properties* Prop)
{
	// Check for duplicates
	for (int I = 0; I < TxtCnt; I++) {

		if (isTag(J_TXT, I, Prop->Tag)) {
			return false;
		}
	}

	// Create pointer with more memory
	Jbw_Text* NewPtr = new Jbw_Text[TxtCnt + 1]; 
	   
	for (int I = 0; I < TxtCnt; I++) {
		NewPtr[I] = TxtPtr[I]; // Copy all current TxtPtrs		
	}

	NewPtr[TxtCnt].Id = TxtCnt;
	NewPtr[TxtCnt].Tag.assign(Prop->Tag);
	NewPtr[TxtCnt].InitTxt(Prop->Rdr, Prop->Caption, Prop->x + 1, Prop->y + 1, Prop->Fsize);
	
	if (TxtCnt > 0) {
		delete[] TxtPtr;
	}
	TxtPtr = NewPtr;
	TxtCnt++;

	return true;
}

/*------------------------------------------------------------------------------------------
	FUNCTION: CreateEbx
------------------------------------------------------------------------------------------*/
bool Jbw_FrameWork::CreateEbx(J_Properties* Prop)
{
	// Check for duplicates
	for (int I = 0; I < EbxCnt; I++) {

		if (isTag(J_EBX, I, Prop->Tag)) {
			return false;
		}
	}

	// Create pointer with more memory
	Jbw_EditBox* NewPtr = new Jbw_EditBox[EbxCnt + 1];

	for (int I = 0; I < EbxCnt; I++) {
		NewPtr[I] = EbxPtr[I]; // Copy all current TxtPtrs		
	}
	//	Child->InitEditBox(Rdr, x, y, w, h, Fsize);
	NewPtr[EbxCnt].Id = EbxCnt;
	NewPtr[EbxCnt].Tag.assign(Prop->Tag);
	NewPtr[EbxCnt].InitEbx(Prop->Rdr, Prop->x, Prop->y, Prop->w, Prop->h, Prop->Fsize);
	if (EbxCnt > 0) {
		delete[] EbxPtr;
	}
	EbxPtr = NewPtr;
	EbxCnt++;

	return true;
}

/*------------------------------------------------------------------------------------------
	FUNCTION: CreateLbx
------------------------------------------------------------------------------------------*/
bool Jbw_FrameWork::CreateLbx(J_Properties* Prop)
{
	// Check for duplicates
	for (int I = 0; I < EbxCnt; I++) {

		if (isTag(J_EBX, I, Prop->Tag)) {
			return false;
		}
	}

	// Create pointer with more memory
	Jbw_ListBox* NewPtr = new Jbw_ListBox[EbxCnt + 1];

	for (int I = 0; I < EbxCnt; I++) {
		NewPtr[I] = LbxPtr[I]; // Copy all current TxtPtrs		
	}
	//	Child->InitEditBox(Rdr, x, y, w, h, Fsize);
	NewPtr[EbxCnt].Id = EbxCnt;
	NewPtr[EbxCnt].Tag.assign(Prop->Tag);
//	NewPtr[EbxCnt].InitLbx(Prop->Rdr, Prop->x, Prop->y, Prop->w, Prop->h, Prop->Fsize);
	if (EbxCnt > 0) {
		delete[] LbxPtr;
	}
	LbxPtr = NewPtr;
	EbxCnt++;

	return true;
}
/*------------------------------------------------------------------------------------------
	FUNCTION: CreateCbx
------------------------------------------------------------------------------------------*/
bool Jbw_FrameWork::CreateCbx(J_Properties * Prop)
{
		// Check for duplicates
		for (int I = 0; I < CbxCnt; I++) {

			if (isTag(J_CBX, I, Prop->Tag)) {
				return false;
			}
		}

		// Create pointer with more memory
		Jbw_ComboBox* NewPtr = new Jbw_ComboBox[EbxCnt + 1];

		for (int I = 0; I < CbxCnt; I++) {
			NewPtr[I] = CbxPtr[I]; // Copy all current TxtPtrs		
		}
		//	Child->InitEditBox(Rdr, x, y, w, h, Fsize);
		NewPtr[CbxCnt].Id = CbxCnt;
		NewPtr[CbxCnt].Tag.assign(Prop->Tag);
//		NewPtr[CbxCnt].InitCbx(Prop->Rdr, Prop->x, Prop->y, Prop->w, Prop->h, Prop->Fsize);
		if (CbxCnt > 0) {
			delete[] CbxPtr;
		}
		CbxPtr = NewPtr;
		CbxCnt++;

		return true;
}

/*------------------------------------------------------------------------------------------
FUNCTION: CreateGrd
------------------------------------------------------------------------------------------*/
bool Jbw_FrameWork::CreateGrd(J_Properties* Prop)
{
	// Check for duplicates
	for (int I = 0; I < GrdCnt; I++) {

		if (isTag(J_GRD, I, Prop->Tag)) {
			return false;
		}
	}

	// Create pointer with more memory
	Jbw_Grid* NewPtr = new Jbw_Grid[GrdCnt + 1];

	for (int I = 0; I < GrdCnt; I++) {
		NewPtr[I] = GrdPtr[I]; // Copy all current TxtPtrs		
	}
	//	Child->InitEditBox(Rdr, x, y, w, h, Fsize);
	NewPtr[GrdCnt].Id = GrdCnt;
	NewPtr[GrdCnt].Tag.assign(Prop->Tag);
	NewPtr[GrdCnt].InitGrd(Prop->Rdr, Prop->Tag, Prop->x, Prop->y, Prop->ColCnt, Prop->RowCnt);
	
	if (GrdCnt > 0) {
		delete[] GrdPtr;
	}
	GrdPtr = NewPtr;
	GrdCnt++;

	return true;
}

/*------------------------------------------------------------------------------------------
FUNCTION: Add
------------------------------------------------------------------------------------------*/
void Add(std::string Obj, int RowCol, int Number = 1, std::string ColName = "")
{

}

/*------------------------------------------------------------------------------------------
FUNCTION: Free all Instances
------------------------------------------------------------------------------------------*/
void Jbw_FrameWork::Free(void)
{
	delete[] TxtPtr;
	delete[] EbxPtr;
	delete[] LbxPtr;
	delete[] CbxPtr;
	delete[] GrdPtr;
}

/*------------------------------------------------------------------------------------------
FUNCTION: Free Instance by Instance Name
------------------------------------------------------------------------------------------*/
template<class TmplObj>
TmplObj Jbw_FrameWork::FreeSub(TmplObj Obj, TmplObj TmpObj, short int *Size, std::string Tag)
{
	bool Flag = false;

	short int Len = *Size; // Because Size is going to change
	for (int I = 0; I < Len; I++) {
		if (Flag == false) {
			if (Obj[I]->Tag.compare(Tag) == 0) {
				Flag = true;
				*Size = *Size-1; // Don't do *Size--
				delete Obj[I]; // Delete this specific memory block

				if (I < Len - 1) {  // If it is the last one there's nothing to move
					TmpObj[I] = Obj[I + 1]; // Copy the next position from Ptr to Tmp
					TmpObj[I]->Id--; // Decrement Id as well
				}
			}
			else {
				if (I < Len - 1) {  // If it is the last one there's no memory available in Tmp
					TmpObj[I] = Obj[I]; // And clearly the Instance was not found
				}					 // So the call to Free() was wrong
			}
		}
		else {
			if (I < Len - 1) {  // If it is the last one there's nothing to move
				TmpObj[I] = Obj[I + 1]; // Copy the next position from Ptr to Tmp
				TmpObj[I]->Id--; // Decrement Id as well
			}
		}
	}
	
	if (Flag == true) {
		delete Obj; // Delete old Memory
		return TmpObj;  // Set Ptr to new Memory
	}
	else {
		delete TmpObj;
		return NULL;
	}
}

/*------------------------------------------------------------------------------------------
FUNCTION: Get()  (Overload 1)
	Get Property by Instance Name
	Return: Int
------------------------------------------------------------------------------------------*/
int Jbw_FrameWork::Get(std::string Obj, int Property) 
{

	// Test if it is an Edit Box parameter
	for (int I = 0; I < EbxCnt; I++) {
		if (isTag(J_EBX, I, Obj)) {

		}
	}
	return NULL;
}

/*------------------------------------------------------------------------------------------
FUNCTION: Set()   
	Set String Property, Reference object by Name
------------------------------------------------------------------------------------------*/
bool Jbw_FrameWork::Set(std::string Obj, std::string  Prop1, const char* Val1,
	std::string  Prop2, const char* Val2, std::string  Prop3,
	const char* Val3, std::string  Prop4, const char* Val4,
	std::string  Prop5, const char* Val5) 
{
	bool Flag = false;

	// Place all Properties and Values in a matrix for easy for loop referencing. 
	std::string StrPtr[5];
	const char* ValPtr[5];
	StrPtr[0] = Prop1; ValPtr[0] = Val1;
	StrPtr[1] = Prop2; ValPtr[1] = Val2;
	StrPtr[2] = Prop3; ValPtr[2] = Val3;
	StrPtr[3] = Prop4; ValPtr[3] = Val4;
	StrPtr[4] = Prop5; ValPtr[4] = Val5;

	for (int I = 0; I < J_LEN; I++) {
		for (int J = 0; J < TxtCnt; J++) {
			if (isTag(J_TXT, J, Obj)) {
				Flag = TxtPtr[J].SetTxt(StrPtr, *ValPtr);
				break;
			}
		}
		for (int J = 0; J < EbxCnt; J++) {
			if (isTag(J_EBX ,J, Obj)) {
				Flag = EbxPtr[J].SetEbx(StrPtr, *ValPtr);
				break;
			}
			if (Flag == true) {
				break;
			}
		}
		if (Flag == true) {
			break;
		}
	}
	return Flag;
}

/*------------------------------------------------------------------------------------------
FUNCTION: GrdSet
------------------------------------------------------------------------------------------*/
bool Jbw_FrameWork::GrdSet(std::string Obj, int Row, int Col,
	std::string Prop1, const char* Val1, std::string  Prop2, const char* Val2, 
	std::string  Prop3, const char* Val3, std::string  Prop4, const char* Val4,
	std::string  Prop5, const char* Val5) 
{
	// Place all Properties and Values in a matrix for easy for loop referencing. 
	std::string* StrPtr[5];
	const char* ValPtr[5];
	StrPtr[0] = &Prop1; ValPtr[0] = Val1;
	StrPtr[1] = &Prop2; ValPtr[1] = Val2;
	StrPtr[2] = &Prop3; ValPtr[2] = Val3;
	StrPtr[3] = &Prop4; ValPtr[3] = Val4;
	StrPtr[4] = &Prop5; ValPtr[4] = Val5;

	Jbw_Grid *PtrG = NULL;
	for (int I = 0; I < GrdCnt; I++) {
		if (isTag(J_GRD, I, Obj)) {
			PtrG = &GrdPtr[I];// Just tp keep the nesting down
		}
	}

	for (int P = 0; P < 5; P++) {
		if (StrPtr[P]->compare("HdrName") == 0) {
			for (int I = 0; I < PtrG->Cols; I++) {
				if (I == Col) {
					PtrG->Element[0][I].Text.assign(ValPtr[P]);
				}
			}
		}
		if (StrPtr[P]->compare("ColWidth") == 0) {
				PtrG->SetColWidth(Col, (int)strtod(ValPtr[P], NULL));
		}
		if (StrPtr[P]->compare("RowHeightAll") == 0) {
			PtrG->SetRowHeight(-1, (int)strtod(ValPtr[P], NULL));
		}
		if (StrPtr[P]->compare("RowHeight") == 0) {
			PtrG->SetRowHeight(Col, (int)strtod(ValPtr[P], NULL));
		}
		if (StrPtr[P]->compare("TxtSize") == 0) {
			PtrG->TxtSize(Col, Row, (int)strtod(ValPtr[P], NULL));
		}
		if (StrPtr[P]->compare("RowTxtSize") == 0) {
			PtrG->RowTxtSize(Col, (int)strtod(ValPtr[P], NULL));
		}
	}
	return true;
}

/*------------------------------------------------------------------------------------------
FUNCTION: GrdAdd
------------------------------------------------------------------------------------------*/
bool Jbw_FrameWork::GrdAdd(std::string Obj, int RowCol, int Number,
	std::string ColName, int Objtype)
{

	return true;
}

