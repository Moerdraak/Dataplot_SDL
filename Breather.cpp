#include "Breather.h"
#include "Jbw_Text.h" // Temporary here





HANDLE hCom;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////                             MAIN                                      ///////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{

	Dataplot Dp; 
	Jbw_Handles *h = Dp.JbwCreateLayout(); // SORT OUT Dp or handles DAMMIT

//	SetupSerialPort("COM4");

	/*   INITIAL RENDER   */
	//	ScreenArea;
	// SORT OUT Dp or handles DAMMIT
	SDL_SetRenderDrawColor(h->JbwRdr, J_C_Window.r, J_C_Window.g, J_C_Window.b, J_C_Window.a);
	SDL_RenderFillRect(h->JbwRdr, &h->GuiArea);

	// SDL_RenderPresent(Dp.J_Rdr);

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
	CloseHandle(hCom);
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
	
	// Logo Area
	LogoArea.x = 3;
	LogoArea.y = 20;
	LogoArea.w = 100;
	LogoArea.h = 100;

	/*  Dataplot Menu  */
	Menu = new Jbw_Menu(&handles);
	Menu->MenuAdd("File", 40);
	Menu->MenuAdd("Tools", 50);
	Menu->MenuAdd("Help", 40);


	/*  DataPlot Heading */
	Create(&handles, J_TXT, "txtDataPlotName", 128, 30, 0, 0, 24, "BREATHER");
	Create(&handles, J_TXT, "txtVersion", 132, 55, 0, 0, 11, "Version: 1.0");



	/*  Data Directory */
	Create(&handles, J_TXT, "txtDataDir", 12, 140, 0, 0, 12, "Data Directory:");
	edDataDir = new Jbw_EditBox(handles.JbwRdr, 12, 155, 328, 18, 11);
	edDataDir->Tag.assign("edDataDir");

	Set("edDataDir",  "Align", "J_LEFT");
	btnDataDir = new Jbw_Button(handles.JbwRdr, 339, 155, 14, 18, ":", 12);

	/*  File ID: */
	Create(&handles, J_TXT, "txtFileId", 12, 175, 0, 0, 12, "File ID:");
	Create(&handles, J_EBX, "edFileId", 12, 190, 40, 18, 11);
	Set("edFileId", "Align", "J_LEFT");

	/*  DataSet Description */
	Create(&handles, J_TXT, "txtDataSet", 12, 210, 0, 0, 12, "Dataset Description:");
	Create(&handles, J_EBX, "edDataSet", 12, 225, 300, 18, 11);
	Set("edDataSet", "Text", "TEST", "Align", "J_LEFT");

	/*  Figure Combobox  */
	Create(&handles, J_TXT, "txtFigure", 12, 340, 0, 0, 12, "Select Figure");
	Create(&handles, J_CBX, "cbxFigure", 12, 355, 300, 18, 11);
	Set("cbxFigure", "Align", "J_LEFT");


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

	/*   Messages   */
	Create(&handles, J_TXT, "txtMessages", 12, 510, 0, 0, 12, "Messages");
	Create(&handles, J_LBX, "lbxMessage", 12, 530, 380, 60, 11);
	Create(&handles, J_BTN, "btnClear", 350, 510, 40, 18, 12, "Clear");

	/* Plot Buttons  */

	btnPlot = new Jbw_Button(handles.JbwRdr, 20, 260, 40, 18, "Plot", 12);
	btnUp = new Jbw_Button(handles.JbwRdr, 70, 260, 40, 18, "One", 12);
	btnDown = new Jbw_Button(handles.JbwRdr, 120, 260, 40, 18, "Two", 12);


	/***********************  SETUP GRAPH AREA   ***************************************/
	/* TEXT: Test Title */
	txtTestTitle = new Jbw_TextBox(handles.JbwRdr, "Test Title", 440, 25, GRAPH_W, 15, 12);
	txtTestTitle->Align = J_CENTRE;

	///* TEXT: Legend */
	txtLegend = new Jbw_TextBox(handles.JbwRdr, "LEGEND", 280, 60, 100, 15, 12);
	txtLegend->Align = J_CENTRE;


	///* TEXT: X Label */
	ObjXlabel = new Jbw_TextBox(handles.JbwRdr, "Air Flow (slm)", 440, 570, GRAPH_W, 16, 12);
	ObjXlabel->Align = J_CENTRE;

	///* TEXT: Y Label */
	ObjYlabel = new Jbw_TextBox(handles.JbwRdr, "Pressure Difference (hPa)", 380, 40, GRAPH_H, 16, 12);
	ObjYlabel->Align = J_CENTRE;
	ObjYlabel->Angle = -90;;


	/*      Graphics Area      */

	//	SDL_Rect vp_Graph;
	vp_Graph.x = 440;
	vp_Graph.y = 45;
	vp_Graph.w = GRAPH_W;
	vp_Graph.h = GRAPH_H;


	// Graphics Inside Area
	GraphArea.x = 0;
	GraphArea.y = 0;
	GraphArea.w = GRAPH_W;
	GraphArea.h = GRAPH_H;

	txtRandom = new Jbw_EditBox(handles.JbwRdr, J_TXT, 0, 0, 10);

	//Legend Area
	LegendArea.x = 100;
	LegendArea.y = 40;
	LegendArea.w = 100;
	LegendArea.h = 100;

	// General Txt box
	Create(&handles, J_TXT, "txtRandom", 0, 0, 0, 0);

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

	handles.Buttons = new Jbw_Button*[10];
	handles.Buttons[0] = btnDataDir;
	handles.Buttons[1] = btnPlot;
	
	handles.Ebox = new Jbw_EditBox * [10];
	handles.Ebox[0] = edDataDir;

	hCom = SetupSerialPort("COM4");

	return &handles;
}

