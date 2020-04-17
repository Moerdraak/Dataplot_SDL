#include "SDL.h"
#include "data.h"
#include "fft.h"
#include <stdio.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>

SDL_Window* DpWindow = NULL; // The window we'll be rendering to
SDL_Surface* wSurf = NULL; // The surface contained by the window
SDL_Surface* gXOut = NULL; // The image we will load and show on the screen
SDL_Renderer* DpRender = NULL; //The window renderer
SDL_Texture* gTexture = NULL;//Current displayed texture

SDL_Point* Xtick; int NumTicksX;
SDL_Point* Ytick; int NumTicksY;
SDL_Point* points;
//Screen dimension constants
const int SCREEN_W = 1100;
const int SCREEN_H = 600;
const int GRAPH_W = 700;
const int GRAPH_H = 500;

enum DpTxtAlign {DP_LEFT, DP_CENTRE, DP_RIGHT};
enum DpType {DP_EDITBOX, DP_TEXT, DP_LINE};

bool init(void); // Starts up SDL and creates window
bool loadMedia(); // Loads media
void close();// Frees media and shuts down SDL
void GenerateTicksX(void);
void GenerateTicksY(void);
void DoTheRender(void);

class DpEdit;
void TextSet(DpEdit *TxtObj, string NewText, const char* Var1, int Val1, const char* Var2 = "~", int Val2 = -1,
				const char* Var3 = "~", int Val3 = -1, const char* Var4 = "~", int Val4 = -1, 
				const char* Var5 = "~", int Val5 = -1, const char* Var6 = "~", int Val6 = -1);
void TextSetSub(DpEdit *TxtObj, const char* Var, int Val);



SDL_Surface* loadSurface(std::string path);
SDL_Texture* loadTexture(std::string path);
void SetupScreen(void);



/**********************************************************/
/****************   CLASS: DpEdit   ***********************/
/**********************************************************/
class DpEdit : public SDL_Rect {
public: // PRIVATE VARIABLES
	SDL_Rect Box = { 0,0,0,0 };
	SDL_Rect Frame = { 0,0,0,0 };
	std::string Text;
	TTF_Font* DpFont = NULL;
	int FontSize = 10;
	SDL_Texture* txtTexture = NULL;
	SDL_Rect txtImage = { 0,0,0,0 };
	SDL_Rect txtClip = { 0,0,0,0 };
	DpType TxtType;
	SDL_RendererFlip Flip = SDL_FLIP_NONE;
	SDL_Point RotPoint = { 0, 0 };
	int Angle = 0;
	int ActTxtW = 0;
public: // PUBLIC VARIABLES
	
	int Align = DP_LEFT;
	SDL_Color TextColor = { 0, 0, 0, 255 };
	Uint8 BackColor[4] = { 255, 255, 255, 255 };


private: // PRIVATE FUNCTIONS
	void CreateTexture(void);

public: // PUBLIC FUNCTIONS
	DpEdit(void) {};
	DpEdit(DpType Type, int x, int y, int w, int h);
	~DpEdit(){}

	void Render(void);
	void Add(string XtraText);
	void New(string NewText);
	void Del(void);
	void Back(void);
};

int ObjCnt = 0;


/**********************************************************/
/************   CLASS: DpObject:DpEdit   ******************/
/**********************************************************/
//class DpObject : public DpEdit {
//private:
//	int Id = -1;
//	int IdFocus = -1;
//public:
//	string tag = "";
//	DpObject(void) {};
//	~DpObject(void) {};
//	DpObject(DpType Type, int x, int y, int w, int h = 14) {
//		Id = ObjCnt++;
//		IdFocus = Id; // Set Focus to this object
//
//		if (Type == DP_EDITBOX || Type == DP_TEXT) {
//			TxtType = Type;
//			Box.x = x + 1; Box.y = y + 1; Box.w = w - 2; Box.h = h - 2; // Creates a border of thickness 1
//			Frame.x = x; Frame.y = y; Frame.w = w; Frame.h = h;		
//		}
//		else if (Type == DP_LINE) {
//
//		}
//	}


/**********************************************************/

