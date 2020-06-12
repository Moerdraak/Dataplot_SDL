#include "Dataplot.h"
#include "Jbw_Text.h" // Temporary here

SDL_Point* TmpPoints;

Uint32 koos(Uint32 interval, void* param) {
	
	Dataplot* Dp = static_cast<Dataplot*>(param);
	Dp->UserRender();
	delete Dp;
	return SDL_AddTimer(5000, &koos, param);
}

void SetColTxtBox(Jbw_TextBox* ColName, SDL_Color Color, SDL_Color TxtColor);

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////                             MAIN                                      ///////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	Dataplot Dp; 
	Jbw_Handles *h = Dp.JbwCreateLayout(); 
	h->Debug = new Jbw_Debug(1300, 50, 500, 900);
	h->Debug->NewLine ("MAIN: Handles created");



	/******************************/
	/*   SDL TIMER STUFFS   */
	//Uint32 delay = (330 / 10) * 10; // To round it down to the nearest 10 ms 
	//SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, &Dp);
	/******************************/

	Dp.cbxFigure->AddRow("Main Sight");
	Dp.cbxFigure->AddRow("Cannon testing");
	Dp.cbxFigure->AddRow("Seeker vibration"); 
	Dp.cbxFigure->AddRow("4. Free Turbine speed");
	Dp.cbxFigure->AddRow("5. Free Turbine speed");
	Dp.cbxFigure->AddRow("6. Free Turbine speed");
	Dp.cbxFigure->AddRow("7. Free Turbine speed");
	Dp.cbxFigure->AddRow("8. Free Turbine speed");
	Dp.cbxFigure->AddRow("9. Free Turbine speed");
	Dp.cbxFigure->AddRow("10. Free Turbine speed");
	Dp.cbxFigure->AddRow("11. Free Turbine speed");
	Dp.cbxFigure->AddRow("12. Free Turbine speed");
	Dp.cbxFigure->AddRow("13. Free Turbine speed");
	Dp.cbxFigure->AddRow("14. Free Turbine speed");
	Dp.cbxFigure->AddRow("15. Free Turbine speed");
	Dp.cbxFigure->AddRow("16. Free Turbine speed");
	Dp.cbxFigure->CbxLbx->TxtList[1].TxtColor = { 180, 0, 0, 255 };



//	SDL_TimerID my_timer_id = SDL_AddTimer(5000, &koos, &Dp);

	Dp.LoadConfigFile("Rooivalk.cfg");
	h->Debug->NewLine("MAIN: Loaded Config, Start UserRender()");
	Dp.UserRender();
	h->Debug->NewLine("MAIN: Done UserRender() ");

	

	Jbw_TextBox White(h, "White", 500, 300, 100, 18, 12); SetColTxtBox(&White, J_WHITE, J_BLACK);
	Jbw_TextBox Black(h, "Black", 500, 320, 100, 18, 12); SetColTxtBox(&Black, J_BLACK, J_WHITE);
	Jbw_TextBox Grey(h, "Grey", 500, 340, 100, 18, 12); SetColTxtBox(&Grey, J_GREY, J_BLACK);
	Jbw_TextBox Silver(h, "Silver", 500, 360, 100, 18, 12); SetColTxtBox(&Silver, J_SILVER, J_WHITE);

	Jbw_TextBox Red(h, "Red", 610, 300, 100, 18, 12); SetColTxtBox(&Red, J_RED, J_BLACK);
	Jbw_TextBox Lime(h, "Lime", 610, 320, 100, 18, 12); SetColTxtBox(&Lime, J_LIME, J_BLACK);
	Jbw_TextBox Blue(h, "Blue", 610, 340, 100, 18, 12); SetColTxtBox(&Blue, J_BLUE, J_WHITE);

	Jbw_TextBox Cyan(h, "Cyan", 720, 300, 100, 18, 12); SetColTxtBox(&Cyan, J_CYAN, J_BLACK);
	Jbw_TextBox Magenta(h, "Magenta", 720, 320, 100, 18, 12); SetColTxtBox(&Magenta, J_MAGENTA, J_BLACK);
	Jbw_TextBox Yellow(h, "Yellow", 720, 340, 100, 18, 12); SetColTxtBox(&Yellow, J_YELLOW, J_BLACK);

	Jbw_TextBox Maroon(h, "Maroon", 830, 300, 100, 18, 12); SetColTxtBox(&Maroon, J_MAROON, J_WHITE);
	Jbw_TextBox Green(h, "Green", 830, 320, 100, 18, 12); SetColTxtBox(&Green, J_GREEN, J_BLACK);
	Jbw_TextBox Navy(h, "Navy", 830, 340, 100, 18, 12); SetColTxtBox(&Navy, J_NAVY, J_WHITE);

	Jbw_TextBox Teal(h, "Teal", 940, 300, 100, 18, 12); SetColTxtBox(&Teal, J_TEAL, J_BLACK);
	Jbw_TextBox Olive(h, "Olive", 940, 320, 100, 18, 12); SetColTxtBox(&Olive, J_OLIVE, J_BLACK);
	Jbw_TextBox Purple(h, "Purple", 940, 340, 100, 18, 12); SetColTxtBox(&Purple, J_PURPLE, J_WHITE);

	SDL_RenderPresent(h->Rdr);

	/*   BEGIN Twak    */
	Dp.edDataSet->Tbx->Text.assign("Rooivalk Rocket Flight test at OTB (2019-02-03)");
	Dp.edDataSet->Tbx->CreateTexture();
	Dp.edDataSet->RdrEbx();
	/*   END Twak  */

	h->Debug->NewLine("MAIN: Start TheLoop()");
	Dp.TheLoop();

	return 0;
}