/*------------------------------------------------------------------------------------------
   PERFORM ALL RENDERING TASKS
------------------------------------------------------------------------------------------*/
void Dataplot::TheLoop(void)
{
	char   ReadByte[64] = { 0 };

	//while (SDL_WaitEvent(&handles.Event) != 0) {
		while(1){
		edDataDir->EbxEvent(&handles);

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

		for (int I = 0; I < LbxCnt; I++) {
			LbxPtr[I].LbxEvent(&handles);
		}

		if (btnPlot->BtnEvent(&handles) == J_BTN_CLICK) {
			btnPlot_Click(&handles);
		}

		GraphRender();
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

	edDataDir->RdrEbx();


	


	edDataDir->Text.assign("data.txt");
	edDataDir->CreateTexture();
	edDataDir->RdrEbx();



	//txtNew->RdrTbx();
	//cbxNew->RdrCbx(&handles);
	btnPlot->RdrBtn();
	btnUp->RdrBtn();
	btnDown->RdrBtn();

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



	SDL_RenderPresent(handles.JbwRdr);

	/****    SET VIEWPORT TO LOGO AREA     ****/
	SDL_RenderSetViewport(handles.JbwRdr, &LogoArea);
	SDL_SetRenderDrawColor(handles.JbwRdr, 255, 255, 255, 255);
	SDL_RenderCopy(handles.JbwRdr, LogoImage, NULL, NULL); // Clear Logo 



		// Render Legend 
	SDL_SetRenderDrawColor(handles.JbwRdr, 255, 255, 255, 255);
	SDL_RenderFillRect(handles.JbwRdr, &LegendArea);

	txtTestTitle->RdrTbx();
	txtLegend->RdrTbx();
	ObjXlabel->RdrTbx();
	ObjYlabel->RdrTbx();

	char TmpTxt[50];
	// X Values
	double xxx = 130.0;
	std::string MaxNum;
	MaxNum.assign(std::to_string(int(xxx)));

	int N;
	if (xxx < 10000) {
		for (int I = 0; I <= 10; I++) {
			sprintf_s(TmpTxt, "%0.2f", I * (xxx / 10));
			txtRandom->InitTbx(handles.JbwRdr, TmpTxt, 420 + I * (GRAPH_W / 10), 550, 50, 15, 10);
			txtRandom->Align = J_CENTRE;
			txtRandom->RdrTbx();
		}
	}
	else {
		N = (int)MaxNum.length() - 4;
		for (int I = 0; I <= 10; I++) {
			sprintf_s(TmpTxt, "%0.2f", I * ((xxx / pow(10, N)) / 10));
			txtRandom->InitTbx(handles.JbwRdr, TmpTxt, 420 + I * (GRAPH_W / 10), 550, 50, 15, 10);
			txtRandom->Align = J_CENTRE;
			txtRandom->RdrTbx();
		}

		txtRandom->InitTbx(handles.JbwRdr, "x 10", 1020, 567, 30, 14, 12);
		txtRandom->Align = J_RIGHT;
		txtRandom->RdrTbx();

		sprintf_s(TmpTxt, "%d", N);
		txtRandom->InitTbx(handles.JbwRdr, TmpTxt, 1051, 560, 30, 15, 10);
		txtRandom->Align = J_LEFT;
		txtRandom->RdrTbx();
	}

	// Y Values
	xxx = 10.0;
	MaxNum.assign(std::to_string(int(xxx)));

	if (xxx < 10000) {
		for (int I = 10; I >= 0; I--) {
			sprintf_s(TmpTxt, "%0.2f", I * (xxx / 10));

			txtRandom->InitTbx(handles.JbwRdr, TmpTxt, 390, 538 - I * (GRAPH_H / 10), 50, 15, 10);
			txtRandom->Align = J_CENTRE;
			txtRandom->RdrTbx();
		}
	}
	else {
		N = (int)MaxNum.length() - 4;
		for (int I = 10; I >= 0; I--) {
			sprintf_s(TmpTxt, "%0.2f", I * ((xxx / pow(10, N)) / 10));
			txtRandom->InitTbx(handles.JbwRdr, TmpTxt, 390, 538 - I * (GRAPH_H / 10), 50, 15, 10);
			txtRandom->Align = J_CENTRE;
			txtRandom->RdrTbx();
		}

		sprintf_s(TmpTxt, "%d", N);
	}
	/****    SET VIEWPORT TO GRAPH AREA     ****/
	SDL_RenderSetViewport(handles.JbwRdr, &vp_Graph);
	SDL_SetRenderDrawColor(handles.JbwRdr, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(handles.JbwRdr, &GraphArea); // Clear Graph

	// Draw X & Y Ticks
	SDL_SetRenderDrawColor(handles.JbwRdr, 0, 0, 0, 255);

	SDL_RenderDrawLine(handles.JbwRdr, 0, 0, 0, GRAPH_H);
	for (int I = 0; I < 10; I++) {
		SDL_RenderDrawLine(handles.JbwRdr, 0, I * (int)round(GRAPH_H / 10), 5, I * (int)round(GRAPH_H / 10));
	}

	SDL_RenderDrawLine(handles.JbwRdr, 0, GRAPH_H - 1, GRAPH_W, GRAPH_H - 1);
	for (int I = 0; I < 10; I++) {
		SDL_RenderDrawLine(handles.JbwRdr, I * (int)round(GRAPH_W / 10), GRAPH_H - 1, I * (int)round(GRAPH_W / 10), GRAPH_H - 6);
	}
	SDL_RenderDrawLine(handles.JbwRdr, 10 * (int)round(GRAPH_W / 10) - 1, GRAPH_H - 1, 10 * (int)round(GRAPH_W / 10) - 1, GRAPH_H - 6);

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

/*------------------------------------------------------------------------------------------
  FUNCTION: btnPlot_Click
------------------------------------------------------------------------------------------*/
void Dataplot::btnPlot_Click(Jbw_Handles* h)
{

}

/*------------------------------------------------------------------------------------------
  FUNCTION: btnPlotAll_Click
------------------------------------------------------------------------------------------*/
void btnPlotAll_Click(Jbw_Handles* h)
{

}

/*------------------------------------------------------------------------------------------
  FUNCTION: btnAdd_Click
------------------------------------------------------------------------------------------*/
void btnAdd_Click(Jbw_Handles* h)
{

}

/*------------------------------------------------------------------------------------------
  FUNCTION: btnUp_Click
------------------------------------------------------------------------------------------*/
void btnUp_Click(Jbw_Handles* h)
{

}

/*------------------------------------------------------------------------------------------
  FUNCTION: SetupSerialPort
------------------------------------------------------------------------------------------*/
HANDLE SetupSerialPort(std::string ComPort)
{
	std::wstring cPort = std::wstring(ComPort.begin(), ComPort.end());
	hCom = CreateFileW(cPort.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (hCom == (HANDLE)-1) {
		return hCom;
	}
	// Do some basic settings
	DCB serialParams = { 0 };
	serialParams.DCBlength = sizeof(serialParams);

	GetCommState(hCom, &serialParams);
	serialParams.BaudRate = 9600;
	serialParams.ByteSize = 8;
	serialParams.StopBits = 2;
	serialParams.Parity = 0;
	SetCommState(hCom, &serialParams);

	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.WriteTotalTimeoutConstant = 50;
	timeout.WriteTotalTimeoutMultiplier = 10;
	SetCommTimeouts(hCom, &timeout);


	return hCom;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   GRAPH Plotting
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Dataplot::GraphRender(void)
{

	char ReadBytes[64] = { 0 };

	float Flow = 0;
	float Pressure = 0;
	char findPar[] = "Flow:";
	int cntCntPar;
	int PosStart = -1;
	int PosEnd = -1;
	std::string TmpStr;
	std::string MsgStr = "Flow: ";

	static SDL_Point* Pts = new SDL_Point[2];
	static bool Initial = true;


	float FactorX = (float)GRAPH_W / 130.0; // Max Flow rate = 120
	float FactorY = (float)GRAPH_H / 10.0;

	memset(&(ReadBytes[0]), 0, 64);
	ReadFile(hCom, ReadBytes, 64, 0, 0);
	TmpStr.append(ReadBytes, 64);
	PosStart = TmpStr.find("Flow: ");
	PosEnd = TmpStr.find(" slm", PosStart);
	if (PosEnd - PosStart > 5 && PosEnd - PosStart < 20) { // Seems like a hit
		if (Initial == true) {
			Pts[0].x = 0;
			Pts[0].y = GRAPH_H;
			Initial = false;
		}
		Pts[1].x = (int)round(stof(TmpStr.substr(PosStart + 5, PosEnd - PosStart - 5)) * FactorX);
		MsgStr.append(TmpStr.substr(PosStart + 5, PosEnd - PosStart - 5)); MsgStr.append(" slm  ["); MsgStr.append(std::to_string(Pts[1].x)); MsgStr.append("]      ");
		TmpStr.erase(0, PosEnd);
	}
	PosStart = TmpStr.find("sure: ");
	PosEnd = TmpStr.find(" hPa", PosStart);
	if (PosEnd - PosStart > 5 && PosEnd - PosStart < 20) { // Seems like a hit
		Pts[1].y = GRAPH_H -(int)round(stof(TmpStr.substr(PosStart + 5, PosEnd - PosStart - 5)) * FactorY);		
		MsgStr.append(TmpStr.substr(PosStart + 5, PosEnd - PosStart - 5)); MsgStr.append(" hPa  ["); MsgStr.append(std::to_string(Pts[1].y)); MsgStr.append("]");
		LbxPtr[0].AddText(MsgStr);
		LbxPtr[0].RdrLbx(&handles);
		TmpStr.erase(0, PosEnd);
	}

	SDL_RenderSetViewport(handles.JbwRdr, &vp_Graph);
	SDL_SetRenderDrawColor(handles.JbwRdr, 255, 0, 0, 255);
	SDL_RenderDrawLines(handles.JbwRdr, Pts, 2);
	SDL_RenderPresent(handles.JbwRdr);
	Pts[0] = Pts[1];

}