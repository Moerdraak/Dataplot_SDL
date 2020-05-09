#include "Jbw_FrameWork.h"

/*------------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_FrameWork::Jbw_FrameWork(void)
{
	//Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	//Set texture filtering to linear
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); // https://wiki.libsdl.org/CategoryHints#Hints

	// Initialize TrueType Fonts
	TTF_Init();

	// Initialise all the ObjWork Base pointers.
	TxtPtr = new Jbw_Text; 
	EbxPtr = new Jbw_EditBox;
	LbxPtr = new Jbw_ListBox;
	CbxPtr = new Jbw_ComboBox;
	GrdPtr = new Jbw_Grid;
}

/*------------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_FrameWork::~Jbw_FrameWork()
{
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	delete[] TxtPtr;
	delete[] EbxPtr;
	delete[] LbxPtr;
	delete[] CbxPtr;
	delete[] GrdPtr;
}

/*------------------------------------------------------------------------------------------
	FUNCTION: Create
				The MAIN CREATE function used by the Coder.
------------------------------------------------------------------------------------------*/
bool Jbw_FrameWork::Create(Jbw_Handles* handles, int ObjType, std::string Tag, int Xpos, int Ypos,
	int WidthOrNumCol, int HeightOrNumRow, int FontSize, std::string Caption)
{
	bool Flag = true;
	J_Properties Prop;
	Prop.handles = *handles;
	Prop.x = Xpos;
	Prop.y = Ypos;
	Prop.w = WidthOrNumCol;			// For most Objects
	Prop.h = HeightOrNumRow;		// For most Objects
	Prop.NumCol = WidthOrNumCol;	// For Grid Object
	Prop.NumRow = HeightOrNumRow;	// For Grid Object
	Prop.Fsize = FontSize;
	Prop.Caption.assign(Caption);
	Prop.Tag.assign(Tag);

	switch (ObjType) {
	case J_TXT:
		Flag = CreateTxt(&Prop);
		break;
	case J_EBX:
		Flag = CreateEbx(&Prop);
		break;
	case J_LBX:
		Flag = CreateLbx(&Prop);
		break;
	case J_CBX:
		Flag = CreateCbx(&Prop);
		break;
	case J_BTN:
		Flag = CreateBtn(&Prop);
		break;
	case J_GRD:
		Flag = CreateGrd(&Prop);
		break;
	default:
		Flag = false;
	}

	return Flag;
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
								// DANGER DANGER If you delete txtImage like you should with Destructor
								// This does not copy well - Write a copy constructor to ensure new 
								// Memory space is created for stuff inside TxtPtr 
								// THIS WILL become important when I start fixing all my memory leaks.
	}

	Prop->Id = TxtCnt;
	NewPtr[TxtCnt].InitTxt(Prop);
	
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

	Prop->Id = EbxCnt;
	NewPtr[EbxCnt].InitEbx(Prop);
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
	for (int I = 0; I < LbxCnt; I++) {
		if (isTag(J_LBX, I, Prop->Tag)) {
			return false;
		}
	}

	// Create pointer with more memory
	Jbw_ListBox* NewPtr = new Jbw_ListBox[LbxCnt + 1];

	for (int I = 0; I < LbxCnt; I++) {
		NewPtr[I] = LbxPtr[I]; // Copy all current TxtPtrs		
	}

	Prop->Id = LbxCnt;
	NewPtr[LbxCnt].InitLbx(Prop);
	if (LbxCnt > 0) {
		delete[] LbxPtr;
	}
	LbxPtr = NewPtr;
	LbxCnt++;

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
		//	Child->InitEditBox(Jrdr, x, y, w, h, Fsize);
		Prop->Id = CbxCnt;
		NewPtr[CbxCnt].InitCbx(Prop);
		if (CbxCnt > 0) {
			delete[] CbxPtr;
		}
		CbxPtr = NewPtr;
		CbxCnt++;

		return true;
}

/*------------------------------------------------------------------------------------------
	FUNCTION: CreateBtn
------------------------------------------------------------------------------------------*/
bool Jbw_FrameWork::CreateBtn(J_Properties* Prop)
{
	// Check for duplicates
	for (int I = 0; I < BtnCnt; I++) {
		if (isTag(J_BTN, I, Prop->Tag)) {
			return false;
		}
	}

	// Create pointer with more memory
	Jbw_Button* NewPtr = new Jbw_Button[BtnCnt + 1];

	for (int I = 0; I < BtnCnt; I++) {
		NewPtr[I] = BtnPtr[I]; // Copy all current BtnPtrs		
	}

	Prop->Id = BtnCnt;
	NewPtr[BtnCnt].InitBtn(Prop);
	if (BtnCnt > 0) {
		delete[] BtnPtr;
	}
	BtnPtr = NewPtr;
	BtnCnt++;

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
	Prop->Id = GrdCnt;
	NewPtr[GrdCnt].InitGrd(Prop);
	
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
std::string Jbw_FrameWork::GetS(Jbw_Handles* h, std::string Obj, std::string Property)
{
	// Test if it is an Edit Box parameter
	for (int I = 0; I < *h->EbxCnt; I++) {
		if (isTag(J_EBX, I, Obj)) {
			return h->EbxPtr[I].EboxGetS(Property);
		}
	}
	return "";
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
			for (int I = 0; I < PtrG->ColCnt; I++) {
				if (I == Col) {
					PtrG->Ebox[0][I].Text.assign(ValPtr[P]);
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


/*------------------------------------------------------------------------------------------
	FUNCTION: isTag
------------------------------------------------------------------------------------------*/
bool Jbw_FrameWork::isTag(int Type, int Id, std::string Tag)
{
	bool Flag = false;

	switch (Type) {
	case J_TXT:
		if (Tag.compare(TxtPtr[Id].Tag) == 0) {
			Flag = true;
		}
		break;
	case J_EBX:
		if (Tag.compare(EbxPtr[Id].Tag) == 0) {
			Flag = true;
		}
		break;
	case J_LBX:
		if (Tag.compare(LbxPtr[Id].Tag) == 0) {
			Flag = true;
		}
		break;
	case J_CBX:
		if (Tag.compare(CbxPtr[Id].Tag) == 0) {
			Flag = true;
		}
		break;
	case J_BTN:
		if (Tag.compare(BtnPtr[Id].Tag) == 0) {
			Flag = true;
		}
		break;
	case J_GRD:
		if (Tag.compare(GrdPtr[Id].Tag) == 0) {
			Flag = true;
		}
		break;
	default:
		return false;
	}
	return Flag;
}

/*------------------------------------------------------------------------------------------
/*                                  List Box STuff                                        */
/*------------------------------------------------------------------------------------------
	FUNCTION: lbxClear
------------------------------------------------------------------------------------------*/
void Jbw_FrameWork::lbxClear(std::string Tag)
{
	for (int I = 0; I < LbxCnt; I++) {
		if (isTag(J_LBX, I, Tag)) {
			LbxPtr[I].Clear();
			LbxPtr[I].RdrLbx(&handles);
		}
	}
}

/*------------------------------------------------------------------------------------------
	FUNCTION: MsgBox
------------------------------------------------------------------------------------------*/
void MsgBox(std::string Title, std::string Msg, J_Type YesNo, int x, int y, int w = 150, int h = 100)
{
	
//	J_Type Answer = MsgBox(Title, Msg, YesNo, x, y, w, h);
}