////////////                         END MAIN                                      ///////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

/*-----------------------------------------------------------------------------------------
	TEMP TWAK
------------------------------------------------------------------------------------------*/
void SetColTxtBox(Jbw_TextBox* ColName, SDL_Color Color, SDL_Color TxtColor)
{
	ColName->BackColor(Color); 
	ColName->FrameOn = true; 
	ColName->FillOn = true;
	ColName->Align = J_CENTRE;
	ColName->TxtColor = TxtColor;
	ColName->CreateTexture();
	ColName->RdrTbx();
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Dataplot::~Dataplot() {

	//Destroy Window and Renderer
	SDL_DestroyRenderer(handles.Rdr);
	SDL_DestroyWindow(handles.Gui);

	handles.Gui = NULL;
	handles.Rdr = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	TTF_Quit();
};

/*------------------------------------------------------------------------------------------
  FUNCTION: JbwCreateLayout:
			First Thing to do, create the GUI and all the objects on the GUI.
			?? Give the important handles back ??
------------------------------------------------------------------------------------------*/
Jbw_Handles* Dataplot::JbwCreateLayout(void)
{
	handles.GuiArea.x = 100; handles.GuiArea.y = 200; 
	handles.GuiArea.w = 1070; handles.GuiArea.h = 600;
	handles.Gui = SDL_CreateWindow("Data Plot", handles.GuiArea.x, handles.GuiArea.y, 
		handles.GuiArea.w, handles.GuiArea.h,
		SDL_WINDOW_OPENGL);
	
	// Create renderer for User window https://wiki.libsdl.org/SDL_CreateRenderer
	handles.Rdr = SDL_CreateRenderer(handles.Gui, -1, SDL_RENDERER_ACCELERATED);

	// Load the logo
	int imgFlags = IMG_INIT_JPG; // Initialize JPG loading
	if ((IMG_Init(imgFlags) & imgFlags)) {
		SDL_Surface* loadedSurface = IMG_Load("Jabberwock.jpg");
		if (!loadedSurface == NULL)
		{
			//Create texture from surface pixels
			Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 255, 255, 255);
			SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);
			LogoImage = SDL_CreateTextureFromSurface(handles.Rdr, loadedSurface);
			SDL_FreeSurface(loadedSurface);
		}
		else {
		//	LbxPtr[0].AddText(SDL_GetError());
		}
	}
	
	IMG_Quit();



	/*  Dataplot Menu  */
	Menu = new Jbw_Menu(&handles);
	Menu->MenuAdd("File", 40);
	Menu->ItemAdd("File", "New Project");
	Menu->ItemAdd("File", "Load Project");
	Menu->ItemAdd("File", "Save Project");
	Menu->ItemAdd("File", "Save Project As");
	Menu->ItemAdd("File", "Save Figure Config");
	Menu->ItemAdd("File", "Load Figure Config");
	Menu->ItemAdd("File", "FileSub", "Something");

	Menu->MenuAdd("Tools", 50);
	Menu->ItemAdd("Tools", "Graph Properties");
	Menu->MenuAdd("Tools", "Convert Old Project Files");
	Menu->MenuAdd("Tools", "Convert Data for Dataplot");
	Menu->ItemAdd("Convert Data for Dataplot", "Pass3200 data");
	Menu->ItemAdd("Convert Data for Dataplot", "CSV data");
	Menu->ItemAdd("Convert Data for Dataplot", "ACRA data");
	Menu->ItemAdd("Convert Data for Dataplot", "Seeker 400 data");

	Menu->MenuAdd("Help", 40);
	Menu->ItemAdd("Help", "Help");
	Menu->ItemAdd("Help", "About");
	
	Menu->MenuAdd("Tools", "Tools Sub 1");
	Menu->MenuAdd("Tools", "Tools Sub 2");

	Menu->MenuAdd("Help", "Help Sub 1");
	Menu->MenuAdd("File", "File Sub 1");
	Menu->MenuAdd("Tools Sub 2", "Tools Sub 2 Sub 1");
	Menu->ItemAdd("Tools Sub 2 Sub 1", "Tools Sub 2 Sub 1 Item 1");
	Menu->ItemAdd("Tools Sub 2", "Tools Sub 2 Item 1");
	Menu->ItemAdd("Tools Sub 2 Sub 1", "Tools Sub 2 Sub 1 Item 2");
	Menu->ItemAdd("Tools", "Tools Item 2 Hoe dan nou");
	/*  DataPlot Heading */
	txtDataPlotName = new Jbw_Text(&handles, "DataPlot", 128, 30, 24);
	txtVersion = new Jbw_Text(&handles, "Version: c1.0", 132, 55, 11);

	/*  Project Detail */
	txtConfig = new Jbw_Text(&handles, "Loaded Config:", 112, 120, 12);
	txtProject = new Jbw_Text(&handles, "Rooivalk", 202, 120, 12);
	txtProject->F_Bold = TTF_STYLE_BOLD;
	txtProject->CreateTexture();

	/*  Bitplot/Wordplot Heading */
	txtBpWp = new Jbw_Text(&handles, "Bit plot", 360, 30, 18);

	/*  Data Directory */
	txtDataDir = new Jbw_Text(&handles, "Data Directory:", 12, 140, 12);
	edDataDir = new Jbw_EditBox(&handles, 12, 155, 328, 18, 11);
	btnDataDir = new Jbw_Button(&handles, 339, 155, 14, 18, ":", 12);

	/*  File ID: */
	txtFileId = new Jbw_Text(&handles, "File ID:", 12, 175, 12);
	edFileId = new Jbw_EditBox(&handles, 12, 190, 40, 18, 11);

	/*  DataSet Description */
	txtDataSet = new Jbw_Text(&handles, "Dataset Description:", 12, 210, 12);
	edDataSet = new Jbw_EditBox(&handles, 12, 225, 300, 18, 11);

	/*  Figure Combobox  */
	txtFigure = new Jbw_Text(&handles, "Select Figure", 12, 340, 12);
	cbxFigure = new Jbw_ComboBox(&handles, 12, 355, 300, 18, 11, false);

	/*   Figure Type Button */
	txtFigBtn = new Jbw_Text(&handles, "Bitplot           Wordplot", 170, 340, 12);

	/*  Title  */
	txtTitle = new Jbw_Text(&handles, "Graph Title", 12, 375, 12);
	edTitle = new Jbw_EditBox(&handles, 12, 390, 300, 18, 11);

	/*  Y Axes label */
	txtYaxLabel = new Jbw_Text(&handles, "Y-Axes Label", 12, 410, 12);
	edYaxLabel = new Jbw_EditBox(&handles, 12, 425, 300, 18, 11);

	/*  X Axes label */
	txtXaxLabel = new Jbw_Text(&handles, "X-Axes Label", 12, 445, 12);
	edXaxLabel = new Jbw_EditBox(&handles, 12, 460, 300, 18, 11);


	/*   Time On/Off Button */
	txtOnOffBtn = new Jbw_Text(&handles, "Time", 260, 445, 12);

	/*   Messages   */
	txtMessages = new Jbw_Text(&handles, "Messages", 12, 480, 12);
	lbxMessage = new Jbw_ListBox(&handles, 12, 495, 1048, 95, 11);
