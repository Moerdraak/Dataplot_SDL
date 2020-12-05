#pragma once
#include "Jbw_Base.h"
#include "Jbw_ListBox.h"
#include "JBW_MsgBox.h"
#include <filesystem>
//#include <fileapi.h>

class Jbw_FileBrowser : private Jbw_Base {
private:
	TTF_Font* Font = NULL;
	SDL_Texture* txtImage = NULL;
	Jbw_Frame* BrowserFrame = NULL;
	Jbw_EditBox* Header = NULL;
	Jbw_EditBox* edFileName = NULL;
	Jbw_Text* txtFileName = NULL;
	Jbw_Button* btnSelect = NULL;
	Jbw_Button* btnCancel = NULL;
	SDL_Surface* txtSurf = NULL;
	J_Type BrowserType;

	int Window_w = 1000;
	int Window_h = 600;
	int TxtSize = 10;

public:
	Jbw_Handles* handles;
	Jbw_ListBox* lbxDir;
	Jbw_ListBox* lbxFiles;
	std::string Directory = "";
	std::string File = "";
	std::string CurDir;

	Jbw_FileBrowser(Jbw_Handles* handles);
	~Jbw_FileBrowser(void);
	void CloseBrowser(void);

	void UpDir(void);
	void SelDir(void);

	std::string GetDir(void);

	void lbxDir_Click(SDL_Event* Event);
	void lbxFiles_Click(SDL_Event* Event);

	void RenderBrowser(void);

};