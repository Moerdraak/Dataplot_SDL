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
	Set("edDataDir", "FontSize", "10", "Align", "J_LEFT");

	/*  File ID: */
	Create(URender, tText, "txtFileId", "File ID:", 12, 155, 12);
	Create(URender, tEdit, "edFileId", J_EDIT, 12, 170, 40, 15);
	Set("edFileId", "FontSize", "10", "Align", "J_LEFT");

	/*  DataSet Description */
	Create(URender, tText, "txtDataSet", "Dataset Description:", 12, 190, 12);
	Create(URender, tEdit, "edDataSet", J_EDIT, 12, 205, 300, 15);
	Set("edDataSet", "Text", "Rooivalk Rocket Flight test at OTB (2019-02-03)",
		"FontSize", "10", "Align", "J_LEFT");

	/*  Figure Combobox  */
	Create(URender, tText, "txtFigure", "Select Figure", 12, 340, 12);
	Create(URender, tEdit, "cbxFigure", J_EDIT, 12, 355, 300);
	Set("cbxFigure", "FontSize", "10", "Align", "J_LEFT");

	/*   Figure Type Button */
	Create(URender, tText, "txtFigBtn", "Bitplot           Wordplot", 170, 340, 12);
//	Create(URender, tEdit, "btnFigBtn", J_TEXT, 208, 340, 300, 15);
//	Set("btnFigBtn", "Text", "X", "FontSize", "12", "Align", "J_LEFT");
//	Create(URender, tEdit, "btnFigBtn1", J_TEXT, 290, 340, 300, 15);
//	Set("btnFigBtn1", "Text", "X", "FontSize", "12", "Align", "J_LEFT");

	/*  Title  */
	Create(URender, tText, "txtTitle", "Graph Title", 12, 370, 12);
	Create(URender, tEdit, "edTitle", J_EDIT, 12, 385, 300);
	Set("edTitle", "FontSize", "10", "Align", "J_LEFT");

	/*  Y Axes label */
	Create(URender, tText, "txtYaxLabel", "Y-Axes Label", 12, 400, 12);
	Create(URender, tEdit, "edYaxLabel", J_EDIT, 12, 415, 300);
	Set("edYaxLabel", "FontSize", "10", "Align", "J_LEFT");

	/*  X Axes label */
	Create(URender, tText, "txtXaxLabel", "X-Axes Label", 12, 435, 12);
	Create(URender, tEdit, "edXaxLabel", J_EDIT,12, 450, 300);
	Set("edXaxLabel", "FontSize", "12", "Align", "J_LEFT");

	/*   Time On/Off Button */
	Create(URender, tText, "txtOnOffBtn", "Time", 260, 435, 12);
//	Create(URender, tEdit, "btnOnOff", J_TEXT, 290, 435, 300, 15);
//	Set("btnOnOff", "Text", "X", "FontSize", "12", "Align", "J_LEFT");

	/*  SETUP GRAPHICS TABLE AREA   */
	