//	lbxMessage = new Jbw_ListBox(&handles, 400, 400, 400, 153, 11);
	btnClear = new Jbw_Button(&handles, 1020, 475, 40, 18, "Clear", 12);

	/* Plot Buttons  */
	btnPlot = new Jbw_Button(&handles, 920, 30, 40, 18, "Plot", 12);
	btnPlotAll = new Jbw_Button(&handles, 970, 30, 90, 18, "Plot All Figures", 12);
	btnUp = new Jbw_Button(&handles, 700, 30, 40, 18, "Up", 12);
	btnDown = new Jbw_Button(&handles, 750, 30, 40, 18, "Down", 12);
	btnAdd = new Jbw_Button(&handles, 800, 30, 60, 18, "Add Bits", 12);

	/*  SETUP GRAPHICS TABLE AREA   */	
	grdFigure = new Jbw_Grid(&handles, 360, 55, 700/* 700 */, 200/* 180 */);
	grdFigure->SetRowHeight(17, -1);
	grdFigure->TxtSize(-1, -1, 15);

	grdFigure->AddCol(&handles, "grdFigure", "Parameter", 180, J_EBX);
	grdFigure->AddCol(&handles, "grdFigure", "Size", 30, J_EBX);
	grdFigure->AddCol(&handles, "grdFigure", "Bit", 55, J_EBX);
	grdFigure->AddCol(&handles, "grdFigure", "Description", 120, J_EBX);
	grdFigure->AddCol(&handles, "grdFigure", "Offset", 40, J_EBX);
	grdFigure->AddCol(&handles, "grdFigure", "Factor", 40, J_EBX);
	
	grdFigure->AddCol(&handles, "grdFigure", "Colour", 70, J_CBX);	
	std::vector<std::string> Colors = { "Black", "Red", "Lime", "Blue", "Magenta", 
		"Cyan", "Yellow", "Maroon", "Green", "Navy", "Teal", "Olive", "Purple", "Grey" };
	grdFigure->AddCbxLbx("Colour", Colors);
		
	grdFigure->AddCol(&handles, "grdFigure", "Symb.", 40, J_CBX);
		std::vector<std::string> Symbols = { "*", "+", "x", "d", "s", "o", "NO" };
		grdFigure->AddCbxLbx("Symb.", Symbols);
	grdFigure->AddCol(&handles, "grdFigure", "Line", 40, J_CBX);
		std::vector<std::string> Lin = { "-", ":", ".", "NO"};
		grdFigure->AddCbxLbx("Line", Lin);
	grdFigure->AddCol(&handles, "grdFigure", "Step", 40, J_CBX);
		std::vector<std::string> Step = { "OFF", "ON" };
		grdFigure->AddCbxLbx("Step", Step);
	grdFigure->AddCol(&handles, "grdFigure", "Filter", 40, J_EBX);
	
	grdFigure->SetCellTxtAlign(J_CENTRE, 6, -1); // Symbol must display Centre
	grdFigure->SetCellTxtAlign(J_CENTRE, 7, -1 ); // Symbol must display Centre
	grdFigure->SetCellTxtAlign(J_CENTRE, 8, -1); // Line must display Centre
	grdFigure->SetCellTxtAlign(J_CENTRE, 9, -1); // Step must display Centre

	// Logo Area
	LogoArea.x = 3;
	LogoArea.y = 20;
	LogoArea.w = 100;
	LogoArea.h = 100;

	handles.Jbw_Obj = new void* [4];
	handles.Jbw_Obj[0] = static_cast<Jbw_Button*>(btnDataDir);
	handles.Jbw_Obj[1] = static_cast<Jbw_Button*>(btnPlot);
	handles.Jbw_Obj[2] = static_cast<Jbw_EditBox*>(edDataDir);
	handles.Jbw_Obj[3] = static_cast<Jbw_EditBox*>(edFileId);


	/********** PLAY AREA ********/	
	Slider = new Jbw_Slider(&handles, 1050, 300, 15, 100, 100);




	return &handles;
}