//	 static DpObject  DpCreate(DpType Type, string Tag, int x, int y, int w, int h = 14) {
//
//		DpObject NewObj;// = new DpObject;
//		
//
//		//NewObj->Id = NewObj->ObjCnt++;
//		//NewObj->IdFocus = NewObj->Id; // Set Focus to this object
//
//		if (Type == DP_EDITBOX || Type == DP_TEXT) {
//			//NewObj->TxtType = Type;
//			//NewObj->Box.x = x + 1; NewObj->Box.y = y + 1; NewObj->Box.w = w - 2; NewObj->Box.h = h - 2; // Creates a border of thickness 1
//			//NewObj->Frame.x = x; NewObj->Frame.y = y; NewObj->Frame.w = w; NewObj->Frame.h = h;
//			NewObj.TxtType = Type;
//			NewObj.Box.x = x + 1; NewObj.Box.y = y + 1; NewObj.Box.w = w - 2; NewObj.Box.h = h - 2; // Creates a border of thickness 1
//			NewObj.Frame.x = x; NewObj.Frame.y = y; NewObj.Frame.w = w; NewObj.Frame.h = h;
//		}
//		else if (Type == DP_LINE) {
//
//		}
//		return NewObj;
//	}
//
//
//};


DpEdit::DpEdit(DpType Type, int x, int y, int w, int h = 14)
{
	Box.x = x + 1; Box.y = y + 1; Box.w = w - 2; Box.h = h - 2; // Creates a border of thickness 1
	Frame.x = x; Frame.y = y; Frame.w = w; Frame.h = h;
	DpFont = TTF_OpenFont("fonts/arial.ttf", FontSize); // Load the default font
	TxtType = Type;
}

void DpEdit::CreateTexture(void) {
	DpFont = TTF_OpenFont("fonts/arial.ttf", FontSize); // Load the default font
	SDL_DestroyTexture(txtTexture); // Free the memory of SDL_Texture
	SDL_Surface* txtSurf = TTF_RenderText_Blended(DpFont, Text.c_str(), TextColor); // Create Surface image from text
	txtTexture = SDL_CreateTextureFromSurface(DpRender, txtSurf); // Move it from RAM to VRAM -> Graphics card which makes it much faster

	/* Cutting Text To Size*/
	int Clip_W = 0, Clip_H = 0, Xo = 0, Yo = 0;	Xo = Box.x+1;	Yo = Box.y + (Box.h - txtSurf->h) / 2;
	ActTxtW = txtSurf->w;
	if (txtSurf->w > Box.w) {
		Clip_W = Box.w - 2; // If text is wider than box
	}
	else {
		Clip_W = txtSurf->w; // If text is equal or narrower than box
	}
	if (txtSurf->h > Box.h) {
		Clip_H = Box.h;      // If text is larger than box
	}
	else {
		Clip_H = txtSurf->h;  // If text is smaller than box
	}
	txtClip = { 0, 0, Clip_W, Clip_H };
	txtImage = { Xo, Yo , Clip_W, Clip_H };

	if (Align == DP_LEFT) { // CENTRE ALIGN TEXT
		if (Angle == 90) {
			txtImage.x += txtImage.h;   //Box.x - txtImage.w + txtImage.h;
		}
		else if (Angle == -90) {
			txtImage.x -= 2;   //Box.x - txtImage.w + txtImage.h;
			txtImage.y += Clip_W + 2;
		}
	}
	else if (Align == DP_CENTRE) { // CENTRE ALIGN TEXT
		if (txtSurf->w < Box.w) { // If text is longer than box don't centre but keep LEFT aligned.
			if (Angle == 90) {
				txtImage.x += txtImage.h; 
				txtImage.y += (Box.w - txtSurf->w) / 2;
			}
			else if (Angle == -90) {
				txtImage.x -= 2;   //Box.x - txtImage.w + txtImage.h;
				txtImage.y += txtSurf->w + (Box.w - txtSurf->w) / 2;
			}
			else {
				txtImage = { Xo + (Box.w - txtSurf->w) / 2, Yo, Clip_W, Clip_H };
			}
		}
	}
	else if (Align == DP_RIGHT) { // RIGHT ALIGN TEXT
		if (txtSurf->w < Box.w) { // If text is longer than box don't right align but keep LEFT aligned.
			if (Angle == 90) {
				txtImage.x += txtImage.h ;   //Box.x - txtImage.w + txtImage.h;
				txtImage.y += (Box.w - Clip_W);  //Box.y + Box.w;
			}
			else if (Angle == -90){
				txtImage.x -= 2;   //Box.x - txtImage.w + txtImage.h;
				txtImage.y += Box.w;
			}else{
				txtImage = { Xo + (Box.w - Clip_W), Yo, Clip_W, Clip_H };
			}
		}
	}
	SDL_FreeSurface(txtSurf); // Free the memory of SDL_Surface
}

