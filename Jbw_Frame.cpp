#include "Jbw_Frame.h"


/*---------------------------------------------------------------
	FUNCTION: Create  Overload 1 "Edit box" 
---------------------------------------------------------------*/
Jbw_EditBox* Jbw_Frame::Create(SDL_Renderer* Rdr, tE tType, std::string NewName, J_Type EboxType,
	int x, int y, int w, int h)
{
	for (int I = 0; I < Size_E; I++) {
		if (NewName.find(Ebox[I]->Tag) == 0) {
			return NULL;
		}
	}
	Jbw_EditBox* Child = new Jbw_EditBox; // Create Child Instance

	Child->Id = Size_E;
	Child->Tag.assign(NewName);
	if (Size_E == 0) {
		Ebox = new Jbw_EditBox*; // Create first Instance of pointer to "Mammal pointer"
	}
	else {
		Jbw_EditBox** Tmp = new Jbw_EditBox * [Size_E + 1]; // Assign new memmory one bigger than before
		for (int I = 0; I < Size_E; I++) {
			Tmp[I] = Ebox[I];
		}
		delete Ebox;
		Ebox = Tmp;	
	}
	Child->Renderer = Rdr;
	Child->Box.x = x;
	Child->Box.y = y;
	Child->Box.w = w;
	Child->Box.h = h;

	Ebox[Size_E++] = Child;

	// Should not return this pointer gives user power to break things, 
	// But just for S&Gs I'll leave it in
	return Child;
}

/*---------------------------------------------------------------
	FUNCTION: Create Overload 2 "List box" 
---------------------------------------------------------------*/
Jbw_ListBox* Jbw_Frame::Create(SDL_Renderer* Rdr, tL tType, std::string NewName) {

	// Check that it is not a duplicate Name
	for (int I = 0; I < Size_L; I++) {
		if (NewName.find(Lbox[I]->Tag) == 0) {
			return NULL;
		}
	}
	Jbw_ListBox* New = new Jbw_ListBox; // Create Child Instance

	New->Id = Size_L;
	New->Tag.assign(NewName);
	if (Size_L == 0) {
		Lbox = new Jbw_ListBox*; // Create first Instance of pointer to "Mammal pointer"
	}
	else {
		Jbw_ListBox** Tmp = new Jbw_ListBox * [Size_L + 1]; // Assign new memmory one bigger than before
		for (int I = 0; I < Size_L; I++) {
			Tmp[I] = Lbox[I];
		}
		delete Lbox;
		Lbox = Tmp;
	}
	Lbox[Size_L++] = New;
	// Should not return this pointer gives user power to break things, But just for S&Gs I'll leave it in
	return New;
}

/*---------------------------------------------------------------
FUNCTION: Free all Instances
---------------------------------------------------------------*/
Jbw_ComboBox* Jbw_Frame::Create(SDL_Renderer* Rdr, tC tType, std::string NewName) 
{
	// Check that it is not a duplicate Name
	for (int I = 0; I < Size_C; I++) {
		if (NewName.find(Cbox[I]->Tag) == 0) {
			return NULL;
		}
	}
	Jbw_ComboBox* New = new Jbw_ComboBox;

	New->Id = Size_C;
	New->Tag.assign(NewName);
	if (Size_C == 0) {
		Cbox = new Jbw_ComboBox*; // Create first Instance of pointer to "Mammal pointer"
	}
	else {
		Jbw_ComboBox** Tmp = new Jbw_ComboBox * [Size_C + 1]; // Assign new memmory one bigger than before
		for (int I = 0; I < Size_C; I++) {
			Tmp[I] = Cbox[I];
		}
		delete Cbox;
		Cbox = Tmp;
	}
	Cbox[Size_C++] = New;
	return New;
}

/*---------------------------------------------------------------
FUNCTION: Free all Instances
---------------------------------------------------------------*/
void Jbw_Frame::Free(void)
{
	// Free all Edit Box Instances
	for (int I = 0; I < Size_E; I++) { // For Loop to delete all Objects before deleting the Base Object
		delete Ebox[I];
	}
	if (Size_E > 0) { // Just in case user free'd all child Instances already
		delete Ebox;
	}

	// Free all List Box Instances
	for (int I = 0; I < Size_L; I++) { // For Loop to delete all Objects before deleting the Base Object
		delete Lbox[I];
	}
	if (Size_L > 0) { // Just in case user free'd all child Instances already
		delete Lbox;
	}

	// Free all Message Box Instances
	for (int I = 0; I < Size_M; I++) { // For Loop to delete all Objects before deleting the Base Object
		delete Mbox[I];
	}
	if (Size_M > 0) { // Just in case user free'd all child Instances already
		delete Mbox;
	}

	// Free all Combo Box Instances
	for (int I = 0; I < Size_C; I++) { // For Loop to delete all Objects before deleting the Base Object
		delete Cbox[I];
	}
	if (Size_C > 0) { // Just in case user free'd all child Instances already
		delete Cbox;
	}
}