/*------------------------------------------------------------------------------------------
   PERFORM ALL RENDERING TASKS
------------------------------------------------------------------------------------------*/
void Dataplot::UserRender(void)
{
	// Clear screen
	SDL_SetRenderDrawColor(handles.Rdr, J_C_Window.r, J_C_Window.g, J_C_Window.b, J_C_Window.a);
	SDL_RenderClear(handles.Rdr);

	// Rnder the Menu
	Menu->MnuRdr();

	/*  DataPlot Heading */
	txtDataPlotName->RdrTxt();
	txtVersion->RdrTxt();

	/*  Project Detail */
	txtConfig->RdrTxt();
	txtProject->RdrTxt();

	/*  Bitplot/Wordplot Heading */
	txtBpWp->RdrTxt();

	/*  Data Directory */
	txtDataDir->RdrTxt();
	edDataDir->RdrEbx();
	btnDataDir->RdrBtn();

	/*  File ID: */
	txtFileId->RdrTxt();
	edFileId->RdrEbx();

	/*  DataSet Description  */
	txtDataSet->RdrTxt();
	edDataSet->RdrEbx();

	/*  Figure Combobox  */
	txtFigure->RdrTxt();
	cbxFigure->RdrCbx(); 

	/*  Graph Title  */
	txtTitle->RdrTxt();
	edTitle->RdrEbx();

	/*  Y Axes label  */
	txtYaxLabel->RdrTxt();
	edYaxLabel->RdrEbx();

	/*  X Axes label  */
	txtXaxLabel->RdrTxt();
	edXaxLabel->RdrEbx();

	/*   Time On/Off Button   */
	txtOnOffBtn->RdrTxt();

	/*   Messages   */
	txtMessages->RdrTxt();
	lbxMessage->RdrLbx(); 
	btnClear->RdrBtn();

	/*  Plot Buttons  */
	btnPlot->RdrBtn();
	btnPlotAll->RdrBtn();
	btnUp->RdrBtn();
	btnDown->RdrBtn();
	btnAdd->RdrBtn();

	/*   Figure Type Button   */
	txtFigBtn->RdrTxt();
	
	/*  Graph config grid   */
	grdFigure->RdrGrd();



	// !!!!   TEMP STUFF  !!!!
	lbxMessage->AddText("Lyn Een, sy Index moet 0 wees");
	lbxMessage->AddText("Lyn Twee, sy Index moet 1 wees");
	lbxMessage->AddText("Lyn Drie, sy Index moet 2 wees");
	lbxMessage->AddText("Lyn Vier, sy Index moet 3 wees");
	lbxMessage->AddText("Lyn Vyf, sy Index moet 4 wees");
	lbxMessage->AddText("Lyn Ses, sy Index moet 5 wees");
	lbxMessage->AddText("Lyn Sewe, sy Index moet 6 wees");
	lbxMessage->AddText("Lyn Agt, sy Index moet 7 wees");
	lbxMessage->AddText("Lyn Nege, sy Index moet 8 wees");
	lbxMessage->AddText("Lyn Tien, sy Index moet 9 wees");
	lbxMessage->AddText("Lyn Elf, sy Index moet 10 wees");
	lbxMessage->AddText("Lyn Twaalf, sy Index moet 11 wees");
	lbxMessage->AddText("Lyn Dertien, sy Index moet 12 wees");
	lbxMessage->AddText("Lyn Veertien, sy Index moet 13 wees");
	lbxMessage->AddText("Lyn Vyftien, sy Index moet 14 wees");
	lbxMessage->RdrLbx();

	edDataDir->Tbx->Text.assign("data.txt");
	edDataDir->Tbx->CreateTexture();
	edDataDir->RdrEbx();

	/********** PLAY AREA ********/
	Slider->RdrSldr();

	cbxPlayCopy = new Jbw_ComboBox(*cbxFigure);

	cbxPlayCopy->Obj.x = cbxFigure->Obj.x + cbxFigure->Obj.w + 20;
	cbxPlayCopy->Obj.y = cbxFigure->Obj.y + cbxFigure->Obj.h + 20;
	cbxPlayCopy->CreateCbx();
	cbxPlayCopy->RdrCbx();

	Lyn = new Jbw_Polygon(&handles, 500, 430);
	Lyn->AddPoint(515, 460);
	Lyn->AddPoint(500, 490);
	Lyn->AddPoint(500, 430);
	Lyn->LineColor = J_RED;
	Lyn->RdrPoly();

	Jbw_Polygon NoggeLyn(*Lyn);
	NoggeLyn.LineColor = J_GREEN;
	NoggeLyn.RdrPoly();
	Lyn->RdrPoly();
	delete Lyn;

	

/*
	SDL_Surface* GetSurf = SDL_GetWindowSurface(handles.Gui);
	unsigned char* pixels = new (std::nothrow) unsigned char[GetSurf->w * GetSurf->h * GetSurf->format->BytesPerPixel];
	SDL_Rect CopyArea = { 500, 100, 500, 300 };
	SDL_RenderReadPixels(handles.Rdr, &CopyArea, GetSurf->format->format, pixels, GetSurf->w* GetSurf->format->BytesPerPixel);
	SDL_Surface* saveSurface = SDL_CreateRGBSurfaceFrom(pixels, CopyArea.w, CopyArea.h,
		GetSurf->format->BitsPerPixel, GetSurf->w * GetSurf->format->BytesPerPixel,
		GetSurf->format->Rmask, GetSurf->format->Gmask, GetSurf->format->Bmask, GetSurf->format->Amask);
	
	// Create an SDL_Texture from the SDL_Surface -> Moving from RAM to Graphics card RAM
	SDL_Texture* AreaImage = SDL_CreateTextureFromSurface(handles.Rdr, saveSurface);
	
	// Set the Vieport for pasting AreaImage and Render the AreaImage
	CopyArea.x += 10;
	SDL_RenderSetViewport(handles.Rdr, &CopyArea);
	SDL_RenderCopy(handles.Rdr, AreaImage, NULL, NULL);
	SDL_RenderPresent(handles.Rdr);
	
	// Clean up memory
	SDL_FreeSurface(saveSurface); saveSurface = NULL;
	delete[] pixels; pixels = NULL;
	SDL_DestroyTexture(AreaImage); AreaImage = NULL;
	*/

	////Create texture from surface pixels
		//Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 255, 255, 255);
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);
		//LogoImage = SDL_CreateTextureFromSurface(handles.Rdr, loadedSurface);



	/**********   END PLAY AREA   ********/




	/****    SET VIEWPORT TO LOGO AREA     ****/
	SDL_RenderSetViewport(handles.Rdr, &LogoArea);