void DpEdit::Render(void)
{
	// Create Grey Border around Edit box 
	if (TxtType == DP_EDITBOX) {
		
		if (Angle == 90 || Angle == -90) {
			SDL_Rect Tmp = Frame;
			Frame.w = Tmp.h;
			Frame.h = Tmp.w;

			Tmp = Box;			
			Box.w = Tmp.h;
			Box.h = Tmp.w;
		}
		SDL_SetRenderDrawColor(DpRender, 0xB0, 0xB0, 0xB0, 0xFF);  
		SDL_RenderFillRect(DpRender, &Frame);

		// Create White inside of Edit box
		SDL_SetRenderDrawColor(DpRender, BackColor[0], BackColor[1], BackColor[2], BackColor[3]); 
		SDL_RenderFillRect(DpRender, &Box);
	}
	
	SDL_RenderCopyEx(DpRender, txtTexture, &txtClip, &txtImage, Angle, &RotPoint, Flip);
}

void DpEdit::Add(string XtraText)
{
	Text.append(XtraText);
	CreateTexture();
//	Render();
}
void DpEdit::New(string NewText) {
	Text.assign(NewText);
	CreateTexture();
}

void DpEdit::Del(void)
{

}
void DpEdit::Back(void)
{	
	if (Text.length() > 1) {
		Text.pop_back();
		CreateTexture();		
	}
	else if(Text.length() > 0){
		Text.assign(" ");
		CreateTexture();
		Text.clear();
	}
}

/************  Global Objects  *********************/
DpEdit *txtFileName;
DpEdit *edFileName;
DpEdit *txtProject;
DpEdit* txtGraphTitle;
DpEdit* txtTestTitle;
DpEdit* txtLegend;
DpEdit* txtXlable;
DpEdit* txtYlable;
DpEdit* txtRandom;
DpEdit* txtDataSet;
DpEdit* edDataSet;
DpEdit* txtYaxLable;
DpEdit* edYaxLable;
DpEdit* txtXaxLable;
DpEdit* edXaxLable;

