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

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

bool init(void); // Starts up SDL and creates window
bool loadMedia(); // Loads media
void close();// Frees media and shuts down SDL
SDL_Surface* loadSurface(std::string path);
SDL_Texture* loadTexture(std::string path);


enum DpTxtAlign {DP_LEFT, DP_CENTRE, DP_RIGHT};
enum DpType {DP_EDITBOX, DP_TEXT, DP_LINE};

class DpEdit : public SDL_Rect {
public: // PRIVATE VARIABLES
	SDL_Rect Box = { 0,0,0,0 };
	SDL_Rect Frame = { 0,0,0,0 };
	std::string Text = " ";
	TTF_Font* DpFont = NULL;
	int FontSize = 10;
	SDL_Texture* txtTexture = NULL;
	SDL_Rect txtImage = { 0,0,0,0 };
	SDL_Rect txtClip = { 0,0,0,0 };
	DpType TxtType;
public: // PUBLIC VARIABLES
	
	int Align = DP_LEFT;
	SDL_Color TextColor = { 0, 0, 0, 255 };
	Uint8 BackColor[4] = { 255, 255, 255, 255 };


private: // PRIVATE FUNCTIONS
	void CreateTexture(void);

public: // PUBLIC FUNCTIONS
	DpEdit(void) {};
	DpEdit(int x, int y, int w, int h);
	~DpEdit(){}

	void Render(void);
	void Add(string XtraText);
	void Del(void);
	void Back(void);
};

int ObjCnt = 0;



class DpObject : public DpEdit {
private:
	int Id = -1;
	int IdFocus = -1;
public:
	string tag = "";

	DpObject(DpType Type, int x, int y, int w, int h = 14) {
		Id = ObjCnt++;
		IdFocus = Id; // Set Focus to this object

		if (Type == DP_EDITBOX || Type == DP_TEXT) {
			TxtType = Type;
			Box.x = x + 1; Box.y = y + 1; Box.w = w - 2; Box.h = h - 2; // Creates a border of thickness 1
			Frame.x = x; Frame.y = y; Frame.w = w; Frame.h = h;
			
		}
		else if (Type == DP_LINE) {

		}
	}
};


//DpEdit::DpEdit(int x, int y, int w, int h = 14)
//{
//	Box.x = x + 1; Box.y = y + 1; Box.w = w - 2; Box.h = h - 2; // Creates a border of thickness 1
//	Frame.x = x; Frame.y = y; Frame.w = w; Frame.h = h;
//	DpFont = TTF_OpenFont("fonts/arial.ttf", FontSize); // Load the default font
//}

void DpEdit::CreateTexture(void) {
	DpFont = TTF_OpenFont("fonts/arial.ttf", FontSize); // Load the default font
	SDL_DestroyTexture(txtTexture); // Free the memory of SDL_Texture
	SDL_Surface* txtSurf = TTF_RenderText_Blended(DpFont, Text.c_str(), TextColor); // Create Surface image from text
	txtTexture = SDL_CreateTextureFromSurface(DpRender, txtSurf); // Move it from RAM to VRAM -> Graphics card which makes it much faster

	/* Cutting Text To Size*/
	int Clip_W = 0, Clip_H = 0, Box_X = 0, Box_Y = 0;
	Box_X = Box.x + 1;
	Box_Y = Box.y + (Box.h - txtSurf->h) / 2;

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
	txtImage = { Box_X, Box_Y , Clip_W, Clip_H };

	if (Align == DP_CENTRE) { // CENTRE ALIGN TEXT
		if (txtSurf->w < Box.w) { // If text is longer than box don't centre but keep LEFT aligned.
			txtImage = { Box_X + (Box.w - txtSurf->w) / 2, Box_Y, Clip_W, Clip_H };
		}
	}
	else if (Align == DP_RIGHT) { // RIGHT ALIGN TEXT
		if (txtSurf->w < Box.w) { // If text is longer than box don't right align but keep LEFT aligned.
			txtImage = { Box_X + (Box.w - Clip_W), Box_Y, Clip_W, Clip_H };
		}
	}

	SDL_FreeSurface(txtSurf); // Free the memory of SDL_Surface
}

void DpEdit::Render(void)
{
	if (TxtType == DP_EDITBOX) {
		SDL_SetRenderDrawColor(DpRender, 0xB0, 0xB0, 0xB0, 0xFF); // Create Grey Border around Edit box  
		SDL_RenderFillRect(DpRender, &Frame);
		SDL_SetRenderDrawColor(DpRender, BackColor[0], BackColor[1], BackColor[2], BackColor[3]); // Create White inside of Edit box
		SDL_RenderFillRect(DpRender, &Box);
	}
	SDL_RenderCopyEx(DpRender, txtTexture, &txtClip, &txtImage, 0, 0, SDL_FLIP_NONE);
}

