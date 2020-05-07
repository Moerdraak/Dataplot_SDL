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

	/*   INITIAL RENDER   */
		//	ScreenArea;
	// SORT OUT Dp or handles DAMMIT
	SDL_SetRenderDrawColor(h->JbwRdr, J_C_Window.r, J_C_Window.g, J_C_Window.b, J_C_Window.a);
	SDL_RenderFillRect(h->JbwRdr, &h->GuiArea);

	
//	SDL_RenderPresent(Dp.J_Rdr);


	//DpGraph* TmpGraph;
	//DpGraph* Figure = new DpGraph(&Dp);
	//Figure->Prev = NULL;
	//
	//Figure->Next = new DpGraph(&Dp); // Create a new instance adressed by this Figure's Next pointer
	//Figure->Next->Prev = Figure; // Set the new Figure's Prev pointer to show to the current Figure.
	//Figure->Next->Next = NULL; // Set the new Figure's Next pointer to NULL
	//Figure = Figure->Next; // Move the Figure pointer to the new Figure.


	//Figure->Next = new DpGraph(&Dp); // Create a new instance adressed by this Figure's Next pointer
	//Figure->Next->Prev = Figure; // Set the new Figure's Prev pointer to show to the current Figure.
	//Figure->Next->Next = NULL; // Set the new Figure's Next pointer to NULL
	//Figure = Figure->Next; // Move the Figure pointer to the new Figure.

	//Main loop flag
	bool quit = false;
	bool flag = true;

	//Event handler
//	SDL_Event e;

	//While application is running
	//Handle events on Interrupt
	int* Params = new int;

	/******************************/
	/*   SDL TIMER STUFFS   */
	//Uint32 delay = (330 / 10) * 10; // To round it down to the nearest 10 ms 
	//SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, &Dp);
	/******************************/
	
	
	//Jbw_MsgBox Msg("TESTING TESTING", "Werk dit? \nDit werk!", J_YESNO, 100, 20);
	//Jbw_MsgBox Msg1("TESTING TESTING", "Werk dit? Dit werk! Werk dit? Dit werk!", J_OK, 500, 20);

	Dp.CbxPtr[0].AddRow(&Dp.handles, "Cannon");
	Dp.CbxPtr[0].AddRow(&Dp.handles, "Main Sight");
	
//	SDL_TimerID my_timer_id = SDL_AddTimer(5000, &koos, &Dp);

	Dp.UserRender();

	int Rendercnt = 0;
	std::string RndrCnttxt;
