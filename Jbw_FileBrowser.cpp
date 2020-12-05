#include "Jbw_FileBrowser.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR: Jbw_FileBrowser
------------------------------------------------------------------------------------------*/
Jbw_FileBrowser::Jbw_FileBrowser(Jbw_Handles* handles)
{
	Jhandle = new Jbw_Handles;

	Font = TTF_OpenFont("fonts\\arial.ttf", 12);
	TTF_SetFontHinting(Font, TTF_HINTING_LIGHT); 

	// Create User Window
	Jhandle->Gui = SDL_CreateWindow("Browser", 100, 100, Window_w, Window_h, SDL_WINDOW_OPENGL
		/*| SDL_WINDOW_BORDERLESS*/);

	// Create renderer for User window
	Jhandle->Rdr = SDL_CreateRenderer(Jhandle->Gui, -1, SDL_RENDERER_ACCELERATED);

	// Create Border
	BrowserFrame = new Jbw_Frame(Jhandle, 0, 0, Window_w, Window_h, true);
	BrowserFrame->LineColor = { 180, 180, 180, 255 };
	BrowserFrame->FillColor = J_C_Window;
	BrowserFrame->CreateFrame();

	Header = new Jbw_EditBox(Jhandle, 0, 0, Window_w, 25);
	Header->Tbx->Text.assign("Directory & File Browser");
	Header->Tbx->Border->LineColor = J_C_Frame;
	Header->Tbx->Border->FillColor = J_C_Header;
	Header->Tbx->TxtSize = 13;
	Header->Tbx->Align = J_CENTRE;
	
	lbxDir = new Jbw_ListBox(Jhandle, 10, 35, (Window_w - 20)/3, Window_h - 75, 10);
	lbxFiles = new Jbw_ListBox(Jhandle, 10 + (Window_w - 20) / 3, 35, 2*(Window_w - 20)/3, Window_h - 75, 10);

	// Create Buttons
	int Btn_w = 50, Btn_h = 22, BtnSpace = 10, txt_w = 70;

	btnSelect = new Jbw_Button(Jhandle, Window_w - 2*Btn_w - 2*BtnSpace, Window_h - BtnSpace - Btn_h, Btn_w, Btn_h, "Select", 12);
	btnCancel = new Jbw_Button(Jhandle, Window_w - Btn_w - BtnSpace, Window_h - BtnSpace - Btn_h, Btn_w, Btn_h, "Cancel", 12);

	txtFileName = new Jbw_Text(Jhandle, "FileName:", 10, Window_h - 10 - 15);
	edFileName = new Jbw_EditBox(Jhandle, txt_w, Window_h - 10 - 15, Window_w - 2 * Btn_w - 3 * BtnSpace - txt_w, 16);


//	Main(); // Start the Browesr
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_FileBrowser::~Jbw_FileBrowser(void)
{
	CloseBrowser();
}
/*-----------------------------------------------------------------------------------------
	FUNCTION: Free
------------------------------------------------------------------------------------------*/
void Jbw_FileBrowser::CloseBrowser(void)
{
	if (btnSelect != NULL) {
		delete btnSelect;
		btnSelect = NULL;
	}

	if (btnCancel != NULL) {
		delete btnCancel;
		btnCancel = NULL;
	}

	if (Header != NULL) {
		delete Header;
		Header = NULL;
	}

	if (Jhandle != NULL) {
		SDL_DestroyWindow(Jhandle->Gui);
		Jhandle->Gui = NULL;

		SDL_DestroyRenderer(Jhandle->Rdr);
		Jhandle->Rdr = NULL;

		SDL_DestroyTexture(txtImage);
		txtImage = NULL;

		TTF_CloseFont(Font);
		Font = NULL;

		Jhandle = NULL;
	}
}



/*-----------------------------------------------------------------------------------------
	FUNCTION: UpDir
------------------------------------------------------------------------------------------*/
void Jbw_FileBrowser::UpDir(void)
{

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: SelDir
------------------------------------------------------------------------------------------*/
void Jbw_FileBrowser::SelDir(void)
{

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: GetDir
------------------------------------------------------------------------------------------*/
std::string Jbw_FileBrowser::GetDir(void)
{
	J_Type Answer = J_NULL;
	RenderBrowser();

	// Get initial directory
	std::filesystem::path TmpDir = std::filesystem::current_path();
	CurDir = TmpDir.u8string();

	lbxDir->AddText(CurDir);
	lbxDir->RdrLbx();
	std::string Tmp = CurDir;

	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::filesystem::space_info VolInf;
	for (int I = 0; I < 26; I++) {
		std::string Volume = alphabet.substr(I, 1);
		Volume.append(":\\");
		try {
			VolInf = std::filesystem::space(Volume);
			lbxDir->AddText(Volume);
		}
		catch (...) {}
	}
	lbxDir->RdrLbx();

	lbxFiles->AddText(".. Back");
	for (auto& p : std::filesystem::directory_iterator(Tmp)) {

		Tmp = p.path().u8string();
		if (p.is_directory()) {
			std::string TmpDir = "[ ";
			TmpDir.append(Tmp.substr(CurDir.length() + 1));
			TmpDir.append("\\ ]");
			lbxFiles->AddText(TmpDir);
		}
		else {
			lbxFiles->AddText(Tmp.substr(CurDir.length() + 1));
		}
	}
	lbxFiles->RdrLbx();

	while (SDL_WaitEvent(&Jhandle->Event) != 0) {

		// Check When Buttons are Clicked
		if (btnSelect->BtnEvent(&Jhandle->Event) == J_MS_LCLICK) {
			CurDir.append("\\");
			return CurDir.append(edFileName->Tbx->Text);
		}
		if (btnCancel != NULL) {
			if (btnCancel->BtnEvent(&Jhandle->Event) == J_MS_LCLICK) {
				CloseBrowser(); // Close the Browser and clean up 
				return "";
			}
		}
		try {
			lbxDir->LbxEvent(&Jhandle->Event);
			if (lbxDir->LbxEvent(&Jhandle->Event) == J_MS_LCLICK) {
				lbxDir_Click(&Jhandle->Event);
			}
			if (lbxFiles->LbxEvent(&Jhandle->Event) == J_MS_LCLICK) {
				lbxFiles_Click(&Jhandle->Event);
			}
			edFileName->EbxEvent(&Jhandle->Event);
		}
		catch (...) 
		{
		}
	}
	return "";
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: lbxFiles_Click
------------------------------------------------------------------------------------------*/
void Jbw_FileBrowser::lbxFiles_Click(SDL_Event* Event)
{
	std::string Tmp;
	// Test for Directory

	if (lbxFiles->TxtList[lbxFiles->Index].Text.compare(".. Back") == 0) {
		CurDir = CurDir.substr(0, CurDir.find_last_of("\\") + 1);

		// Clear the File listbox
		lbxFiles->Clear();
		if (CurDir.length() > 3) { // Add ".. Back" to Listbox as long as you're not in the root yet
			lbxFiles->AddText(".. Back");
		}
		// Iterate through all the files in the directory, populating the listbox
		for (auto& p : std::filesystem::directory_iterator(CurDir)) {
			Tmp = p.path().u8string();
			if (p.is_directory()) {
				std::string TmpDir = "[ "; //Add brackets when it is a directory
				TmpDir.append(Tmp.substr(CurDir.length()));
				TmpDir.append("\\ ]");
				lbxFiles->AddText(TmpDir);
			}
			else {
				lbxFiles->AddText(Tmp.substr(CurDir.length())); // Add just the file name if it's a file
			}
		}
		lbxFiles->RdrLbx();
		CurDir = CurDir.substr(0, CurDir.length() - 1); // Get rid of the last "/" before running the next search
	}
	else if (lbxFiles->TxtList[lbxFiles->Index].Text.compare(0, 2, "[ ") == 0) { // This is a Directory
		CurDir.append("\\");
		CurDir.append(lbxFiles->TxtList[lbxFiles->Index].Text.substr(2, lbxFiles->TxtList[lbxFiles->Index].Text.length() - 4));

		// Clear the File listbox
		lbxFiles->Clear();
		if (CurDir.length() > 3) { // Add ".. Back" to Listbox as long as you're not in the root yet
			lbxFiles->AddText(".. Back");
		}
		for (auto& p : std::filesystem::directory_iterator(CurDir)) {
			Tmp = p.path().u8string();
			if (p.is_directory()) {
				std::string TmpDir = "[ ";
				TmpDir.append(Tmp.substr(CurDir.length()));
				TmpDir.append("\\ ]");
				lbxFiles->AddText(TmpDir);
			}
			else {
				lbxFiles->AddText(Tmp.substr(CurDir.length()));
			}
		}
		lbxFiles->RdrLbx();
		CurDir = CurDir.substr(0, CurDir.length() - 1); // Get rid of the last "/" before running the next search
	}
	else {
		edFileName->Assign(lbxFiles->TxtList[lbxFiles->Index].Text);
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: lbxDir_Click
------------------------------------------------------------------------------------------*/
void Jbw_FileBrowser::lbxDir_Click(SDL_Event* Event)
{
	std::string Tmp;
	lbxFiles->Clear();
	CurDir.assign(lbxDir->TxtList[lbxDir->Index].Text);

	for (auto& p : std::filesystem::directory_iterator(CurDir)) {
		Tmp = p.path().u8string();
		if (p.is_directory()) {
			std::string TmpDir = "[ ";
			TmpDir.append(Tmp.substr(CurDir.length()));
			TmpDir.append("\\ ]");
			lbxFiles->AddText(TmpDir);
		}
		else {
			lbxFiles->AddText(Tmp.substr(CurDir.length()));
		}
	}
		lbxFiles->RdrLbx();
		CurDir.assign(CurDir.substr(0, CurDir.length()-1));
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RenderBrowser
------------------------------------------------------------------------------------------*/
void Jbw_FileBrowser::RenderBrowser(void) {

	SDL_SetRenderDrawColor(Jhandle->Rdr, 230, 230, 230, 255);
	SDL_RenderClear(Jhandle->Rdr);

	// Render Frame
	BrowserFrame->RdrFrame();

	// Render Header
	Header->Tbx->CreateTexture();
	Header->RdrEbx();

	// Render List boxes
	lbxDir->RdrLbx();
	lbxFiles->RdrLbx();

	txtFileName->RdrTxt();
	edFileName->RdrEbx();

	// Render Buttons
	btnSelect->RdrBtn();
	btnCancel->RdrBtn();
}