void DpEdit::Add(string XtraText)
{
	Text.append(XtraText);
	CreateTexture();
//	Render();
}
void DpEdit::Del(void)
{

}
void DpEdit::Back(void)
{
	Text.pop_back();
	if (Text.length() == 0) {
		Text = " ";
	}
	CreateTexture();
//	Render();
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////                             MAIN                                      //////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{

	/*             Do MYSTUFFS           */
	TData BaseData("Data.txt"); // Read in data from a txt file
	TData FreqData;// Create pointer of TData to store answer
	Time2Freq(&BaseData, &FreqData);// Call the function that converts time based data to Frequency domain


	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
//
	IMG_Init(imgFlags);
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
//		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}


//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
	

			SDL_SetRenderDrawColor(DpRender, 0xFF, 0xFF, 0xFF, 255); // Color from within the rectangle
			//Update screen
			SDL_RenderPresent(DpRender);

	//		DpObject Handles[10];
			DpObject txtFileName(DP_TEXT, 5, 40, 200); // Create Edit box
			txtFileName.Align = DP_CENTRE;
			txtFileName.FontSize = 12;
			txtFileName.Add("File Name:");

			DpObject edFileName(DP_EDITBOX, 5, 55, 200); // Create Edit box
			edFileName.Align = DP_LEFT;
			edFileName.Add("");

			DpObject edProject(DP_EDITBOX, 100, 500, 100); // Create Edit box
			
			edProject.Align = DP_RIGHT;
			edProject.Add("");

			


			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_TEXTINPUT)
					{
						edFileName.Add(e.text.text);
					}
					else if (e.type == SDL_KEYDOWN)
					{
			
						//Select surfaces based on key press

						if (e.key.keysym.sym == SDLK_BACKSPACE) {
							edFileName.Back();
						}else if (e.key.keysym.sym == SDLK_DELETE) {
							edFileName.Del();
						}
						else if(e.key.keysym.sym){
						}
						
					}

				}

				//Clear screen
				SDL_SetRenderDrawColor(DpRender, 0xE8, 0xE8, 0xE8, 0xFF); // This sets the color you clear the screen to ( see below )
				SDL_RenderClear(DpRender); // This clears the rendering target with the draw color set above

				//Graphics Area
				SDL_Rect GraphArea;
				GraphArea.x = 300;
				GraphArea.y = 40;
				GraphArea.w = SCREEN_WIDTH - 400;
				GraphArea.h = SCREEN_HEIGHT - 100;

				SDL_SetRenderDrawColor(DpRender, 0xFF, 0xFF, 0xFF, 0x00);
				SDL_RenderFillRect(DpRender, &GraphArea);

				SDL_RenderFillRect(DpRender, &GraphArea);

				//Legend Area
				SDL_Rect LegendArea;
				LegendArea.x = SCREEN_WIDTH - 95;
				LegendArea.y = 40;
				LegendArea.w = 85;
				LegendArea.h = 100;
				SDL_RenderFillRect(DpRender, &LegendArea);

				
				edFileName.Render();
				edProject.Render();
				txtFileName.Render();

				//SDL_RenderCopy(gRenderer, TextTexture, NULL, &destination);

			//	SDL_RenderSetViewport(gRenderer, &topLeftViewport);

				//Render texture to screen
			//	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
		
				//Update screen
				SDL_RenderPresent(DpRender);
				SDL_Delay(10);
			}
		}
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
		DpWindow = SDL_CreateWindow("Data Plot", 100, 200, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
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
				enum FontSize { FONT_6 = 0, FONT_7, FONT_8, FONT_9, FONT_10, FONT_11, FONT_12, FONT_13, 
								FONT_14, FONT_16, FONT_18, FONT_20, FONT_22, FONT_24, FONT_26, FONT_28
				};
				TTF_Font* DpFont[16];
				DpFont[FONT_6] = TTF_OpenFont("fonts/arial.ttf", 6); DpFont[FONT_7] = TTF_OpenFont("fonts/arial.ttf", 7);
				DpFont[FONT_8] = TTF_OpenFont("fonts/arial.ttf", 8); DpFont[FONT_9] = TTF_OpenFont("fonts/arial.ttf", 9);
				DpFont[FONT_10] = TTF_OpenFont("fonts/arial.ttf", 10); DpFont[FONT_11] = TTF_OpenFont("fonts/arial.ttf", 11);
				DpFont[FONT_12] = TTF_OpenFont("fonts/arial.ttf", 12); DpFont[FONT_13] = TTF_OpenFont("fonts/arial.ttf", 13);
				DpFont[FONT_14] = TTF_OpenFont("fonts/arial.ttf", 14); DpFont[FONT_16] = TTF_OpenFont("fonts/arial.ttf", 16);
				DpFont[FONT_18] = TTF_OpenFont("fonts/arial.ttf", 18); DpFont[FONT_20] = TTF_OpenFont("fonts/arial.ttf", 20);
				DpFont[FONT_22] = TTF_OpenFont("fonts/arial.ttf", 22); DpFont[FONT_24] = TTF_OpenFont("fonts/arial.ttf", 24);
				DpFont[FONT_26] = TTF_OpenFont("fonts/arial.ttf", 26); DpFont[FONT_28] = TTF_OpenFont("fonts/arial.ttf", 28);

				


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
	gTexture = loadTexture("paint.jpg");

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