//	SDL_SetRenderDrawColor(handles.Rdr, 255, 0, 255, 255);
	SDL_RenderCopy(handles.Rdr, LogoImage, NULL, NULL); 

	/*      RENDER  USER SCREEN     */
	SDL_RenderPresent(handles.Rdr);
}

/*------------------------------------------------------------------------------------------
   PERFORM ALL RENDERING TASKS
------------------------------------------------------------------------------------------*/
void Dataplot::TheLoop(void)
{
	while (SDL_WaitEvent(&handles.Event) != 0) {
		/* BEGIN: MUST HAVE FOR JBW GUI */
		// Quit program
		if (handles.Event.type == SDL_QUIT)
		{
			break;
		}

		// Check if Window is active
		if ((SDL_GetWindowID(handles.Gui) == handles.Event.window.windowID) 
			&& handles.Event.window.event == SDL_WINDOWEVENT_ENTER) {
			handles.WindowActive = true;
			handles.Debug->NewLine("DataPlot WIndow: ACTIVE");
			continue;
		}
		else if ((SDL_GetWindowID(handles.Gui) == handles.Event.window.windowID) 
			&& handles.Event.window.event == SDL_WINDOWEVENT_LEAVE) {
			handles.WindowActive = false;
			handles.Debug->NewLine("DataPlot WIndow: IN-ACTIVE");
			continue;
		}
		/* END: MUST HAVE FOR JBW GUI */


		// Menu Events
		Menu->MnuEvent(&handles);
		//switch (Menu->MnuEvent(&handles)) {
		//case 0:

		//	break;
		//case 1:
		//	
		//	break;
		//case 2:
		//	
		//	break;
		//}

		/*  Data Directory */
		edDataDir->EbxEvent(&handles.Event);
		if (btnDataDir->BtnEvent(&handles.Event) == J_MS_LCLICK) {
			btnDataDir_Click(&handles);
		}

		/*  File ID: */
		edFileId->EbxEvent(&handles.Event);

		/*  DataSet Description */
		edDataSet->EbxEvent(&handles.Event);

		/*  Figure Combobox  */
		cbxFigure->CbxEvent(&handles.Event);

		/*  Graph Title  */
		edTitle->EbxEvent(&handles.Event);

		/*  Y Axes label */
		edYaxLabel->EbxEvent(&handles.Event);

		/*  X Axes label */
		edXaxLabel->EbxEvent(&handles.Event);

		/*   Time On/Off Button */
		

		/*   Messages   */
		if(lbxMessage->LbxEvent(&handles.Event) == J_MS_LCLICK) {
			grdFigure->Set(2, 3, lbxMessage->Index);
		}

		if (btnClear->BtnEvent(&handles.Event) == J_MS_LCLICK) {
			btnClear_Click();
		}

		/*   Grid   */
		grdFigure->GrdEvent(&handles.Event);
	
		if (grdFigure->OnChange == true) {
			grdFigure->OnChange = false;
			grdFigure_OnChange(grdFigure->GridEvent);
		}
		
		if (handles.Event.user.type == 1) {
			int sdfg = 0;
		}

		if (btnPlot->BtnEvent(&handles.Event) == J_MS_LCLICK) {
			btnPlot_Click(&handles);
		}
		if (btnPlotAll->BtnEvent(&handles.Event) == J_MS_LCLICK) {
			btnPlotAll_Click(&handles);
		}
		if (btnUp->BtnEvent(&handles.Event) == J_MS_LCLICK) {
			btnUp_Click(&handles);
		}
		if (btnDown->BtnEvent(&handles.Event) == J_MS_LCLICK) {
			btnDown_Click(&handles);
		}
		if (btnAdd->BtnEvent(&handles.Event) == J_MS_LCLICK) {
			btnAdd_Click(&handles);
		}


		handles.Debug->dbgEvent(&handles.Event);

		/********** PLAY AREA ********/
		Slider->SldrEvent(&handles.Event);
		cbxPlayCopy->CbxEvent(&handles.Event);
	}
}

