#include "Dataplot.h"
#include "Jbw_Text.h" // Temporary here
SDL_Point* TmpPoints;

//SDL_TimerCallback koos(void) {
//	int a = 0;
//	return this
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////                             MAIN                                      ///////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{

	Dataplot Dp; 
	Dp.SetupScreen();


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
	
	
	Jbw_MsgBox Msg("TESTING TESTING", "Werk dit? \nDit werk!", J_YESNO, 100, 20);
	Jbw_MsgBox Msg1("TESTING TESTING", "Werk dit? Dit werk! Werk dit? Dit werk!", J_OK, 500, 20);


	Uint32 delay = (5000 / 10) * 10; // To round it down to the nearest 10 ms 
	
//	SDL_TimerID my_timer_id = SDL_AddTimer(delay, &koos, &Dp);

//	Dp.UserRender();

	int Rendercnt = 0;
	std::string RndrCnttxt;
//	while (1) {
//		if (SDL_PollEvent(&e)) {
	while (SDL_WaitEvent(Dp.e) != 0){
		RndrCnttxt.assign("The Render Count is now up to: ");
		RndrCnttxt.append(std::to_string(Rendercnt++));
		Dp.LbxPtr[0].AddText(RndrCnttxt);

			// User requests quit
			if (Dp.e->type == SDL_QUIT)
			{
				quit = true;
				break;
			}

			for (int I = 0; I < Dp.EbxCnt; I++) {
				Dp.EbxPtr[I].EbxEvent(Dp.e);
			}

			for (int I = 0; I < Dp.BtnCnt; I++) {
				Dp.BtnPtr[I].BtnEvent(Dp.e);
			}

			for (int I = 0; I < Dp.CbxCnt; I++) {
				Dp.CbxPtr[I].CbxEvent(Dp.e);
			}

			for (int I = 0; I < Dp.GrdCnt; I++) {
				Dp.GrdPtr[I].Event(Dp.e);
			}

		//	Dp.UserRender();

			//Figure->GraphRender(1);
			//Figure->Prev->GraphRender(2);
			//Figure->Prev->Prev->GraphRender(3);
			//	SDL_Delay(1000);
		}


	//Free resources and close SDL
	//close();

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   CONSTRUCTOR 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
Dataplot::Dataplot() {
	//Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);
	//Set texture filtering to linear
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); // WTF
//Create User Window
	UserWindow = SDL_CreateWindow("Data Plot", 100, 200, U_SCREEN_W, U_SCREEN_H, SDL_WINDOW_OPENGL);
	// Create renderer for User window
	J_Rdr = SDL_CreateRenderer(UserWindow, -1, SDL_RENDERER_ACCELERATED);

	// Initialize JPG loading
	int imgFlags = IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{/* Throw Error  Image DLL missing*/
	}

	// Initialize TrueType Fonts
	if (TTF_Init())
	{ /** TRUE TYPE FONTS DLL missing */
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   DESTRUCTOR 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
Dataplot::~Dataplot() {

	//Destroy window
	SDL_DestroyRenderer(J_Rdr);
	SDL_DestroyWindow(UserWindow);

	UserWindow = NULL;
	J_Rdr = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   INITIALISE 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Dataplot::Init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) // WTF
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create User Window
		UserWindow = SDL_CreateWindow("Data Plot", 100, 200, U_SCREEN_W, U_SCREEN_H, SDL_WINDOW_OPENGL);
		if (UserWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{			
			J_Rdr = SDL_CreateRenderer(UserWindow, -1, SDL_RENDERER_ACCELERATED); // Create renderer for window
			if (J_Rdr == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(J_Rdr, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize JPG loading
				int imgFlags = IMG_INIT_JPG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				// Initialize TrueType Fonts
				if (TTF_Init())
				{
					printf("TTF could not initialize! SDL_TTF Error: %s\n", TTF_GetError());
					success = false;
				}
			}			
		}
		
	}
	return success;
}

/*------------------------------------------------------------------------------------------
   CLOSE THE WINDOW
------------------------------------------------------------------------------------------*/
void Dataplot::Close()
{
	////Destroy window
	//SDL_DestroyRenderer(J_Rdr);
	//SDL_DestroyWindow(UserWindow);

	//UserWindow = NULL;
	//J_Rdr = NULL;

	////Quit SDL subsystems
	//IMG_Quit();
	//SDL_Quit();
	//TTF_Quit();
}
/*------------------------------------------------------------------------------------------
   SETUP SCREEN AREA 
------------------------------------------------------------------------------------------*/
bool Dataplot::SetupScreen(void)
{
	/****************  USER SCREEN  ****************/
	//	ScreenArea;
	ScreenArea.x = 0;
	ScreenArea.y = 0;
	ScreenArea.w = U_SCREEN_W;
	ScreenArea.h = U_SCREEN_H;
	SDL_SetRenderDrawColor(J_Rdr, 0xE8, 0xE8, 0xE8, 0xFF);
	SDL_RenderFillRect(J_Rdr, &ScreenArea);

	// Load the logo
	SDL_Surface* loadedSurface = IMG_Load("Jabberwock.jpg");
	if (!loadedSurface == NULL)
	{
		//Create texture from surface pixels
		LogoImage = SDL_CreateTextureFromSurface(J_Rdr, loadedSurface);
		SDL_FreeSurface(loadedSurface);
	}

	/*  DataPlot Heading */
	Create(J_Rdr, J_TXT, "txtDataPlotName", 110, 10, 0, 0, 24, "DataPlot");
	Create(J_Rdr, J_TXT, "txtVersion", 110, 35, 0, 0, 11, "Version: c1.0");

	/*  Project Detail */
	Create(J_Rdr, J_TXT, "txt1", 110, 90, 0, 0, 12, "Loaded Config:");
	Create(J_Rdr, J_TXT, "txtProject", 200, 90, 0, 0, 12, "Rooivalk");
	Set("txtProject", "F_Bold", "1"); // make it Bold

	/*  Bitplot/Wordplot Heading */
	Create(J_Rdr, J_TXT, "txtBpWp", 360, 8, 0, 0, 18, "Bit plot");

	/*  Data Directory */
	Create(J_Rdr, J_TXT, "txtDataDir", 12, 120, 0, 0, 12, "Data Directory:");
	Create(J_Rdr, J_EBX, "edDataDir", 12, 135, 328, 18, 11);
	Set("edDataDir",  "Align", "J_LEFT");
	Create(J_Rdr, J_BTN, "btnDataDir", 339, 135, 14, 18, 12, ":");

	/*  File ID: */
	Create(J_Rdr, J_TXT, "txtFileId", 12, 155, 0, 0, 12, "File ID:");
	Create(J_Rdr, J_EBX, "edFileId", 12, 170, 40, 18, 11);
	Set("edFileId", "Align", "J_LEFT");

	/*  DataSet Description */
	Create(J_Rdr, J_TXT, "txtDataSet", 12, 190, 0, 0, 12, "Dataset Description:");
	Create(J_Rdr, J_EBX, "edDataSet", 12, 205, 300, 18, 11);
	Set("edDataSet", "Text", "Rooivalk Rocket Flight test at OTB (2019-02-03)",
		 "Align", "J_LEFT");

	/*  Figure Combobox  */
	Create(J_Rdr, J_TXT, "txtFigure", 12, 340, 0, 0, 12, "Select Figure");
	Create(J_Rdr, J_CBX, "cbxFigure", 12, 355, 300, 18, 11);
	Set("cbxFigure", "Align", "J_LEFT");

	/*   Figure Type Button */
	Create(J_Rdr, J_TXT, "txtFigBtn", 170, 340, 0, 0, 12, "Bitplot           Wordplot");


	/*  Title  */
	Create(J_Rdr, J_TXT, "txtTitle", 12, 375, 0, 0, 12, "Graph Title");
	Create(J_Rdr, J_EBX, "edTitle", 12, 390, 300, 18, 11);
	Set("edTitle", "Align", "J_LEFT");

	/*  Y Axes label */
	Create(J_Rdr, J_TXT, "ObjYaxLabel", 12, 410, 0, 0, 12, "Y-Axes Label");
	Create(J_Rdr, J_EBX, "edYaxLabel", 12, 425, 300, 18, 11);
	Set("edYaxLabel", "Align", "J_LEFT");

	/*  X Axes label */
	Create(J_Rdr, J_TXT, "ObjXaxLabel", 12, 445, 0, 0, 12, "X-Axes Label");
	Create(J_Rdr, J_EBX, "edXaxLabel", 12, 460, 300, 18, 11);
	Set("edXaxLabel", "Align", "J_LEFT");

	/*   Time On/Off Button */
	Create(J_Rdr, J_TXT, "txtOnOffBtn", 260, 445, 0, 0, 12, "Time");

	/*   Messages   */
	Create(J_Rdr, J_TXT, "txtMessages", 12, 480, 0, 0, 12, "Messages");
	Create(J_Rdr, J_LBX, "lbxMessage", 12, 495, 1048, 95, 11);
	Create(J_Rdr, J_BTN, "btnClear", 1020, 475, 40, 18, 12, "Clear");

	/* Plot Buttons  */
	Create(J_Rdr, J_BTN, "btnPlot", 300, 230, 40, 18, 12, "Plot");
	Create(J_Rdr, J_BTN, "btnPlotAll", 300, 250, 90, 18, 12, "Plot All Figures");
	Create(J_Rdr, J_BTN, "btnUp", 300, 270, 40, 18, 12, "Up");
	Create(J_Rdr, J_BTN, "btnDown", 300, 290, 40, 18, 12, "Down");
	Create(J_Rdr, J_BTN, "btnAdd", 300, 310, 70, 18, 12, "Add Bits");



	/*  SETUP GRAPHICS TABLE AREA   */	
	Create(J_Rdr, J_GRD, "grdFigure", 360, 35, 11, 10);

	GrdSet("grdFigure", 0, 0,  "HdrName", "Parameter",   "ColWidth", "180");
	GrdSet("grdFigure", 0, 1,  "HdrName", "Size",		  "ColWidth", "30");
	GrdSet("grdFigure", 0, 2,  "HdrName", "Bit",		  "ColWidth", "55");
	GrdSet("grdFigure", 0, 3,  "HdrName", "Description", "ColWidth", "120");
	GrdSet("grdFigure", 0, 4,  "HdrName", "Offset",      "ColWidth", "40");
	GrdSet("grdFigure", 0, 5,  "HdrName", "Factor",	  "ColWidth", "40");
	GrdSet("grdFigure", 0, 6,  "HdrName", "Colour",	  "ColWidth", "70");
	GrdSet("grdFigure", 0, 7,  "HdrName", "Symb.",		  "ColWidth", "40");
	GrdSet("grdFigure", 0, 8,  "HdrName", "Line",		  "ColWidth", "40");
	GrdSet("grdFigure", 0, 9,  "HdrName", "Step",		  "ColWidth", "40");
	GrdSet("grdFigure", 0, 10, "HdrName", "Filter",	  "ColWidth", "40");

	GrdSet("grdFigure", 0, 0, "RowHeightAll", "16", "RowTxtSize", "10");
	GrdSet("grdFigure", 0, 0, "RowHeight", "18", "TxtSize", "12");

	// Logo Area
	LogoArea.x = 3;
	LogoArea.y = 3;
	LogoArea.w = 100;
	LogoArea.h = 100;

	return 0;
}


/*------------------------------------------------------------------------------------------
   PERFORM ALL RENDERING TASKS
------------------------------------------------------------------------------------------*/
void Dataplot::UserRender(void)
{
	// Clear screen
	SDL_SetRenderDrawColor(J_Rdr, 230, 230, 230, 255); // This sets the color you clear the screen to ( see below )
	SDL_RenderClear(J_Rdr); // This clears the rendering target with the draw color set above

	// Render Txt Objects	
	for (int I = 0; I < TxtCnt; I++) {
		TxtPtr[I].RdrTxt(); // ???!!!!! Write a Render call in ObjWork !!!!
	}

	// Render Edit Box  Objects	
	for (int I = 0; I < EbxCnt; I++) {
		EbxPtr[I].RdrEbx(); // ???!!!!! Write a Render call in ObjWork !!!!
	}

	// Render List Box  Objects	
	for (int I = 0; I < LbxCnt; I++) {
		LbxPtr[I].RdrLbx(); 
	}

	// Render Combo Box  Objects	
	for (int I = 0; I < CbxCnt; I++) {
		CbxPtr[I].RdrCbx(); 
	}

	// Render Buttons  Objects	
	for (int I = 0; I < BtnCnt; I++) {
			BtnPtr[I].RdrBtn(); 
			SDL_RenderPresent(J_Rdr);
	}

	// Render Grid Objects
	for (int I = 0; I < GrdCnt; I++) {
		GrdPtr[I].RdrGrd(); // ???!!!!! Write a Render call in ObjWork !!!!
	}

	SDL_RenderPresent(J_Rdr);

	/****    SET VIEWPORT TO LOGO AREA     ****/
	SDL_RenderSetViewport(J_Rdr, &LogoArea);
	SDL_SetRenderDrawColor(J_Rdr, 255, 255, 255, 255);
	SDL_RenderCopy(J_Rdr, LogoImage, NULL, NULL); // Clear Logo 

	/*      RENDER  USER SCREEN     */
	SDL_RenderPresent(J_Rdr);
}



