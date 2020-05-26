#include "Dataplot.h"
#include "Jbw_Text.h" // Temporary here


SDL_Point* TmpPoints;

Uint32 koos(Uint32 interval, void* param) {
	
	Dataplot* Dp = static_cast<Dataplot*>(param);
	Dp->UserRender();
	delete Dp;
	return SDL_AddTimer(5000, &koos, param);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////                             MAIN                                      ///////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{

	Dataplot Dp; 
	Jbw_Handles *h = Dp.JbwCreateLayout(); // SORT OUT Dp or handles DAMMIT

	/******************************/
	/*   SDL TIMER STUFFS   */
	//Uint32 delay = (330 / 10) * 10; // To round it down to the nearest 10 ms 
	//SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, &Dp);
	/******************************/

	Jbw_TextBox Tmp(h, "The Lazy Quick Brown Fox jump over the fence", 400, 400, 300, 16, 11);
	Tmp.ShowFrame = true;
	Tmp.TxtColor = J_C_White;
	Tmp.CreateTexture();
	Tmp.RdrTbx();

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

//	SDL_TimerID my_timer_id = SDL_AddTimer(5000, &koos, &Dp);

	Dp.UserRender();
	Dp.TheLoop();

	return 0;
}

////////////                         END MAIN                                      ///////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Dataplot::~Dataplot() {

	//Destroy Window and Renderer
	SDL_DestroyRenderer(handles.Rdr);
	SDL_DestroyWindow(handles.JbwGui);

	handles.JbwGui = NULL;
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
	handles.JbwGui = SDL_CreateWindow("Data Plot", handles.GuiArea.x, handles.GuiArea.y, 
		handles.GuiArea.w, handles.GuiArea.h,
		SDL_WINDOW_OPENGL);
	
	// Create renderer for User window https://wiki.libsdl.org/SDL_CreateRenderer
	handles.Rdr = SDL_CreateRenderer(handles.JbwGui, -1, SDL_RENDERER_ACCELERATED);

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
	Menu->MenuAdd("Tools", 50);
	Menu->MenuAdd("Help", 40);

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
	edDataSet->Text.assign("Rooivalk Rocket Flight test at OTB (2019-02-03)");

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
	btnPlot = new Jbw_Button(&handles, 350, 250, 40, 18, "Plot", 12);
	btnPlotAll = new Jbw_Button(&handles, 350, 270, 90, 18, "Plot All Figures", 12);
	btnUp = new Jbw_Button(&handles, 350, 290, 40, 18, "Up", 12);
	btnDown = new Jbw_Button(&handles, 350, 310, 40, 18, "Down", 12);
	btnAdd = new Jbw_Button(&handles, 350, 330, 60, 18, "Add Bits", 12);

	/*  SETUP GRAPHICS TABLE AREA   */	
	grdFigure = new Jbw_Grid(&handles, 360, 55, 10, 18);

	grdFigure->AddCol(&handles, "grdFigure", "Parameter", 180, J_EBX);
	grdFigure->AddCol(&handles, "grdFigure", "Size", 30, J_EBX);
	grdFigure->AddCol(&handles, "grdFigure", "Bit", 55, J_EBX);
	grdFigure->AddCol(&handles, "grdFigure", "Description", 120, J_EBX);
	grdFigure->AddCol(&handles, "grdFigure", "Offset", 40, J_EBX);
	grdFigure->AddCol(&handles, "grdFigure", "Factor", 40, J_EBX);
	grdFigure->AddCol(&handles, "grdFigure", "Colour", 70, J_CBX);	
		std::vector<std::string> Colors = { "Black", "Blue", "Green", "Red", "Magenta", "Cyan", "111111", "123", "111222", "erg", "wfg", "wef" };
		grdFigure->AddCbxList("Colour", Colors);
	grdFigure->AddCol(&handles, "grdFigure", "Symb.", 40, J_CBX);
		std::vector<std::string> Symbols = { "*", "+", "x", "d", "s", "o" };
		grdFigure->AddCbxList("Symb.", Symbols);
	grdFigure->AddCol(&handles, "grdFigure", "Line", 40, J_CBX);
		std::vector<std::string> Lin = { "-", ":", ".", " "};
		grdFigure->AddCbxList("Line", Lin);
	grdFigure->AddCol(&handles, "grdFigure", "Step", 40, J_CBX);
		std::vector<std::string> Step = { "OFF", "ON" };
		grdFigure->AddCbxList("Step", Step);
	grdFigure->AddCol(&handles, "grdFigure", "Filter", 40, J_EBX);

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
	Menu->MnuRdr(&handles);

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

	edDataDir->Text.assign("data.txt");
	edDataDir->CreateTexture();
	edDataDir->RdrEbx();



	SDL_RenderPresent(handles.Rdr);

	/****    SET VIEWPORT TO LOGO AREA     ****/
	SDL_RenderSetViewport(handles.Rdr, &LogoArea);
	SDL_SetRenderDrawColor(handles.Rdr, 255, 255, 255, 255);
	SDL_RenderCopy(handles.Rdr, LogoImage, NULL, NULL); // Clear Logo 

	/*      RENDER  USER SCREEN     */
	SDL_RenderPresent(handles.Rdr);
}

/*------------------------------------------------------------------------------------------
   PERFORM ALL RENDERING TASKS
------------------------------------------------------------------------------------------*/
void Dataplot::TheLoop(void)
{
	while (SDL_WaitEvent(&handles.Event) != 0) {
		
		// Quit program
		if (handles.Event.type == SDL_QUIT)
		{
			break;
		}

		// Menu Events
		Menu->MnuEvent(&handles);

		/*  Data Directory */
		edDataDir->EbxEvent(&handles);
		if (btnDataDir->BtnEvent(&handles) == J_BTN_CLICK) {
			btnDataDir_Click(&handles);
		}

		/*  File ID: */
		edFileId->EbxEvent(&handles);

		/*  DataSet Description */
		edDataSet->EbxEvent(&handles);

		/*  Figure Combobox  */
		cbxFigure->CbxEvent(); 

		/*  Graph Title  */
		edTitle->EbxEvent(&handles);

		/*  Y Axes label */
		edYaxLabel->EbxEvent(&handles);

		/*  X Axes label */
		edXaxLabel->EbxEvent(&handles);

		/*   Time On/Off Button */
		

		/*   Messages   */
		if(lbxMessage->LbxEvent(&handles) == J_BTN_CLICK) {
			grdFigure->Set(2, 3, lbxMessage->Index);
		}

		if (btnClear->BtnEvent(&handles) == J_BTN_CLICK) {
			btnClear_Click(&handles);
		}

		/*   Grid   */
		grdFigure->GrdEvent(&handles);

		if (btnPlot->BtnEvent(&handles) == J_BTN_CLICK) {
			btnPlot_Click(&handles);
		}
		if (btnPlotAll->BtnEvent(&handles) == J_BTN_CLICK) {
			btnPlotAll_Click(&handles);
		}
		if (btnUp->BtnEvent(&handles) == J_BTN_CLICK) {
			btnUp_Click(&handles);
		}
		if (btnDown->BtnEvent(&handles) == J_BTN_CLICK) {
			btnDown_Click(&handles);
		}
		if (btnAdd->BtnEvent(&handles) == J_BTN_CLICK) {
			btnAdd_Click(&handles);
		}
	}
}

/*------------------------------------------------------------------------------------------
  FUNCTION: BtnClear_Click
------------------------------------------------------------------------------------------*/
void Dataplot::btnClear_Click(Jbw_Handles* h)
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