//	while (1) {
//		if (SDL_PollEvent(&e)) {

	Dp.TheLoop();


	//Free resources and close SDL
	//close();

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
	SDL_DestroyRenderer(handles.JbwRdr);
	SDL_DestroyWindow(handles.JbwGui);

	handles.JbwGui = NULL;
	handles.JbwRdr = NULL;

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
	handles.JbwRdr = SDL_CreateRenderer(handles.JbwGui, -1, SDL_RENDERER_ACCELERATED);

	// Load the logo
	int imgFlags = IMG_INIT_JPG; // Initialize JPG loading
	if ((IMG_Init(imgFlags) & imgFlags)) {
		SDL_Surface* loadedSurface = IMG_Load("Jabberwock.jpg");
		if (!loadedSurface == NULL)
		{
			//Create texture from surface pixels
			Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 255, 255, 255);
			SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);
			LogoImage = SDL_CreateTextureFromSurface(handles.JbwRdr, loadedSurface);
			SDL_FreeSurface(loadedSurface);
		}
		else {
			LbxPtr[0].AddText(SDL_GetError());
		}
	}
	IMG_Quit();
	

	/***   START Framework Change Xperiment   ***/
	//void** TmpH = new void*[10];
	//handles.Jbw_Obj = TmpH;

	//Ding = new Jbw_EditBox(handles.JbwRdr, 400, 235, 328, 18, 12);

	//TmpH[0] = static_cast<Jbw_EditBox*>(Ding);	
	//Jbw_EditBox* New = static_cast<Jbw_EditBox*>(TmpH[0]);

	//MsgMsg = new Jbw_ListBox(handles.JbwRdr, 350, 350, 700, 95, 11);
	//handles.Jbw_Obj[1] = MsgMsg;

	//Tst = new Jbw_Grid(handles.JbwRdr, "Kabouter", 360, 300, 18, 5);
	//Tst->AddCol(&handles, "r", "Parameter", 180, J_EBX);
	//Tst->AddCol(&handles, "r", "Size", 30, J_EBX);
	//Tst->AddCol(&handles, "r", "Bit", 55, J_EBX);
	/***   END Framework Change Xperiment   ***/

	///////// TEXT BOX   ////////////////////
	txtNew = new Jbw_TextBox(handles.JbwRdr, "Some Basic Text", 500, 400, 300, 15, 12);
	txtNew->ShowFrame = true;
	txtNew->Border.LineColor = J_C_LGrey;
	txtNew->Border.FillColor = J_C_LGrey;
	txtNew->Align = J_CENTRE;
	txtNew->TxtColor = J_C_Black;
	txtNew->CreateTexture();

	cbxNew = new Jbw_ComboBox(handles.JbwRdr,  500, 355, 300, 18, 11, true);


	/*  Dataplot Menu  */
	Menu = new Jbw_Menu(&handles);
	Menu->MenuAdd("File", 40);
	Menu->MenuAdd("Tools", 50);
	Menu->MenuAdd("Help", 40);


	/*  DataPlot Heading */
	Create(&handles, J_TXT, "txtDataPlotName", 128, 30, 0, 0, 24, "DataPlot");
	Create(&handles, J_TXT, "txtVersion", 132, 55, 0, 0, 11, "Version: c1.0");

	/*  Project Detail */
	Create(&handles, J_TXT, "txt1", 112, 120, 0, 0, 12, "Loaded Config:");
	Create(&handles, J_TXT, "txtProject", 202, 120, 0, 0, 12, "Rooivalk");
	Set("txtProject", "F_Bold", "1"); // make it Bold

	/*  Bitplot/Wordplot Heading */
	Create(&handles, J_TXT, "txtBpWp", 360, 30, 0, 0, 18, "Bit plot");

	/*  Data Directory */
	Create(&handles, J_TXT, "txtDataDir", 12, 140, 0, 0, 12, "Data Directory:");
	Create(&handles, J_EBX, "edDataDir", 12, 155, 328, 18, 11);
	Set("edDataDir",  "Align", "J_LEFT");
//	Create(&handles, J_BTN, "btnDataDir", 339, 135, 14, 18, 12, ":");
	btnDataDir = new Jbw_Button(handles.JbwRdr, 339, 155, 14, 18, ":", 12);

	/*  File ID: */
	Create(&handles, J_TXT, "txtFileId", 12, 175, 0, 0, 12, "File ID:");
	Create(&handles, J_EBX, "edFileId", 12, 190, 40, 18, 11);
	Set("edFileId", "Align", "J_LEFT");

	/*  DataSet Description */
	Create(&handles, J_TXT, "txtDataSet", 12, 210, 0, 0, 12, "Dataset Description:");
	Create(&handles, J_EBX, "edDataSet", 12, 225, 300, 18, 11);
	Set("edDataSet", "Text", "Rooivalk Rocket Flight test at OTB (2019-02-03)",
		 "Align", "J_LEFT");

	/*  Figure Combobox  */
	Create(&handles, J_TXT, "txtFigure", 12, 340, 0, 0, 12, "Select Figure");
	Create(&handles, J_CBX, "cbxFigure", 12, 355, 300, 18, 11);
	
	Set("cbxFigure", "Align", "J_LEFT");

	/*   Figure Type Button */
	Create(&handles, J_TXT, "txtFigBtn", 170, 340, 0, 0, 12, "Bitplot           Wordplot");

	/*  Title  */
	Create(&handles, J_TXT, "txtTitle", 12, 375, 0, 0, 12, "Graph Title");
	Create(&handles, J_EBX, "edTitle", 12, 390, 300, 18, 11);
	Set("edTitle", "Align", "J_LEFT");

	/*  Y Axes label */
	Create(&handles, J_TXT, "ObjYaxLabel", 12, 410, 0, 0, 12, "Y-Axes Label");
	Create(&handles, J_EBX, "edYaxLabel", 12, 425, 300, 18, 11);
	Set("edYaxLabel", "Align", "J_LEFT");

	/*  X Axes label */
	Create(&handles, J_TXT, "ObjXaxLabel", 12, 445, 0, 0, 12, "X-Axes Label");
	Create(&handles, J_EBX, "edXaxLabel", 12, 460, 300, 18, 11);
	Set("edXaxLabel", "Align", "J_LEFT");

	/*   Time On/Off Button */
	Create(&handles, J_TXT, "txtOnOffBtn", 260, 445, 0, 0, 12, "Time");

	/*   Messages   */
	Create(&handles, J_TXT, "txtMessages", 12, 480, 0, 0, 12, "Messages");
	Create(&handles, J_LBX, "lbxMessage", 12, 495, 1048, 95, 11);
	Create(&handles, J_BTN, "btnClear", 1020, 475, 40, 18, 12, "Clear");

	/* Plot Buttons  */
	Create(&handles, J_BTN, "btnPlot", 300, 230, 40, 18, 12, "Plot");
	Create(&handles, J_BTN, "btnPlotAll", 300, 250, 90, 18, 12, "Plot All Figures");
	Create(&handles, J_BTN, "btnUp", 300, 270, 40, 18, 12, "Up");
	Create(&handles, J_BTN, "btnDown", 300, 290, 40, 18, 12, "Down");
	Create(&handles, J_BTN, "btnAdd", 300, 310, 70, 18, 12, "Add Bits");

	/*  SETUP GRAPHICS TABLE AREA   */	
