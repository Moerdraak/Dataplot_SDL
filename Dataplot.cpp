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
	Jbw_Handles h = Dp.JbwCreateLayout(); // SORT OUT Dp or handles DAMMIT

	/*   INITIAL RENDER   */
		//	ScreenArea;
	// SORT OUT Dp or handles DAMMIT
	SDL_SetRenderDrawColor(h.JbwRdr, J_C_Window.r, J_C_Window.g, J_C_Window.b, J_C_Window.a);
	SDL_RenderFillRect(h.JbwRdr, &Dp.GuiArea);


	
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


	
//	SDL_TimerID my_timer_id = SDL_AddTimer(5000, &koos, &Dp);

	Dp.UserRender();

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
				Dp.CbxPtr[I].CbxEvent(h, Dp.e);
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
Jbw_Handles Dataplot::JbwCreateLayout(void)
{
	GuiArea.x = 100; GuiArea.y = 200; GuiArea.w = 1070; GuiArea.h = 600;
	handles.JbwGui = SDL_CreateWindow("Data Plot", GuiArea.x, GuiArea.y, GuiArea.w, GuiArea.h,
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
			LogoImage = SDL_CreateTextureFromSurface(handles.JbwRdr, loadedSurface);
			SDL_FreeSurface(loadedSurface);
		}
	}
	IMG_Quit();
	
	/*  DataPlot Heading */
	Create(handles, J_TXT, "txtDataPlotName", 108, 10, 0, 0, 24, "DataPlot");
	Create(handles, J_TXT, "txtVersion", 112, 35, 0, 0, 11, "Version: c1.0");

	/*  Project Detail */
	Create(handles, J_TXT, "txt1", 112, 90, 0, 0, 12, "Loaded Config:");
	Create(handles, J_TXT, "txtProject", 202, 90, 0, 0, 12, "Rooivalk");
	Set("txtProject", "F_Bold", "1"); // make it Bold

	/*  Bitplot/Wordplot Heading */
	Create(handles, J_TXT, "txtBpWp", 360, 8, 0, 0, 18, "Bit plot");

	/*  Data Directory */
	Create(handles, J_TXT, "txtDataDir", 12, 120, 0, 0, 12, "Data Directory:");
	Create(handles, J_EBX, "edDataDir", 12, 135, 328, 18, 11);
	Set("edDataDir",  "Align", "J_LEFT");
	Create(handles, J_BTN, "btnDataDir", 339, 135, 14, 18, 12, ":");

	/*  File ID: */
	Create(handles, J_TXT, "txtFileId", 12, 155, 0, 0, 12, "File ID:");
	Create(handles, J_EBX, "edFileId", 12, 170, 40, 18, 11);
	Set("edFileId", "Align", "J_LEFT");

	/*  DataSet Description */
	Create(handles, J_TXT, "txtDataSet", 12, 190, 0, 0, 12, "Dataset Description:");
	Create(handles, J_EBX, "edDataSet", 12, 205, 300, 18, 11);
	Set("edDataSet", "Text", "Rooivalk Rocket Flight test at OTB (2019-02-03)",
		 "Align", "J_LEFT");

	/*  Figure Combobox  */
	Create(handles, J_TXT, "txtFigure", 12, 340, 0, 0, 12, "Select Figure");
	Create(handles, J_CBX, "cbxFigure", 12, 355, 300, 18, 11);
	
	Set("cbxFigure", "Align", "J_LEFT");

	/*   Figure Type Button */
	Create(handles, J_TXT, "txtFigBtn", 170, 340, 0, 0, 12, "Bitplot           Wordplot");

	/*  Title  */
	Create(handles, J_TXT, "txtTitle", 12, 375, 0, 0, 12, "Graph Title");
	Create(handles, J_EBX, "edTitle", 12, 390, 300, 18, 11);
	Set("edTitle", "Align", "J_LEFT");

	/*  Y Axes label */
	Create(handles, J_TXT, "ObjYaxLabel", 12, 410, 0, 0, 12, "Y-Axes Label");
	Create(handles, J_EBX, "edYaxLabel", 12, 425, 300, 18, 11);
	Set("edYaxLabel", "Align", "J_LEFT");

	/*  X Axes label */
	Create(handles, J_TXT, "ObjXaxLabel", 12, 445, 0, 0, 12, "X-Axes Label");
	Create(handles, J_EBX, "edXaxLabel", 12, 460, 300, 18, 11);
	Set("edXaxLabel", "Align", "J_LEFT");

	/*   Time On/Off Button */
	Create(handles, J_TXT, "txtOnOffBtn", 260, 445, 0, 0, 12, "Time");

	/*   Messages   */
	Create(handles, J_TXT, "txtMessages", 12, 480, 0, 0, 12, "Messages");
	Create(handles, J_LBX, "lbxMessage", 12, 495, 1048, 95, 11);
	Create(handles, J_BTN, "btnClear", 1020, 475, 40, 18, 12, "Clear");

	/* Plot Buttons  */
	Create(handles, J_BTN, "btnPlot", 300, 230, 40, 18, 12, "Plot");
	Create(handles, J_BTN, "btnPlotAll", 300, 250, 90, 18, 12, "Plot All Figures");
	Create(handles, J_BTN, "btnUp", 300, 270, 40, 18, 12, "Up");
	Create(handles, J_BTN, "btnDown", 300, 290, 40, 18, 12, "Down");
	Create(handles, J_BTN, "btnAdd", 300, 310, 70, 18, 12, "Add Bits");

	/*  SETUP GRAPHICS TABLE AREA   */	
	Create(handles, J_GRD, "grdFigure", 360, 35, 0, 10, 18);

	GrdPtr->AddCol(handles, "grdFigure", "Parameter", 180, J_EBX);
	GrdPtr->AddCol(handles, "grdFigure", "Size", 30, J_EBX);
	GrdPtr->AddCol(handles, "grdFigure", "Bit", 55, J_EBX);
	GrdPtr->AddCol(handles, "grdFigure", "Description", 120, J_EBX);
	GrdPtr->AddCol(handles, "grdFigure", "Offset", 40, J_EBX);
	GrdPtr->AddCol(handles, "grdFigure", "Factor", 40, J_EBX);
	GrdPtr->AddCol(handles, "grdFigure", "Colour", 70, J_CBX);
	GrdPtr->AddCol(handles, "grdFigure", "Symb.", 40, J_CBX);
	GrdPtr->AddCol(handles, "grdFigure", "Line", 40, J_CBX);
	GrdPtr->AddCol(handles, "grdFigure", "Step", 40, J_CBX);
	GrdPtr->AddCol(handles, "grdFigure", "Filter", 40, J_EBX);

	// Logo Area
	LogoArea.x = 3;
	LogoArea.y = 3;
	LogoArea.w = 100;
	LogoArea.h = 100;

	return handles;
}