/*------------------------------------------------------------------------------------------
  FUNCTION: BtnClear_Click
------------------------------------------------------------------------------------------*/
void Dataplot::btnClear_Click(void)
{
	lbxMessage->Clear();
	lbxMessage->RdrLbx();
}

/*------------------------------------------------------------------------------------------
  FUNCTION: btnDataDir_Click
------------------------------------------------------------------------------------------*/
void Dataplot::btnDataDir_Click(Jbw_Handles* h)
{
	J_Type Answer = MsgBox("REALLY", "This will take some time.\n"
		"For now just type in the full path and name.\nLike non-lazy people.", J_YESNO, 300, 300);
	if (Answer == J_NO) {
		Answer = MsgBox("YOU REALLY DON'T GET THIS ??", "This will take some time. "
			"For now just type in the full path and name. Like non-lazy people.", J_OK, 400, 300);
	}
}

/*------------------------------------------------------------------------------------------
  FUNCTION: btnPlot_Click
------------------------------------------------------------------------------------------*/
void Dataplot::btnPlot_Click(Jbw_Handles* h)
{
	//DpGraph* TmpGraph;
	DpGraph* Figure = new DpGraph(h);
	Figure->Prev = NULL;

	Figure->Next = new DpGraph(h); // Create a new instance adressed by this Figure's Next pointer
	Figure->Next->Prev = Figure; // Set the new Figure's Prev pointer to show to the current Figure.
	Figure->Next->Next = NULL; // Set the new Figure's Next pointer to NULL
	Figure = Figure->Next; // Move the Figure pointer to the new Figure.

	Figure->Next = new DpGraph(h);
	Figure->Next->Prev = Figure; 
	Figure->Next->Next = NULL; 
	Figure = Figure->Next; 
	
	Figure->GraphRender(1);
	Figure->Prev->GraphRender(2);
	Figure->Prev->Prev->GraphRender(3);
}

