#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Jbw_EditBox.h"
#include "data.h"
#include "fft.h"

/**************************************************************************************
	CLASS: Graph
	=============
	This is
**************************************************************************************/
class Dataplot; // Forward Declaration

class DpGraph {
private:

public:

	TData* BaseData = NULL;
	TData *FreqData = NULL;



	const Dataplot* Dp;

	// BASE OBJECTS
	SDL_Window* GraphWindow = NULL; // The window we'll be rendering to DOESN'T BELONG HERE MUST BE CREATED ON THE FLY
	SDL_Surface* wSurf = NULL; // The surface contained by the window
	SDL_Renderer* GRender = NULL; // The User window renderer

	// RECTANGLE OBJECTS
	SDL_Rect vp_Graph;
	SDL_Rect vp_Main; // For clearing the Thing  // TMP !!!!!!
	SDL_Rect GraphArea;
	SDL_Rect LegendArea;


	// TEXT OBJECTS
	Jbw_EditBox* txtGraphTitle;
	Jbw_EditBox* txtTestTitle;
	Jbw_EditBox* txtLegend;
	Jbw_EditBox* txtXlabel;
	Jbw_EditBox* txtYlabel;
	Jbw_EditBox* txtRandom;

	// EDITBOX OBJECTS



	// BUTTONS

	const int G_SCREEN_W = 900;
	const int G_SCREEN_H = 600;
	const int GRAPH_W = 700;
	const int GRAPH_H = 500;

	/*******************  CONSTRUCTORS  *******************/
	DpGraph(const Dataplot* Dp);
	~DpGraph();

	DpGraph* Next;
	DpGraph* Prev;

	/*******************  FUNCTIONS  *******************/

	void GraphRender(int Config);
};