/*------------------------------------------------------------------------------------------
   PERFORM ALL RENDERING TASKS
------------------------------------------------------------------------------------------*/
void Dataplot::UserRender(void)
{
	// Clear screen
	SDL_SetRenderDrawColor(handles.JbwRdr, 230, 230, 230, 255); // This sets the color you clear the screen to ( see below )
	SDL_RenderClear(handles.JbwRdr); // This clears the rendering target with the draw color set above

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
		CbxPtr[I].RdrCbx(handles); 
	}
	
	// Render Buttons  Objects	
	for (int I = 0; I < BtnCnt; I++) {
			BtnPtr[I].RdrBtn(); 
			SDL_RenderPresent(handles.JbwRdr);
	}

	// Render Grid Objects
	for (int I = 0; I < GrdCnt; I++) {
		GrdPtr[I].RdrGrd(); // ???!!!!! Write a Render call in ObjWork !!!!
	}

	SDL_RenderPresent(handles.JbwRdr);

	/****    SET VIEWPORT TO LOGO AREA     ****/
	SDL_RenderSetViewport(handles.JbwRdr, &LogoArea);
	SDL_SetRenderDrawColor(handles.JbwRdr, 255, 255, 255, 255);
	SDL_RenderCopy(handles.JbwRdr, LogoImage, NULL, NULL); // Clear Logo 

	/*      RENDER  USER SCREEN     */
	SDL_RenderPresent(handles.JbwRdr);
}



