#include "Jbw_Menu.h"

///////////////////////////////////////////////////////////////////////////////////////////
//                       CLASS Jbw_Menu
///////////////////////////////////////////////////////////////////////////////////////////
/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR: Jbw_Menu
------------------------------------------------------------------------------------------*/
Jbw_Menu::Jbw_Menu(Jbw_Handles* handles)
{
	Jhandle = handles;
	// Create Frame at the top of the screen
	Obj.x = 0;
	Obj.y = 0; // Hide Top line of Frame
	Obj.h = 18;
	Obj.w = Jhandle->GuiArea.w;
	LineColor = J_WHITE;
	FillColor = J_WHITE;
	Fill = true;
	CreateFrame(); // Create the frame points from above info
	Jbw_TextBox Events;
}

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR: Jbw_Menu
------------------------------------------------------------------------------------------*/
Jbw_Menu::Jbw_Menu(Jbw_Handles* h, std::string SubbtnMenuName, const SDL_Rect* ParentObj)
{
	Jhandle = h;
	Obj = *ParentObj;

//	btnMenuName = new Jbw_Button(Jhandle, Obj.x, Obj.y, Obj.w, Obj.h, SubbtnMenuName, 12);
	btnMenuName = new Jbw_Button[1]; // Must do it this way because in Item Add I have to do a delete[]
	btnMenuName->InitBtn(Jhandle, Obj.x, Obj.y, Obj.w, Obj.h, SubbtnMenuName, 12);
	btnMenuName->BtnColor = J_WHITE;
	btnMenuName->BtnBorderColor = J_WHITE;
	btnMenuName->HoverBorderColor = J_C_Frame;
	btnMenuName->HoverColor = J_C_LGrey;
	btnMenuName->CreateButton();
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR: ~Jbw_Menu
------------------------------------------------------------------------------------------*/
Jbw_Menu::~Jbw_Menu()
{

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MenuAdd Overload 1: Adding a Top Menu
------------------------------------------------------------------------------------------*/
void Jbw_Menu::MenuAdd(std::string NewTopMenu, int w)
{
//	Jbw_lbxMenuName* TmpMenu = new Jbw_lbxMenuName[MnuCnt + 1];

	Jbw_Menu* Cur = this; // create a Current pointer 

	// Move Cur pointer to the end of the linked list
	while (Cur->Next != NULL) {
		Cur = Cur->Next; // Move to End of Linked List
	}

	// Create a new Sub Menu at the end of the link List

	SDL_Rect NewObj = { TotalWidth, 0, w, 18 };
	Cur->Next = new Jbw_Menu(Jhandle, NewTopMenu, &NewObj); // New Menu
	Cur->Next->Prev = Cur; // New Menu's Prev pointer must point to Cur.
	Cur->Next->Parent = this;
	Cur->Next->MnuCnt++;
	TotalWidth += w;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MenuAdd Overload 2: Adding a Sub Menu
------------------------------------------------------------------------------------------*/
Jbw_Return Jbw_Menu::MenuAdd(std::string ParbtnMenuName, std::string SubbtnMenuName)
{
	Jbw_Return FoundParent;
	FoundParent.ErrMessage.assign("Could not find the specified parent btnMenuName");
	Jbw_Menu* Cur = this; // create a Current pointer 

	// Find parent for the new  Menu (Cur pointer)
	Jbw_Menu* Par = Next; // create a Parent pointer 
	while (Par != NULL) {
		if (Par->btnMenuName->Caption.compare(ParbtnMenuName) == 0) {
			
			// Move Cur pointer to the end of the linked list
			while (Cur->Next != NULL) {
				Cur = Cur->Next; // Move to End of Linked List
			}
			
			// Create a new Sub Menu at the end of the link List
			Cur->Next = new Jbw_Menu(Jhandle, SubbtnMenuName, &Obj); // New Menu
			Cur->Next->Prev = Cur; // New Menu's Prev pointer must point to Cur.
			Cur = Cur->Next;
		
			// Set the new Menu's Parent pointer
			Cur->Parent = Par;
			Cur->MnuCnt = 1; // The first entry is the Menu Name
			Cur->TotH = 18;
			Cur->btnMenuName->Visible = false;

			FoundParent.ReturnType = true;
			FoundParent.ErrMessage.assign("");
			break;
		}
		Par = Par->Next;
	}
	ItemAdd(ParbtnMenuName, SubbtnMenuName);

	return FoundParent;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: ItemAdd Overload 1 Adding an Item to the Menu
------------------------------------------------------------------------------------------*/
void Jbw_Menu::ItemAdd(std::string ParbtnMenuName, std::string MenuItem)
{
	Jbw_Menu* Cur = Next;
	while (Cur != NULL) {
		if (Cur->btnMenuName->Caption.compare(ParbtnMenuName) == 0) { // Found the right Menu
			break;
		}
		Cur = Cur->Next;
	}

	// Create more memory space and copy all existing Items
	Jbw_Button* TmpbtnMenuName = new Jbw_Button[Cur->MnuCnt + 1];
	for (int I = 0; I < Cur->MnuCnt; I++) {
		TmpbtnMenuName[I] = Cur->btnMenuName[I];
	//	delete& Cur->btnMenuName[I];
	}
	delete[] Cur->btnMenuName;
	Cur->btnMenuName = TmpbtnMenuName;

	// Add new Menu item
	Cur->btnMenuName[Cur->MnuCnt].Visible = false;
	Cur->btnMenuName[Cur->MnuCnt++].InitBtn(Jhandle, 2, TotH, 0, 0, MenuItem, 12);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: ItemAdd Overload 2 Adding an Item to the Sub Menu
------------------------------------------------------------------------------------------*/
void Jbw_Menu::ItemAdd(std::string NewText, std::string SubbtnMenuName, std::string MenuItem)
{

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MnuRdr
------------------------------------------------------------------------------------------*/
void Jbw_Menu::MnuRdr()
{
	RdrFrame();

	Jbw_Menu* Cur = Next;
	while (Cur != NULL) {
		if (Cur->Parent->Parent == NULL) { // Found a Top Level Meny Item
			Cur->btnMenuName->CreateButton(); 
			Cur->btnMenuName->RdrBtn();
		}
		Cur = Cur->Next;
	}

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: lbxMenuNameRdr
------------------------------------------------------------------------------------------*/
void Jbw_Menu::lbxMenuNameRdr()
{

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MnuEvent
------------------------------------------------------------------------------------------*/
const Jbw_Menu* Jbw_Menu::MnuEvent(SDL_Event* Event)
{

	Jbw_Menu* Cur = Next;
	while (Cur != NULL) {

		/* Mouse Over event on the buttons must close all other submenus and open the relevant one */
		if (Cur->btnMenuName->BtnEvent(Event) == J_MS_OVER) {
			// Check if it's Top level
			if (Cur->btnMenuName->msOver == true && Cur->ShowSub == false) {
				//  Set all ShowSubs  to false
				Jbw_Menu* SetShowSub = this->Next;
				while (SetShowSub != NULL) {
					if (SetShowSub != Cur) {
					//	h->Debug->NewLine("Jbw_Menu: Destroy SubMenu: ", SetShowSub->btnMenuName->Caption);
						SetShowSub->ShowSub = false;
						SDL_DestroyRenderer(SetShowSub->lstHandles.Rdr);
						SDL_DestroyWindow(SetShowSub->lstHandles.Gui);
					}
					SetShowSub = SetShowSub->Next;
				}

				// Set Current SubMenu ShowSub to true
				Cur->ShowSub = true;
				Jhandle->Debug->NewLine("Jbw_Menu: Set Cur->ShowSub = true");

				// If it's a Top Level menu, Render it's SubMenu
				if (Cur->Parent->Parent == NULL) { 
					CreateTopLbx(Cur);
					Cur->Visible = true;
				}
			}
		}

		/* Mouse Click anywhere else than the Submenu or button (Menu name) must close all Submenu's */
		if (Event->type == SDL_MOUSEBUTTONDOWN){
		//	h->Debug->NewLine("Jbw_Menu: Mouse button down EVENT");
			if (Cur->btnMenuName->msOver == false || (Cur->lbxMenuName != NULL && Cur->lbxMenuName->msOver == false)) {
				if (Cur->ShowSub == true) {
					Cur->ShowSub = false;
					SDL_DestroyRenderer(Cur->lstHandles.Rdr);
					SDL_DestroyWindow(Cur->lstHandles.Gui);
				}
			}
		}

		Cur = Cur->Next;
	}
	return NULL;
}


/*-----------------------------------------------------------------------------------------
	FUNCTION: MnuEvent
------------------------------------------------------------------------------------------*/
void Jbw_Menu::CreateTopLbx(Jbw_Menu* Menu)
{
	Jhandle->Debug->NewLine("CreateTopLbx");
	int TotW = 0;
	int TotH = 0;

	lbxMenuName = new Jbw_ListBox(&Menu->lstHandles, Obj.x, Obj.y + Obj.h, 600, 500, 10); // Details to follow
	SDL_Color MnuColor = J_C_LGrey; // { 250, 250, 255, 255 };
	lbxMenuName->LineColor = MnuColor;
	lbxMenuName->FillColor = MnuColor;
	lbxMenuName->TxtFillColor = MnuColor;
	lbxMenuName->TxtBorderColor = MnuColor;
	lbxMenuName->TxtBoxH = 25; // Nice menu spacing

	for (int I = 1; I < Menu->MnuCnt; I++) { // Ignore the first entry that's its own Name
		lbxMenuName->AddText(Menu->btnMenuName[I].Caption);
		if (lbxMenuName->TxtList[lbxMenuName->Cnt - 1].txtBox.w > TotW) {
			TotW = lbxMenuName->TxtList[lbxMenuName->Cnt - 1].txtBox.w; // To Determine ListBox Width
		}

		TotH += lbxMenuName->TxtList[lbxMenuName->Cnt - 1].Border->Obj.h; // To Determine ListBox Height
	}

	// Get Main window current position
	int GuiX = 0, GuiY = 0;
	SDL_GetWindowPosition(Jhandle->Gui, &GuiX, &GuiY);

	// Create Listbox Window
	SDL_Rect Area;
	Area.x = GuiX + Menu->Obj.x;
	Area.y = GuiY + Menu->Obj.y + Menu->Obj.h - 1;
	Area.w = TotW + 35;
	Area.h = TotH + 20;

	Menu->lstHandles.Gui = SDL_CreateWindow("", Area.x, Area.y, Area.w, Area.h,
		SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS /*|	SDL_WINDOW_ALWAYS_ON_TOP */);

	// Create Listbox Renderer
	Menu->lstHandles.Rdr = SDL_CreateRenderer(Menu->lstHandles.Gui, -1, SDL_RENDERER_ACCELERATED);

	// Draw Window Frame 
	Area.x = 0;
	Area.y = 0;
	SDL_SetRenderDrawColor(Menu->lstHandles.Rdr, J_C_Frame.r, J_C_Frame.g, J_C_Frame.b, J_C_Frame.a);
	SDL_RenderDrawRect(Menu->lstHandles.Rdr, &Area);
	SDL_SetRenderDrawColor(Menu->lstHandles.Rdr, MnuColor.r, MnuColor.g, MnuColor.b, MnuColor.a);
	
	// Fill Window Background
	Area.x++;
	Area.y++;
	Area.w -= 2;
	Area.h -= 2;
	SDL_RenderFillRect(Menu->lstHandles.Rdr, &Area);

	// Render List box
	lbxMenuName->Jhandle = &Menu->lstHandles;
	lbxMenuName->CreateFrame();
	lbxMenuName->ResizeListBox(15, 5, Area.w - 16, Area.h - 6);
	lbxMenuName->RdrLbx();
}