//	grdFigure = new Jbw_Grid(360, 35, 0, 10, 18);

	Create(&handles, J_GRD, "grdFigure", 360, 55, 0, 10, 18);
	GrdPtr->AddCol(&handles, "grdFigure", "Parameter", 180, J_EBX);
	GrdPtr->AddCol(&handles, "grdFigure", "Size", 30, J_EBX);
	GrdPtr->AddCol(&handles, "grdFigure", "Bit", 55, J_EBX);
	GrdPtr->AddCol(&handles, "grdFigure", "Description", 120, J_EBX);
	GrdPtr->AddCol(&handles, "grdFigure", "Offset", 40, J_EBX);
	GrdPtr->AddCol(&handles, "grdFigure", "Factor", 40, J_EBX);
	GrdPtr->AddCol(&handles, "grdFigure", "Colour", 70, J_CBX);
	GrdPtr->AddCol(&handles, "grdFigure", "Symb.", 40, J_CBX);
	GrdPtr->AddCol(&handles, "grdFigure", "Line", 40, J_CBX);
	GrdPtr->AddCol(&handles, "grdFigure", "Step", 40, J_CBX);
	GrdPtr->AddCol(&handles, "grdFigure", "Filter", 40, J_EBX);

	// Logo Area
	LogoArea.x = 3;
	LogoArea.y = 20;
	LogoArea.w = 100;
	LogoArea.h = 100;
	
	// Update handles with all created Objects
	handles.TxtPtr = TxtPtr;
	handles.EbxPtr = EbxPtr;
	handles.LbxPtr = LbxPtr;
	handles.CbxPtr = CbxPtr;
	handles.BtnPtr = BtnPtr;
	handles.GrdPtr = GrdPtr;

	handles.TxtCnt = &TxtCnt;
	handles.EbxCnt = &EbxCnt;
	handles.LbxCnt = &LbxCnt;
	handles.CbxCnt = &CbxCnt;
	handles.BtnCnt = &BtnCnt;
	handles.GrdCnt = &GrdCnt;

	return &handles;
}