SDL_Rect ScreenArea;
SDL_Rect GraphArea;
SDL_Rect GraphAreaInside;
SDL_Rect LegendArea;
SDL_Rect LogoArea;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////                             MAIN                                      //////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{

	/**************       Do MYSTUFFS      *******************/
	TData BaseData("Data.txt"); // Read in data from a txt file
	TData FreqData;// Create pointer of TData to store answer
	Time2Freq(&BaseData, &FreqData);// Call the function that converts time based data to Frequency domain



	//Start up SDL and create window
	if (!init()) // printf("Failed to initialize!\n");
	{		
		close(); // Free resources and close SDL
		return 0;	
	}

	//Load media
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
	}

	// Setting up the screen area
	SetupScreen();


	points = new SDL_Point[1000];// = { {0, 0}, {20, 140}, {40, 10}, {60, 80} };
	double FactorX = GRAPH_W / FreqData.Xval[999] ;
	double FactorY = (double)GRAPH_H * 2 ;
	for (int I = 0; I < 1000; I++) {
		points[I].x = round(FreqData.Xval[I] * FactorX);
		points[I].y = 300 + round(FreqData.Yval[I] * FactorY) ; //+ SCREEN_HEIGHT;
		int x = 0;
	}
	   
	//Main loop flag
	bool quit = false;
	bool flag = true;

	//Event handler
	SDL_Event e;

	//While application is running
	//Handle events on Interrupt
	while (SDL_WaitEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			quit = true;
			break;
		}
		else if (e.type == SDL_TEXTINPUT)
		{
			edFileName->Add(e.text.text);
			flag = true;

		}
		else if (e.type == SDL_KEYDOWN)
		{

			//Select surfaces based on key press

			if (e.key.keysym.sym == SDLK_BACKSPACE) {
				edFileName->Back();
				flag = true;
			}else if (e.key.keysym.sym == SDLK_DELETE) {
				edFileName->Del();
				flag = true;
			}
			else if(e.key.keysym.sym){
			}			
		}

		if (flag == false) {
			continue;
		}

		flag = false;
		DoTheRender();
		////Clear screen
		//SDL_SetRenderDrawColor(DpRender, 0xE8, 0xE8, 0xE8, 0xFF); // This sets the color you clear the screen to ( see below )
		//SDL_RenderClear(DpRender); // This clears the rendering target with the draw color set above
		//		
		//// Set viewport to Main Screen
		//SDL_RenderSetViewport(DpRender, &ScreenArea);

		//// Render Legend 
		//SDL_SetRenderDrawColor(DpRender, 0xFF, 0xFF, 0xFF, 0xFF);
		//SDL_RenderFillRect(DpRender, &LegendArea);


		//// Render Objects
		//edFileName->Render();
		//txtProject->Render();
		//txtFileName->Render();
		//txtGraphTitle->Render();
		//txtTestTitle->Render();
		//txtXlable->Render();
		//txtYlable->Render();

		//// Set viewport to LogoArea
		//SDL_RenderSetViewport(DpRender, &LogoArea);
		//// Render LogoArea 
		//SDL_RenderCopy(DpRender, gTexture, NULL, NULL);

		///*     SET VIEWPORT TO GRAP AREA        */
		//SDL_RenderSetViewport(DpRender, &GraphArea);
		//SDL_SetRenderDrawColor(DpRender, 0xFF, 0xFF, 0xFF, 0xFF);
		//SDL_RenderFillRect(DpRender, &GraphAreaInside); // Clear Graph

		//// Draw X & Y Ticks
		//SDL_SetRenderDrawColor(DpRender, 0, 0, 0, 255);
		//SDL_RenderDrawLines(DpRender, Xtick, NumTicksX * 3+1);
		//SDL_RenderDrawLines(DpRender, Ytick, NumTicksY * 3 + 1);

		//// Plot Graph
		//SDL_SetRenderDrawColor(DpRender, 255, 0, 0, 255);
		//SDL_RenderDrawLines(DpRender, points, 1000);

		///*      RENDER  GRAPH     */
		//SDL_RenderPresent(DpRender);




	}
	

	//Free resources and close SDL
	close();
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   INITIALISE 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool init()
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

		//Create window
		DpWindow = SDL_CreateWindow("Data Plot", 100, 200, SCREEN_W, SCREEN_H, SDL_WINDOW_OPENGL);
		if (DpWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{			
			DpRender = SDL_CreateRenderer(DpWindow, -1, SDL_RENDERER_ACCELERATED); // Create renderer for window
			if (DpRender == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(DpRender, 0xFF, 0xFF, 0xFF, 0xFF);

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
//   LOAD MEDIA 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
//	gXOut = SDL_LoadBMP("Jabberwock.bmp");

//	gXOut = loadSurface("paint.jpg");
	gTexture = loadTexture("Jabberwock.jpg");

	if (gTexture == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "03_event_driven_programming/x.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   LOAD SURFACE
//////////////////////////////////////////////////////////////////////////////////////////////////////////
SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, wSurf->format, 0);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   LOAD TEXTURE
//////////////////////////////////////////////////////////////////////////////////////////////////////////
SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(DpRender, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   CLOSE THE WINDOW
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void close()
{
	//Deallocate surface
	SDL_FreeSurface(gXOut);
	gXOut = NULL;

	//Destroy window
	SDL_DestroyRenderer(DpRender);
	SDL_DestroyWindow(DpWindow);
	DpWindow = NULL;
	DpRender = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   SETUP SCREEN AREA 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetupScreen(void)
{
	/* TEXT: File Name */
	txtFileName = new DpEdit(DP_TEXT, 5, 120, 200, 15); // Create Edit box
	TextSet(txtFileName, "Data Directory:", "FontSize", 12, "Align", DP_CENTRE);

	/* EDIT: File Name */
	edFileName = new DpEdit(DP_EDITBOX, 5, 135, 200); // Create Edit box
	edFileName->Align = DP_LEFT;

	/* TEXT: Project Name */
	txtProject = new DpEdit(DP_TEXT, 110, 50, 200, 15); // Create Edit box
	TextSet(txtProject, "Setup: Rooivalk", "FontSize", 12, "Align", DP_LEFT);

	/* TEXT: DataSet Description */
	txtDataSet = new DpEdit(DP_TEXT, 5, 220, 200, 15); // Create Edit box
	TextSet(txtDataSet, "Dataset Description:", "FontSize", 12, "Align", DP_CENTRE);

	/* EDIT: Figure Name/Description */
	edDataSet = new DpEdit(DP_EDITBOX, 5, 235, 200); // Create Edit box
	edDataSet->Align = DP_LEFT;

	/* TEXT: Test Title */
	txtTestTitle = new DpEdit(DP_TEXT, 300, 8, GRAPH_W, 15);
	TextSet(txtTestTitle, "Test Title", "FontSize", 12, "Align", DP_CENTRE);


	txtYaxLable = new DpEdit(DP_TEXT, 5, 400, 200, 15);
	TextSet(txtYaxLable, "X-Axes Lable", "FontSize", 12, "Align", DP_CENTRE);

	edYaxLable = new DpEdit(DP_EDITBOX, 5, 415, 200);
	edYaxLable->Align = DP_LEFT;

	txtXaxLable = new DpEdit(DP_TEXT, 5, 500, 200, 15);
	TextSet(txtXaxLable, "Y-Axes Lable", "FontSize", 12, "Align", DP_CENTRE);

	edXaxLable = new DpEdit(DP_EDITBOX, 5, 515, 200);
	TextSet(txtXaxLable, "Time (s)", "Align", DP_LEFT);


	/* TEXT: Graph Title */
	txtGraphTitle = new DpEdit(DP_TEXT, 300, 24, GRAPH_W, 15);
	//	txtGraphTitle = new DpEdit(DP_EDITBOX, 220, 87, 400);
	//	txtGraphTitle = new DpEdit(DP_EDITBOX, 238, 215, 400);
	txtGraphTitle->FontSize = 12;
	txtGraphTitle->Align = DP_CENTRE;
	txtGraphTitle->Add("Graph Title");

	/* TEXT: Legend */
	txtLegend = new DpEdit(DP_TEXT, SCREEN_W - 95, 40, 85); // Create Edit box
	txtLegend->Align = DP_CENTRE;
	txtLegend->FontSize = 12;
	txtLegend->Add("LEGEND");


	/* TEXT: X Lable */
	txtXlable = new DpEdit(DP_TEXT, 300, 570, GRAPH_W); // Create Edit box
	txtXlable->FontSize = 12;
	txtXlable->Align = DP_CENTRE;
	txtXlable->Add("X - Axes");

	/* TEXT: Y Lable */
	txtYlable = new DpEdit(DP_TEXT, 240, 40, GRAPH_H); // Create Edit box
	txtYlable->FontSize = 12;
	txtYlable->Angle = -90;
	txtYlable->Flip = SDL_FLIP_NONE;
	txtYlable->Align = DP_CENTRE;
	txtYlable->Add("Y - Axes");
	
	//	ScreenArea;
	ScreenArea.x = 0;
	ScreenArea.y = 0;
	ScreenArea.w = SCREEN_W;
	ScreenArea.h = SCREEN_H;
	SDL_SetRenderDrawColor(DpRender, 0xE8, 0xE8, 0xE8, 0xFF);
	SDL_RenderFillRect(DpRender, &ScreenArea);

	/*      Graphics Area      */
	//	SDL_Rect GraphArea;
	GraphArea.x = 300;
	GraphArea.y = 40;
	GraphArea.w = GRAPH_W;
	GraphArea.h = GRAPH_H;

	// Graphics Inside Area
	GraphAreaInside.x = 0;
	GraphAreaInside.y = 0;
	GraphAreaInside.w = GRAPH_W;
	GraphAreaInside.h = GRAPH_H;
	
	txtRandom = new DpEdit(DP_TEXT, 0, 0, 10);
	   	 
	//Legend Area
	//	SDL_Rect LegendArea;
	LegendArea.x = SCREEN_W - 95;
	LegendArea.y = 55;
	LegendArea.w = 90;
	LegendArea.h = 100;

	// Logo Area
	//	SDL_Rect LogoArea;
	LogoArea.x = 3;
	LogoArea.y = 3;
	LogoArea.w = 100;
	LogoArea.h = 100;
}















//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   PERFORM ALL RENEDERING TASKS
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void DoTheRender(void)
{
	char TmpTxt[50];
	//Clear screen
	SDL_SetRenderDrawColor(DpRender, 0xE8, 0xE8, 0xE8, 0xFF); // This sets the color you clear the screen to ( see below )
	SDL_RenderClear(DpRender); // This clears the rendering target with the draw color set above

	// Set viewport to Main Screen
	SDL_RenderSetViewport(DpRender, &ScreenArea);

	// Render Legend 
	SDL_SetRenderDrawColor(DpRender, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(DpRender, &LegendArea);

	// Render Objects
	edFileName->Render();
	txtProject->Render();
	txtFileName->Render();
	txtLegend->Render();
	txtGraphTitle->Render();
	txtTestTitle->Render();
	txtXlable->Render();
	txtYlable->Render();
	txtDataSet->Render();
	edDataSet->Render();
	txtYaxLable->Render();
	edYaxLable->Render();
	txtXaxLable->Render();
	edXaxLable->Render();

	// X Values
	int Xo = 275;
	double xxx = 453656.34;

	string MaxNum;
	MaxNum.assign(to_string(int(xxx)));
	
	int N;
	if (xxx < 10000) {
		for (int I = 0; I <= 10; I++) {
			sprintf_s(TmpTxt, "%0.2f", I * (xxx  / 10));
			TextSet(txtRandom, TmpTxt, "x", Xo+I*(GRAPH_W/10), "y", 545, "FontSize", 10, "w", 50, "h", 10, "Align", DP_CENTRE);
		}
	}	
	else {
		N = MaxNum.length()-4;
		for (int I = 0; I <= 10; I++) {
			sprintf_s(TmpTxt, "%0.2f", I * ((xxx / pow(10, N)) / 10));
			TextSet(txtRandom, TmpTxt, "x", Xo+I*(GRAPH_W/10), "y", 545, "FontSize", 10, "w", 50, "h", 10, "Align", DP_CENTRE);
		}
		
		TextSet(txtRandom, "x 10", "x", 1015, "y", 527, "FontSize", 12, "w", 30, "h", 14, "Align", DP_RIGHT);
		sprintf_s(TmpTxt, "%d", N); 
		TextSet(txtRandom, TmpTxt, "x", 1046, "y", 520, "FontSize", 10, "w", 30, "h", 10, "Align", DP_LEFT);
	}

	// Y Values
	int Yo = 540;
	 xxx = 235673;
	MaxNum.assign(to_string(int(xxx)));

	if (xxx < 10000) {
		for (int I = 10; I >=0; I--) {
			sprintf_s(TmpTxt, "%0.2f", I * (xxx / 10));
			TextSet(txtRandom, TmpTxt, "x", 252, "y", 534 - I * (GRAPH_H / 10), "FontSize", 10, "w", 50, "h", 10, "Align", DP_CENTRE);
		}
	}
	else {
		N = MaxNum.length() - 4;
		for (int I = 10; I >= 0; I--) {
			sprintf_s(TmpTxt, "%0.2f", I * ((xxx / pow(10, N)) / 10));
			TextSet(txtRandom, TmpTxt, "x", 252, "y", 534 - I * (GRAPH_H / 10), "FontSize", 10, "w", 50, "h", 10, "Align", DP_CENTRE);
		}

		TextSet(txtRandom, "x 10", "x", 262, "y", 16, "FontSize", 12, "w", 30, "h", 14, "Align", DP_RIGHT);
		sprintf_s(TmpTxt, "%d", N);
		TextSet(txtRandom, TmpTxt, "x", 292, "y", 10, "FontSize", 10, "w", 30, "h", 10, "Align", DP_LEFT);
	}


	/****    SET VIEWPORT TO LOGO AREA     ****/
	SDL_RenderSetViewport(DpRender, &LogoArea);
	SDL_SetRenderDrawColor(DpRender, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderCopy(DpRender, gTexture, NULL, NULL); // Clear Logo 

	/****    SET VIEWPORT TO GRAPH AREA     ****/
	SDL_RenderSetViewport(DpRender, &GraphArea);
	SDL_SetRenderDrawColor(DpRender, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(DpRender, &GraphAreaInside); // Clear Graph

	// Draw X & Y Ticks
	SDL_SetRenderDrawColor(DpRender, 0, 0, 0, 255);

	SDL_RenderDrawLine(DpRender, 0, 0, 0, GRAPH_H);
	for (int I = 0; I < 10; I++) {
		SDL_RenderDrawLine(DpRender, 0, I*round(GRAPH_H/10), 5, I * round(GRAPH_H / 10));
	}



	SDL_RenderDrawLine(DpRender, 0, GRAPH_H-1, GRAPH_W, GRAPH_H-1);
	for (int I = 0; I < 10; I++) {
		SDL_RenderDrawLine(DpRender, I * round(GRAPH_W / 10), GRAPH_H - 1, I * round(GRAPH_W / 10), GRAPH_H - 6);
	}
	SDL_RenderDrawLine(DpRender, 10 * round(GRAPH_W / 10)-1, GRAPH_H - 1, 10 * round(GRAPH_W / 10)-1, GRAPH_H - 6);

	// Plot Graphs
	SDL_SetRenderDrawColor(DpRender, 255, 0, 0, 255);
	SDL_RenderDrawLines(DpRender, points, 1000);

	/*      RENDER  GRAPH     */
	SDL_RenderPresent(DpRender);
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   TextSet For setting text properties on one line
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextSet(DpEdit *TxtObj, string NewText, const char* Var1, int Val1, const char* Var2, int Val2,
	const char* Var3, int Val3, const char* Var4, int Val4,
	const char* Var5, int Val5, const char* Var6, int Val6)
{
	TextSetSub(TxtObj, Var1, Val1);
	TextSetSub(TxtObj, Var2, Val2);
	TextSetSub(TxtObj, Var3, Val3);
	TextSetSub(TxtObj, Var4, Val4);
	TextSetSub(TxtObj, Var5, Val5);
	TextSetSub(TxtObj, Var6, Val6);

	TxtObj->New(NewText);
	TxtObj->Render();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Private function used by TextSet (For setting text properties on one line)
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextSetSub(DpEdit *TxtObj, const char* Var, int Val) {
	if (strcmp(Var, "x") == 0) {
		TxtObj->Box.x = Val;
	}
	if (strcmp(Var, "y") == 0) {
		TxtObj->Box.y = Val;
	}
	if (strcmp(Var, "w") == 0) {
		TxtObj->Box.w = Val;
	}
	if (strcmp(Var, "h") == 0) {
		TxtObj->Box.h = Val;
	}
	if (strcmp(Var, "Align") == 0) {
		TxtObj->Align = Val;
	}
	if (strcmp(Var, "FontSize") == 0) {
		TxtObj->FontSize = Val;
	}
	if (strcmp(Var, "Angle") == 0) {
		TxtObj->Angle = Val;
	}
//	if (strcmp(Var, "TextColor") == 0) {
//		TxtObj->TextColor = Val;
//	}
	if (strcmp(Var, "Text") == 0) {
		TxtObj->Text = Val;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   My PRINTF  Maar dit maak MEMORY LEAK !! Jy return sonder dat die memory ge-free raak
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//char* myprintf(const char *Txt, int Num) {
//	char* FormattedString = new char[1];
//	char* Tmp;
//
//	double Pos = 0;
//	while (Txt[0] != '\0') {
//		if (Txt[0] != '%' || Txt[0] == '%' && Txt[1] == '%') {
//			Tmp = new char[Pos + 1.0];
//			for (int I = 0; I < Pos; I++) {
//				 Tmp[I] = FormattedString[I];
//			}
//
//			delete[] FormattedString;
//			FormattedString = Tmp;
//			FormattedString[int(Pos)] = Txt[0];
//			Txt++;
//			Pos++;
//		}
//		else if (Txt[0] == '%' && FormattedString[int(Pos) - 1] == '%') {
//			Txt++;
//		}
//		else if (Txt[0] == '%' && Txt[1] == 'd') {
//			// Check for negative
//			if (abs(Num) != Num) {
//				// Add xtra space
//				Tmp = new char[Pos + 1.0];
//				for (int I = 0; I < Pos; I++) {
//					Tmp[I] = FormattedString[I];
//				}
//
//				delete[] FormattedString;
//				FormattedString = Tmp;
//				FormattedString[int(Pos)] = '-';
//				
//				Pos++;
//				Num = abs(Num);
//			}
//			Txt++;
//			unsigned short int  N;
//			// finding N
//			for (N = 9; N > 0; N--) {
//				if (floor(Num / pow(10, N)) > 0.0) {
//					break;
//				}
//			}
//			// Inserting digit by digit
//			for (int I = N; I >= 0; I--) {
//				Tmp = new char[Pos + 1.0];
//				for (int J = 0; J < Pos; J++) {
//					Tmp[J] = FormattedString[J];
//				}
//
//				delete[] FormattedString;
//				FormattedString = Tmp;
//
//				FormattedString[int(Pos)] = floor(Num / pow(10, I)) + 48;
//				Num = Num - floor(Num / pow(10, I)) * pow(10, I);
//				
//				Pos++;
//			}
//			Txt++;
//		}
//	}
//	FormattedString[int(Pos)] = 0;
//	return FormattedString;
//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void GenerateTicksX(void)
//{
//	int Pos = 0;
//	NumTicksX = 11;
//
//	Xtick = new SDL_Point[1 + NumTicksX * 3];
//	Xtick[Pos].x = GRAPH_W - 1; Xtick[Pos++].y = GRAPH_H - 1; // Begin Baseline from end
//	Xtick[Pos].x = 0; Xtick[Pos++].y = GRAPH_H - 1; // End Baseline at Beginning
//	for (int I = 0; I < NumTicksX - 1; 0) {
//		Xtick[Pos].x = I * (GRAPH_W / 10); Xtick[Pos++].y = GRAPH_H - 6; // Tick 0
//		Xtick[Pos].x = I * (GRAPH_W / 10); Xtick[Pos++].y = GRAPH_H - 1; // Tick 0
//		Xtick[Pos].x = (++I) * (GRAPH_W / 10); Xtick[Pos++].y = GRAPH_H - 1; // Tick 1
//	}
//	// Move last tick mark to just inside the window
//	Xtick[Pos].x = 10 * (GRAPH_W / 10) - 1; Xtick[Pos++].y = GRAPH_H - 1;
//	Xtick[Pos].x = 10 * (GRAPH_W / 10) - 1; Xtick[Pos].y = GRAPH_H - 6;
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void GenerateTicksY(void)
//{
//	int Pos = 0;
//	NumTicksY = 11;
//
//	Ytick = new SDL_Point[1 + NumTicksY * 3];
//	Ytick[Pos].x = 0; Ytick[Pos++].y = GRAPH_H - 1; // Begin Baseline from end
//	Ytick[Pos].x = 0; Ytick[Pos++].y = 0; // End Baseline at Beginning
//	for (int I = 0; I < NumTicksY - 1; 0) {
//		Ytick[Pos].x = 5; Ytick[Pos++].y = I * (GRAPH_H / 10); // Tick 0
//		Ytick[Pos].x = 0; Ytick[Pos++].y = I * (GRAPH_H / 10); // Tick 0
//		Ytick[Pos].x = 0; Ytick[Pos++].y = (++I) * (GRAPH_H / 10); // Tick 1
//	}
//	// Move last tick mark to just inside the window
//	Ytick[Pos].x = 0; Ytick[Pos++].y = 10 * (GRAPH_H / 10) - 1;
//	Ytick[Pos].x = 5; Ytick[Pos].y = 10 * (GRAPH_H / 10) - 1;
//}