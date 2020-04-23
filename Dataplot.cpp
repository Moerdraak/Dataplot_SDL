#include "Dataplot.h"

SDL_Point* TmpPoints;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////                             MAIN                                      ///////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	tE tEdit;
	tL tList;

	Dataplot Dp; 


	Dp.SetupScreen();
	
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

	/* TEXT: File Name */
	Create(URender, tEdit, "txtDataDir", J_TEXT, 500, 50, 300, 16);
	Set("txtDataDir", "Text", "Data Directory:", "FontSize", "12",
		"Align", "J_CENTRE", "Box", "300 100 100 16", "TextColor", "0 0 255");


	//txtDataDir = new Jbw_EditBox(URender, J_TEXT, 5, 120, 300, 15); // Create Edit box
	//txtDataDir->Set("Data Directory:", "FontSize", 12, "Align", J_CENTRE);

	///* EDIT: File Name */
	//edDataDir = new Jbw_EditBox(URender, J_EDIT, 5, 135, 300); // Create Edit box
	//edDataDir->Align = J_LEFT;

	///* TEXT: Project Name */
	//txtProject = new Jbw_EditBox(URender, J_TEXT, 110, 50, 300, 15); // Create Edit box
	//txtProject->Set("Setup: Rooivalk", "FontSize", 12, "Align", J_LEFT);

	///* TEXT: DataSet Description */
	//txtDataSet = new Jbw_EditBox(URender, J_TEXT, 5, 220, 300, 15); // Create Edit box
	//txtDataSet->Set("Dataset Description:", "FontSize", 12, "Align", J_CENTRE);

	///* EDIT: Figure Name/Description */
	//edDataSet = new Jbw_EditBox(URender, J_EDIT, 5, 235, 300); // Create Edit box
	//edDataSet->Set("Rooivalk Rocket Flight test at OTB (2019-02-03)", "Align", J_LEFT);

	//txtYaxLabel = new Jbw_EditBox(URender, J_TEXT, 5, 400, 300, 15);
	//txtYaxLabel->Set("X-Axes Label", "FontSize", 12, "Align", J_CENTRE);

	//edYaxLabel = new Jbw_EditBox(URender, J_EDIT, 5, 415, 300);
	//edYaxLabel->Align = J_LEFT;

	//txtXaxLabel = new Jbw_EditBox(URender, J_TEXT, 5, 500, 300, 15);
	//txtXaxLabel->Set("Y-Axes Label", "FontSize", 12, "Align", J_CENTRE);

	//edXaxLabel = new Jbw_EditBox(URender, J_EDIT, 5, 515, 300);
	//edXaxLabel->Set("Time (s)", "Align", J_LEFT);

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
	for (int I = 0; I < Size_E; I++) {
		Ebox[I]->Render();
	}

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