//	Create(URender, tGrid, "grdFigure", 360, 35, 11, 10);
	Create(URender, tGrid, "grdFigure", 360, 100, 11, 10);
	//Set("grdFigure",)
	
	int tblX = 360, tblY = 30;
	int w1 = 180, w2 = 30, w3 = 55, w4 = 120, w5 = 40, w6 = 40,
		w7 = 70, w8 = 40, w9 = 40, w10 = 40, w11 = 40;
	int h = 18;
	

	// Header Row
	const char* BColor = "Make a lot of space available"; // Dangerous Move
	const char* FrameColor = "Make a lot of space available"; // Dangerous Move
	const char* TxtSize = "Make a lot of space available"; // Dangerous Move
	
	// Row 1 
	TxtSize = "10";
	BColor = "255 255 255";
	FrameColor = "230 230 230";

	tblX = 360;
	tblY = 30 + h - 1;
	Create(URender, tEdit, "tblhParameter0", J_EDIT, tblX, tblY, w1, h);
	Set("tblhParameter0", "FontSize", "10", "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w1 - 1;
	Create(URender, tEdit, "tblhSize0", J_EDIT, tblX, tblY, w2, h);
	Set("tblhSize0", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w2 - 1;
	Create(URender, tEdit, "tblhBit0", J_EDIT, tblX, tblY, w3, h);
	Set("tblhBit0", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w3 - 1;
	Create(URender, tEdit, "tblhDescription0", J_EDIT, tblX, tblY, w4, h);
	Set("tblhDescription0", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w4 - 1;
	Create(URender, tEdit, "tblhOffset0", J_EDIT, tblX, tblY, w5, h);
	Set("tblhOffset0", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w5 - 1;
	Create(URender, tEdit, "tblhFactor0", J_EDIT, tblX, tblY, w6, h);
	Set("tblhFactor0", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w6 - 1;
	Create(URender, tEdit, "tblhColor0", J_EDIT, tblX, tblY, w7, h);
	Set("tblhColor0", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w7 - 1;
	Create(URender, tEdit, "tblhSymbol0", J_EDIT, tblX, tblY, w8, h);
	Set("tblhSymbol0", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w8 - 1;
	Create(URender, tEdit, "tblhLine0", J_EDIT, tblX, tblY, w9, h);
	Set("tblhLine0", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w9 - 1;
	Create(URender, tEdit, "tblhStep0", J_EDIT, tblX, tblY, w10, h);
	Set("tblhStep0", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w10 - 1;
	Create(URender, tEdit, "tblhFilter0", J_EDIT, tblX, tblY, w11, h);
	Set("tblhFilter0", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);

	// Row 2 
	BColor = "245 245 245";
	tblX = 360;
	tblY += h-1;
	Create(URender, tEdit, "tblhParameter1", J_EDIT, tblX, tblY, w1, h);
	Set("tblhParameter1", "FontSize", "10", "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w1 - 1;
	Create(URender, tEdit, "tblhSize1", J_EDIT, tblX, tblY, w2, h);
	Set("tblhSize1", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w2 - 1;
	Create(URender, tEdit, "tblhBit1", J_EDIT, tblX, tblY, w3, h);
	Set("tblhBit1", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w3 - 1;
	Create(URender, tEdit, "tblhDescription1", J_EDIT, tblX, tblY, w4, h);
	Set("tblhDescription1", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w4 - 1;
	Create(URender, tEdit, "tblhOffset1", J_EDIT, tblX, tblY, w5, h);
	Set("tblhOffset1", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w5 - 1;
	Create(URender, tEdit, "tblhFactor1", J_EDIT, tblX, tblY, w6, h);
	Set("tblhFactor1", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w6 - 1;
	Create(URender, tEdit, "tblhColor1", J_EDIT, tblX, tblY, w7, h);
	Set("tblhColor1", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w7 - 1;
	Create(URender, tEdit, "tblhSymbol1", J_EDIT, tblX, tblY, w8, h);
	Set("tblhSymbol1", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w8 - 1;
	Create(URender, tEdit, "tblhLine1", J_EDIT, tblX, tblY, w9, h);
	Set("tblhLine1", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w9 - 1;
	Create(URender, tEdit, "tblhStep1", J_EDIT, tblX, tblY, w10, h);
	Set("tblhStep1", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w10 - 1;
	Create(URender, tEdit, "tblhFilter1", J_EDIT, tblX, tblY, w11, h);
	Set("tblhFilter1", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);

	// Row 3 
	BColor = "255 255 255";
	tblX = 360;
	tblY += h - 1;
	Create(URender, tEdit, "tblhParameter2", J_EDIT, tblX, tblY, w1, h);
	Set("tblhParameter2", "FontSize", "10", "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w1 - 1;
	Create(URender, tEdit, "tblhSize2", J_EDIT, tblX, tblY, w2, h);
	Set("tblhSize2", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w2 - 1;
	Create(URender, tEdit, "tblhBit2", J_EDIT, tblX, tblY, w3, h);
	Set("tblhBit2", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w3 - 1;
	Create(URender, tEdit, "tblhDescription2", J_EDIT, tblX, tblY, w4, h);
	Set("tblhDescription2", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w4 - 1;
	Create(URender, tEdit, "tblhOffset2", J_EDIT, tblX, tblY, w5, h);
	Set("tblhOffset2", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w5 - 1;
	Create(URender, tEdit, "tblhFactor2", J_EDIT, tblX, tblY, w6, h);
	Set("tblhFactor2", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w6 - 1;
	Create(URender, tEdit, "tblhColor2", J_EDIT, tblX, tblY, w7, h);
	Set("tblhColor2", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w7 - 1;
	Create(URender, tEdit, "tblhSymbol2", J_EDIT, tblX, tblY, w8, h);
	Set("tblhSymbol2", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w8 - 1;
	Create(URender, tEdit, "tblhLine2", J_EDIT, tblX, tblY, w9, h);
	Set("tblhLine2", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w9 - 1;
	Create(URender, tEdit, "tblhStep2", J_EDIT, tblX, tblY, w10, h);
	Set("tblhStep2", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);
	tblX += w10 - 1;
	Create(URender, tEdit, "tblhFilter2", J_EDIT, tblX, tblY, w11, h);
	Set("tblhFilter2", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor);

	// Header Row
	tblX = 360;
	tblY = 30;
	BColor = "220 220 220";
	FrameColor = "150 150 150";
	TxtSize = "12";

	Create(URender, tEdit, "tblhParameter", J_EDIT, tblX, tblY, w1, h);
	Set("tblhParameter", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor, "Text", "Parameter");
	tblX += w1 - 1;
	Create(URender, tEdit, "tblhSize", J_EDIT, tblX, tblY, w2, h);
	Set("tblhSize", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor, "Text", "Size");
	tblX += w2 - 1;
	Create(URender, tEdit, "tblhBit", J_EDIT, tblX, tblY, w3, h);
	Set("tblhBit", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor, "Text", "Bit");
	tblX += w3 - 1;
	Create(URender, tEdit, "tblhDescription", J_EDIT, tblX, tblY, w4, h);
	Set("tblhDescription", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor, "Text", "Description");
	tblX += w4 - 1;
	Create(URender, tEdit, "tblhOffset", J_EDIT, tblX, tblY, w5, h);
	Set("tblhOffset", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor, "Text", "Offset");
	tblX += w5 - 1;
	Create(URender, tEdit, "tblhFactor", J_EDIT, tblX, tblY, w6, h);
	Set("tblhFactor", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor, "Text", "Factor");
	tblX += w6 - 1;
	Create(URender, tEdit, "tblhColor", J_EDIT, tblX, tblY, w7, h);
	Set("tblhColor", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor, "Text", "Color");
	tblX += w7 - 1;
	Create(URender, tEdit, "tblhSymbol", J_EDIT, tblX, tblY, w8, h);
	Set("tblhSymbol", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor, "Text", "Symb.");
	tblX += w8 - 1;
	Create(URender, tEdit, "tblhLine", J_EDIT, tblX, tblY, w9, h);
	Set("tblhLine", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor, "Text", "Line");
	tblX += w9 - 1;
	Create(URender, tEdit, "tblhStep", J_EDIT, tblX, tblY, w10, h);
	Set("tblhStep", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor, "Text", "Step");
	tblX += w10 - 1;
	Create(URender, tEdit, "tblhFilter", J_EDIT, tblX, tblY, w11, h);
	Set("tblhFilter", "FontSize", TxtSize, "Align", "J_CENTRE",
		"FrameColor", FrameColor, "BackColor", BColor, "Text", "Filter");
		
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