/*---------------------------------------------------------------
FUNCTION: Free Instance by Instance Name
---------------------------------------------------------------*/
template<class TmplObj>
TmplObj Jbw_Frame::FreeSub(TmplObj Obj, TmplObj TmpObj, short int *Size, std::string Tag)
{
	bool Flag = false;

	short int Len = *Size; // Because Size is going to change
	for (int I = 0; I < Len; I++) {
		if (Flag == false) {
			if (Obj[I]->Tag.find(Tag, 0) == 0) {
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

/*---------------------------------------------------------------
FUNCTION: Free Edit box Instance by Name
---------------------------------------------------------------*/
void Jbw_Frame::Free(tE T, std::string Tag) 
{
	bool Flag = false;

	Jbw_EditBox** Tmp = new Jbw_EditBox * [(double)Size_E - 1]; // Assign new memmory one smaller than before
	
	Ebox = FreeSub(Ebox, Tmp, &Size_E, Tag);
	
	if (Size_E == 0) {
		delete Ebox;
	}
}

/*---------------------------------------------------------------
FUNCTION: Free List box Instance by Name
---------------------------------------------------------------*/
void Jbw_Frame::Free(tL T, std::string Tag)
{
	bool Flag = false;

	Jbw_ListBox** Tmp = new Jbw_ListBox * [(double)Size_L - 1]; // Assign new memmory one smaller than before

	Lbox = FreeSub(Lbox, Tmp, &Size_L, Tag);

	if (Size_L == 0) {
		delete Lbox;
	}
}

///*---------------------------------------------------------------
//FUNCTION: Free MESSAGE BOX Instance by Name
//---------------------------------------------------------------*/
//void Jbw_Frame::Free(tL T, std::string Tag)
//{
//	bool Flag = false;
//
//	Jbw_ListBox** Tmp = new Jbw_ListBox * [(double)Size_ - 1]; // Assign new memmory one smaller than before
//
//	box = FreeSub(Lbox, Tmp, &Size_, Tag);
//
//	if (Size_L == 0) {
//		delete box;
//	}
//}

/*---------------------------------------------------------------
FUNCTION: Free COMBO BOX Instance by Name
---------------------------------------------------------------*/
void Jbw_Frame::Free(tC T, std::string Tag)
{
	bool Flag = false;

	Jbw_ComboBox** Tmp = new Jbw_ComboBox * [(double)Size_C - 1]; // Assign new memmory one smaller than before

	Cbox = FreeSub(Cbox, Tmp, &Size_C, Tag);

	if (Size_C == 0) {
		delete Cbox;
	}
}

/*---------------------------------------------------------------
FUNCTION: Free Instance by Id
---------------------------------------------------------------*/
void Jbw_Frame::Free(int ObjId) {
	if (ObjId < Size_E) {
		//	Free(Ptr[ObjId]->Name);
	}
}


/*---------------------------------------------------------------
FUNCTION: Get()  (Overload 1)
	Get Property by Instance Name
	Return: Int
---------------------------------------------------------------*/
int Jbw_Frame::Get(std::string Obj, int Property) {

	// Test if it is an Edit Box parameter
	for (int I = 0; I < Size_E; I++) {
		if (Ebox[I]->Tag.find(Obj, 0) == 0) {
			if (1) {

			}

		}
	}
	return NULL;
}

/*---------------------------------------------------------------
FUNCTION: Set()   
	Set String Property, Reference object by Name
---------------------------------------------------------------*/
bool Jbw_Frame::Set(std::string Obj, std::string  Prop1, const char* Val1,
	std::string  Prop2, const char* Val2, std::string  Prop3,
	const char* Val3, std::string  Prop4, const char* Val4,
	std::string  Prop5, const char* Val5) {

	// Place all Properties and Values in a matrix for easy for loop referencing. 
	std::string* StrPtr[5];
	const char* ValPtr[5];
	StrPtr[0] = &Prop1; ValPtr[0] = Val1;
	StrPtr[1] = &Prop2; ValPtr[1] = Val2;
	StrPtr[2] = &Prop3; ValPtr[2] = Val3;
	StrPtr[3] = &Prop4; ValPtr[3] = Val4;
	StrPtr[4] = &Prop5; ValPtr[4] = Val5;

	bool Flag = false;

	// Test if it is an Edit Box parameter
	for (int I = 0; I < Size_E; I++) {
		if (Ebox[I]->Tag.find(Obj, 0) == 0) {
			// Feed Edit box Set routine all the values
			for (int J = 0; J < 5; J++) {
				if (Prop1.c_str() != "NULL") {
					Ebox[I]->SetX(*StrPtr[J], ValPtr[J]);
				}
			}
			Ebox[I]->CreateTexture();
		}
	}

	// Test if it is a List Box parameter
	for (int I = 0; I < Size_L; I++) {
		if (Lbox[I]->Tag.find(Obj, 0) == 0) {
			// Feed List box Set routine all the values
			for (int J = 0; J < 5; J++) {
				if (Prop1.c_str() != "NULL") {
	//				Lbox[I]->Set(*StrPtr[J][0], *StrPtr[J][1]);
				}
			}
		}
	}

	// Test if it is a Combo Box parameter
	for (int I = 0; I < Size_C; I++) {
		if (Cbox[I]->Tag.find(Obj, 0) == 0) {
			// Feed Combo box Set routine all the values
			for (int J = 0; J < 5; J++) {
				if (Prop1.c_str() != "NULL") {
		//			Cbox[I]->SetX(*StrPtr[J][0], *StrPtr[J][1]);
				}
			}
		}
	}

	return Flag;
}