/*------------------------------------------------------------------------------------------
  FUNCTION: btnPlotAll_Click
------------------------------------------------------------------------------------------*/
void Dataplot::btnPlotAll_Click(Jbw_Handles* h)
{

}

/*------------------------------------------------------------------------------------------
  FUNCTION: btnAdd_Click
------------------------------------------------------------------------------------------*/
void Dataplot::btnAdd_Click(Jbw_Handles* h)
{

}

/*------------------------------------------------------------------------------------------
  FUNCTION: btnUp_Click
------------------------------------------------------------------------------------------*/
void Dataplot::btnUp_Click(Jbw_Handles* h)
{

}

/*------------------------------------------------------------------------------------------
  FUNCTION: btnDown_Click
------------------------------------------------------------------------------------------*/
void Dataplot::btnDown_Click(Jbw_Handles* h)
{

}


/*------------------------------------------------------------------------------------------
  FUNCTION: grdFigure_OnChange
------------------------------------------------------------------------------------------*/
void Dataplot::grdFigure_OnChange(Jbw_Grid::grdEvent GridEvent)
{
	if (GridEvent.Col == 6) { // color Collumn
		GridCellColorChange(GridEvent.Col, GridEvent.Row, grdFigure->GetIndex(GridEvent.Col, GridEvent.Row));
		grdFigure->RdrGrd();
	}

	if (GridEvent.Col == 8) { // color Collumn
		GridCellColorChange(GridEvent.Col, GridEvent.Row, grdFigure->GetIndex(6, GridEvent.Row));
		grdFigure->RdrGrd();
	}
}
/*------------------------------------------------------------------------------------------
FUNCTION: grdFigure_OnChange
------------------------------------------------------------------------------------------*/
	void Dataplot::GridCellColorChange(int Col, int Row, int Index)
	{
	switch (Index) {
	case 0: // Black
		grdFigure->SetCellTxtColor(J_BLACK, Col, Row);
		break;
	case 1: // Red
		grdFigure->SetCellTxtColor(J_RED, Col, Row);
		break;
	case 2: // Lime
		grdFigure->SetCellTxtColor(J_LIME, Col, Row);
		break;
	case 3: // Blue
		grdFigure->SetCellTxtColor(J_BLUE, Col, Row);
		break;
	case 4: // Magenta
		grdFigure->SetCellTxtColor(J_MAGENTA, Col, Row);
		break;
	case 5: // Cyan
		grdFigure->SetCellTxtColor(J_CYAN, Col, Row);
		break;
	case 6: // Yellow
		grdFigure->SetCellTxtColor(J_YELLOW, Col, Row);
		break;
	case 7: // Maroon
		grdFigure->SetCellTxtColor(J_MAROON, Col, Row);
		break;
	case 8: // Green
		grdFigure->SetCellTxtColor(J_GREEN, Col, Row);
		break;
	case 9: // Navy
		grdFigure->SetCellTxtColor(J_NAVY, Col, Row);
		break;
	case 10: // Teal
		grdFigure->SetCellTxtColor(J_TEAL, Col, Row);
		break;
	case 11: // Olive
		grdFigure->SetCellTxtColor(J_OLIVE, Col, Row);
		break;
	case 12: // Purple
		grdFigure->SetCellTxtColor(J_PURPLE, Col, Row);
		break;
	case 13: // Grey
		grdFigure->SetCellTxtColor(J_GREY, Col, Row);
		break;
	}
}