/*------------------------------------------------------------------------------------------
   PERFORM ALL RENDERING TASKS
------------------------------------------------------------------------------------------*/
void Dataplot::TheLoop(void)
{
	while (SDL_WaitEvent(&handles.Event) != 0) {
	//	Ding->RdrEbx();
	//	Ding->EbxEvent(&handles);
	//	MsgMsg->RdrLbx();

	//	Tst->Event(&handles);
	//	Tst->RdrGrd(&handles);
		// User requests quit

		cbxNew->CbxEvent(&handles);

		Menu->MnuEvent(&handles);

		if (handles.Event.type == SDL_QUIT)
		{
			break;
		}


		for (int I = 0; I < EbxCnt; I++) {
			EbxPtr[I].EbxEvent(&handles);
		}

		if (btnDataDir->BtnEvent(&handles) == J_BTN_CLICK) {
			btnDataDir_Click(&handles);
		}

		for (int I = 0; I < BtnCnt; I++) {		

			if (BtnPtr[I].Tag.compare("btnClear") == 0) {
				if (BtnPtr[I].BtnEvent(&handles) == J_BTN_CLICK) {
					btnClear_Click(&handles);
				}
			}
			else {
				BtnPtr[I].BtnEvent(&handles);
			}
		}

		for (int I = 0; I < CbxCnt; I++) {
			CbxPtr[I].CbxEvent(&handles);
		}

		for (int I = 0; I < GrdCnt; I++) {
			GrdPtr[I].Event(&handles);
		}

		for (int I = 0; I < LbxCnt; I++) {
			LbxPtr[I].LbxEvent(&handles);
		}

	}
}

/*------------------------------------------------------------------------------------------
   PERFORM ALL RENDERING TASKS
------------------------------------------------------------------------------------------*/
void Dataplot::UserRender(void)
{
	// Clear screen
	SDL_SetRenderDrawColor(handles.JbwRdr, J_C_Window.r, J_C_Window.g, J_C_Window.b, J_C_Window.a); 
	SDL_RenderClear(handles.JbwRdr); 

	// Rnder the Menu
	Menu->MnuRdr(&handles);




	LbxPtr[0].AddText("Eeen");
	LbxPtr[0].AddText("Tweee");
	LbxPtr[0].AddText("Drieen");
	LbxPtr[0].AddText("Vieeeeeeeeeer");

	//Ding->RdrEbx();
	//Tst->RdrGrd(&handles);

	txtNew->RdrTbx();
	cbxNew->RdrCbx(&handles);

	// Render Txt Objects	
	for (int I = 0; I < TxtCnt; I++) {
		TxtPtr[I].RdrTxt(); // ???!!!!! Write a Render call in ObjWork !!!!
		SDL_RenderPresent(handles.JbwRdr);
	}

	// Render Edit Box  Objects	
	for (int I = 0; I < EbxCnt; I++) {
		EbxPtr[I].RdrEbx(); // ???!!!!! Write a Render call in ObjWork !!!!
	}

	// Render List Box  Objects	
	for (int I = 0; I < LbxCnt; I++) {
		LbxPtr[I].RdrLbx(&handles);
	}
	
	// Render Combo Box  Objects	
	for (int I = 0; I < CbxCnt; I++) {
		CbxPtr[I].RdrCbx(&handles); 
	}
	
	// Render Buttons  Objects	
	btnDataDir->RdrBtn();
	for (int I = 0; I < BtnCnt; I++) {
			BtnPtr[I].RdrBtn(); 
			SDL_RenderPresent(handles.JbwRdr);
	}

	// Render Grid Objects
	for (int I = 0; I < GrdCnt; I++) {
		GrdPtr[I].RdrGrd(&handles); // ???!!!!! Write a Render call in ObjWork !!!!
	}

	SDL_RenderPresent(handles.JbwRdr);

	/****    SET VIEWPORT TO LOGO AREA     ****/
	SDL_RenderSetViewport(handles.JbwRdr, &LogoArea);
	SDL_SetRenderDrawColor(handles.JbwRdr, 255, 255, 255, 255);
	SDL_RenderCopy(handles.JbwRdr, LogoImage, NULL, NULL); // Clear Logo 

	/*      RENDER  USER SCREEN     */
	SDL_RenderPresent(handles.JbwRdr);
}

/*------------------------------------------------------------------------------------------
  FUNCTION: BtnClear_Click
------------------------------------------------------------------------------------------*/
void Dataplot::btnClear_Click(Jbw_Handles* h)
{
	lbxClear("lbxMessage");
//	MsgMsg->Clear();
//	MsgMsg->RdrLbx();
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