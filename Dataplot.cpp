#include "Dataplot.h"
#include "Jbw_Text.h" // Temporary here
SDL_Point* TmpPoints;

tE tEdit;
tL tList;
tC tCombo;
tG tGrid;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////                             MAIN                                      ///////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{

	Dataplot Dp; 
	Dp.SetupScreen();

	
	//Jbw_Polygon Poly(Dp.URender);
	//Poly.AddPoint(500, 400);
	//Poly.AddPoint(550, 450);
	//Poly.AddPoint(555, 455);
	//Poly.AddPoint(540, 400);
	//Poly.AddPoint(500, 420);
	//Poly.AddPoint(500, 400);

	//Poly.PolyRdr();




	SDL_RenderPresent(Dp.URender);
//	SDL_Renderer* Rdr, J_Type Type, int x, int y, int w, int h
//	Jbw_EditBox aa(Dp.URender,)


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
	SDL_Event e;

	//While application is running
	//Handle events on Interrupt
	 

	int Cnt = 0;

	while (SDL_WaitEvent(&e) != 0){

		Cnt += 10;
		// User requests quit
		if (e.type == SDL_QUIT)
		{
			quit = true;
			break;
		}
		else if (e.type == SDL_TEXTINPUT)
		{
	//		Dp.edDataDir->Add(e.text.text);
			flag = true;

		}
		else if (e.type == SDL_KEYDOWN)
		{

			//Select surfaces based on key press

			if (e.key.keysym.sym == SDLK_BACKSPACE) {
			//	Dp.edDataDir->BackSpace();
				flag = true;
			}else if (e.key.keysym.sym == SDLK_DELETE) {
		//		Dp.edDataDir->Del();
				flag = true;
			}
			else if(e.key.keysym.sym){
			}			
		}

	//	Dp.edDataDir->Event(&e);


		if (flag == false) {
//			continue;
		}

		flag = false;

		Dp.UserRender();



		//Figure->GraphRender(1);
		//Figure->Prev->GraphRender(2);
		//Figure->Prev->Prev->GraphRender(3);
		
		SDL_Delay(1000);
	}
	
	//Free resources and close SDL
	//close();
	Dp.Free(tEdit, "edName");

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
	URender = SDL_CreateRenderer(UserWindow, -1, SDL_RENDERER_ACCELERATED);

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
	SDL_DestroyRenderer(URender);
	SDL_DestroyWindow(UserWindow);

	UserWindow = NULL;
	URender = NULL;

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
			URender = SDL_CreateRenderer(UserWindow, -1, SDL_RENDERER_ACCELERATED); // Create renderer for window
			if (URender == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(URender, 0xFF, 0xFF, 0xFF, 0xFF);

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   CLOSE THE WINDOW
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Dataplot::Close()
{
	////Destroy window
	//SDL_DestroyRenderer(URender);
	//SDL_DestroyWindow(UserWindow);

	//UserWindow = NULL;
	//URender = NULL;

	////Quit SDL subsystems
	//IMG_Quit();
	//SDL_Quit();
	//TTF_Quit();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   SETUP SCREEN AREA 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Dataplot::SetupScreen(void)
{
	tT tText;
	tE tEdit;
	tL tList;
	/****************  USER SCREEN  ****************/
	//	ScreenArea;
	ScreenArea.x = 0;
	ScreenArea.y = 0;
	ScreenArea.w = U_SCREEN_W;
	ScreenArea.h = U_SCREEN_H;
	SDL_SetRenderDrawColor(URender, 0xE8, 0xE8, 0xE8, 0xFF);
	SDL_RenderFillRect(URender, &ScreenArea);

	// Load the logo
	SDL_Surface* loadedSurface = IMG_Load("Jabberwock.jpg");
	if (!loadedSurface == NULL)
	{
		//Create texture from surface pixels
		LogoImage = SDL_CreateTextureFromSurface(URender, loadedSurface);
		SDL_FreeSurface(loadedSurface);
	}

	/*  DataPlot Heading */
	Create(URender, tText, "txtDataPlotName", "DataPlot", 110, 10, 24);
	Create(URender, tText, "txtVersion", " Version: c1.0 ", 110, 35, 11);

	/*  Project Detail */
	Create(URender, tText, "txt1", "Loaded Config:", 110, 90, 12);
	Create(URender, tText, "txtProject", "Rooivalk", 200, 90, 12);
	Set("txtProject", "F_Bold", "1"); // make it Bold

	/*  Bitplot/Wordplot Heading */
	Create(URender, tText, "txtBpWp", "Bit plot", 360, 8, 18);

	/*  Data Directory */
	Create(URender, tText, "txtDataDir", "Data Directory:", 12, 120, 12);
	Create(URender, tEdit, "edDataDir", J_EDIT, 12, 135, 300, 15);
	Set("edDataDir", "TxtSize", "10", "Align", "J_LEFT");

	/*  File ID: */
	Create(URender, tText, "txtFileId", "File ID:", 12, 155, 12);
	Create(URender, tEdit, "edFileId", J_EDIT, 12, 170, 40, 15);
	Set("edFileId", "TxtSize", "10", "Align", "J_LEFT");

	/*  DataSet Description */
	Create(URender, tText, "txtDataSet", "Dataset Description:", 12, 190, 12);
	Create(URender, tEdit, "edDataSet", J_EDIT, 12, 205, 300, 15);
	Set("edDataSet", "Text", "Rooivalk Rocket Flight test at OTB (2019-02-03)",
		"TxtSize", "10", "Align", "J_LEFT");

	/*  Figure Combobox  */
	Create(URender, tText, "txtFigure", "Select Figure", 12, 340, 12);
	Create(URender, tEdit, "cbxFigure", J_EDIT, 12, 355, 300);
	Set("cbxFigure", "TxtSize", "10", "Align", "J_LEFT");

	/*   Figure Type Button */
	Create(URender, tText, "txtFigBtn", "Bitplot           Wordplot", 170, 340, 12);
//	Create(URender, tEdit, "btnFigBtn", J_TEXT, 208, 340, 300, 15);
//	Set("btnFigBtn", "Text", "X", "TxtSize", "12", "Align", "J_LEFT");
//	Create(URender, tEdit, "btnFigBtn1", J_TEXT, 290, 340, 300, 15);
//	Set("btnFigBtn1", "Text", "X", "TxtSize", "12", "Align", "J_LEFT");

	/*  Title  */
	Create(URender, tText, "txtTitle", "Graph Title", 12, 370, 12);
	Create(URender, tEdit, "edTitle", J_EDIT, 12, 385, 300);
	Set("edTitle", "TxtSize", "10", "Align", "J_LEFT");

	/*  Y Axes label */
	Create(URender, tText, "txtYaxLabel", "Y-Axes Label", 12, 400, 12);
	Create(URender, tEdit, "edYaxLabel", J_EDIT, 12, 415, 300);
	Set("edYaxLabel", "TxtSize", "10", "Align", "J_LEFT");

	/*  X Axes label */
	Create(URender, tText, "txtXaxLabel", "X-Axes Label", 12, 435, 12);
	Create(URender, tEdit, "edXaxLabel", J_EDIT,12, 450, 300);
	Set("edXaxLabel", "TxtSize", "12", "Align", "J_LEFT");

	/*   Time On/Off Button */
	Create(URender, tText, "txtOnOffBtn", "Time", 260, 435, 12);
//	Create(URender, tEdit, "btnOnOff", J_TEXT, 290, 435, 300, 15);
//	Set("btnOnOff", "Text", "X", "TxtSize", "12", "Align", "J_LEFT");

	/*  SETUP GRAPHICS TABLE AREA   */
	
//	Create(URender, tGrid, "grdFigure", 360, 35, 11, 10);
	Create(URender, tGrid, "grdFigure", 360, 100, 11, 10);
	// SetHdr(FontSize)
	// SetCell(FontSize)

	Grid[0]->SetColWidth(0, 180);
	Grid[0]->Element[0][0].Text.assign("Parameter");
	Grid[0]->Element[0][1].Text.assign("Size");
	Grid[0]->Element[0][2].Text.assign("Bit");
	Grid[0]->Element[0][3].Text.assign("Description");
	Grid[0]->Element[0][4].Text.assign("Offset");
	Grid[0]->Element[0][5].Text.assign("Factor");
	Grid[0]->Element[0][6].Text.assign("Colour");
	Grid[0]->Element[0][7].Text.assign("Symb.");
	Grid[0]->Element[0][8].Text.assign("Line");
	Grid[0]->Element[0][9].Text.assign("Step");
	Grid[0]->Element[0][10].Text.assign("Filter");

	Grid[0]->SetRowHeight(-1, 16);
	Grid[0]->SetRowHeight(0, 20);


	Grid[0]->SetColWidth(1, 30);
	Grid[0]->Element[0][1].Text.assign("Size");
	Grid[0]->SetColWidth(2, 55);
	Grid[0]->SetColWidth(3, 120);
	Grid[0]->SetColWidth(4, 40);
	Grid[0]->SetColWidth(5, 40);
	Grid[0]->SetColWidth(6, 70);
	Grid[0]->SetColWidth(7, 40);
	Grid[0]->SetColWidth(8, 40);
	Grid[0]->SetColWidth(9, 40);
	Grid[0]->SetColWidth(10, 40);


		
	// Logo Area
	LogoArea.x = 3;
	LogoArea.y = 3;
	LogoArea.w = 100;
	LogoArea.h = 100;

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   PERFORM ALL RENEDERING TASKS
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Dataplot::UserRender(void)
{
//	char TmpTxt[50];
	//Clear screen
	SDL_SetRenderDrawColor(URender, 230, 230, 230, 255); // This sets the color you clear the screen to ( see below )
	SDL_RenderClear(URender); // This clears the rendering target with the draw color set above

	// Set viewport to Main Screen
	SDL_RenderSetViewport(URender, &ScreenArea);

	// Render Objects 
	
	for (int I = 0; I < Size_T; I++) {
		Jtext[I]->Render(); // ???!!!!! Write a Render call in Framework !!!!
	}

	for (int I = 0; I < Size_E; I++) {
		Ebox[I]->Render(); // ???!!!!! Write a Render call in Framework !!!!
	}
	Render("grdFigure");
//	Grid[0]->GetVal(1, 2, 3.3);   //GetVal((int)2, (int)3);

	SDL_RenderPresent(URender);
	//txtProject->Render();
	//txtDataDir->Render();
	//edDataDir->Render();

	//txtDataSet->Render();
	//edDataSet->Render();
	//txtYaxLabel->Render();
	//edYaxLabel->Render();
	//txtXaxLabel->Render();
	//edXaxLabel->Render();

	/****    SET VIEWPORT TO LOGO AREA     ****/
	SDL_RenderSetViewport(URender, &LogoArea);
	SDL_SetRenderDrawColor(URender, 255, 255, 255, 255);
	SDL_RenderCopy(URender, LogoImage, NULL, NULL); // Clear Logo 

	/*      RENDER  USER SCREEN     */
	SDL_RenderPresent(URender);
}