/*------------------------------------------------------------------------------------------
  FUNCTION: LoadConfigFile
------------------------------------------------------------------------------------------*/
void Dataplot::LoadConfigFile(std::string FileName)
{
	std::ifstream DataFile;
	DataFile.open(FileName);

	if (!DataFile)
	{
		MsgBox("FILE ERROR", "No such File", J_OK, 100, 100);
	}

	char* s = new char[200];
	int RowNum = 0;
	grdFigure->AddRow(&handles,20);

	while (!DataFile.eof()) {
//		grdFigure->AddRow(&handles);
		DataFile.getline(s, 200, 2);
		grdFigure->SetCellText(s, 0, RowNum); // Parameter
		DataFile.getline(s, 200, 2);
		grdFigure->SetCellText(s, 1, RowNum); // Size
		DataFile.getline(s, 200, 2);
		grdFigure->SetCellText(s, 2, RowNum); // Bit
		DataFile.getline(s, 200, 2);
		grdFigure->SetCellText(s, 3, RowNum); // Description
		DataFile.getline(s, 200, 2);
		grdFigure->SetCellText(s, 4, RowNum); // Offset
		DataFile.getline(s, 200, 2);
		grdFigure->SetCellText(s, 5, RowNum); // Factor
		DataFile.getline(s, 200, 2);
		grdFigure->SetCellText(s, 6, RowNum); // Colour
		GridCellColorChange(6, RowNum, grdFigure->GetIndex(6, RowNum)); // Also Change the Color of the font
		DataFile.getline(s, 200, 2);
		grdFigure->SetCellText(s, 7, RowNum); // Symbol
		DataFile.getline(s, 200, 2);
		grdFigure->SetCellText(s, 8, RowNum); // Line
		GridCellColorChange(8, RowNum, grdFigure->GetIndex(6, RowNum)); // Also Change the Color of the font
		DataFile.getline(s, 200, 2);
		grdFigure->SetCellText(s, 9, RowNum); // Step
		DataFile.getline(s, 200, 10);
		grdFigure->SetCellText(s, 10, RowNum); // Filter
		RowNum++;
	}
	delete[] s;
}