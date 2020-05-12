#include "DpGraph.h"
#include "Dataplot.h"
/**************************************************************************************
	CLASS: Graph
	=============
	This is
**************************************************************************************/

DpGraph::~DpGraph() {

	//Destroy window
	SDL_DestroyRenderer(GRender);
	SDL_DestroyWindow(GraphWindow);

	GraphWindow = NULL;
	GRender = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   GRAPH WINDOW CONSTRUCTOR
//////////////////////////////////////////////////////////////////////////////////////////////////////////
DpGraph::DpGraph(Jbw_Handles* h) {

	ghandles = new Jbw_Handles;

	// Create Graph window
	ghandles->JbwGui = SDL_CreateWindow("Data Plot", 500, 300, G_SCREEN_W, G_SCREEN_H, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	// Create renderer for Graph window
	ghandles->Rdr = SDL_CreateRenderer(GraphWindow, -1, SDL_RENDERER_ACCELERATED);
	// Initialize True Type Fonts
	TTF_Init();

	

	// Set up Screen Area

	/* TEXT: Test Title */
	txtTestTitle = new Jbw_TextBox(ghandles, "Test Title", 75, 8, GRAPH_W, 15, 12);
	txtTestTitle->Align = J_CENTRE;

	///* TEXT: Graph Title */
	txtGraphTitle = new Jbw_TextBox(ghandles, "Graph Title", 75, 24, GRAPH_W, 15, 12);
	txtGraphTitle->Align = J_CENTRE;

	///* TEXT: Legend */
	txtLegend = new Jbw_TextBox(ghandles, "LEGEND", G_SCREEN_W - 115, 40, 100, 15, 12);
	txtLegend->Align = J_CENTRE;

	///* TEXT: X Label */
	ObjXlabel = new Jbw_TextBox(ghandles, "X-Axes Label", 75, 570, GRAPH_W, 16, 12);
	ObjXlabel->Align = J_CENTRE;

	///* TEXT: Y Label */
	ObjYlabel = new Jbw_TextBox(ghandles, "Y-Axes Label", 10, 40, GRAPH_H, 16, 12);
	ObjYlabel->Align = J_CENTRE;
	ObjYlabel->Angle = -90;

	/*      Graphics Area      */
	//	SDL_Rect vp_Graph;
	vp_Graph.x = 75;
	vp_Graph.y = 40;
	vp_Graph.w = GRAPH_W;
	vp_Graph.h = GRAPH_H;

	vp_Main.x = 0;
	vp_Main.y = 0;
	vp_Main.w = G_SCREEN_W;
	vp_Main.h = G_SCREEN_H;

	// Graphics Inside Area
	GraphArea.x = 0;
	GraphArea.y = 0;
	GraphArea.w = GRAPH_W;
	GraphArea.h = GRAPH_H;

	txtRandom = new Jbw_EditBox(ghandles, J_TXT, 0, 0, 10);

	//Legend Area
	//	SDL_Rect LegendArea;
	LegendArea.x = G_SCREEN_W - 115;
	LegendArea.y = 40;
	LegendArea.w = 100;
	LegendArea.h = 100;

	/**************       Do MYSTUFFS      **************/
//	std::string aa = GetS(handles, "edXaxLabel", "Text" );

	Jbw_EditBox* Tmp = static_cast<Jbw_EditBox *>(h->Jbw_Obj[2]);
	BaseData = new TData(Tmp->Text); // Read in data from a txt file
	FreqData = new TData;
	Time2Freq(BaseData, FreqData);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//   PERFORM ALL RENEDERING TASKS
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void DpGraph::GraphRender(int Config)
{
	SDL_Point* TmpPoints;

	if (Config == 1) {
		TmpPoints = new SDL_Point[1000];// = { {0, 0}, {20, 140}, {40, 10}, {60, 80} };

		double FactorX = GRAPH_W / BaseData->Xval[999];
		double FactorY = (double)GRAPH_H * 0.01;
		for (int I = 0; I < 1000; I++) {
			TmpPoints[I].x = (int)round(BaseData->Xval[I] * FactorX);
			TmpPoints[I].y = 300 + (int)round(BaseData->Yval[I] * FactorY); //+ SCREEN_HEIGHT;
			int x = 0;
		}
	}
	else if (Config == 2){
		TmpPoints = new SDL_Point[500];// = { {0, 0}, {20, 140}, {40, 10}, {60, 80} };

		double FactorX = GRAPH_W / BaseData->Xval[499];
		double FactorY = (double)GRAPH_H * 0.02;
		for (int I = 0; I < 500; I++) {
			TmpPoints[I].x = (int)round(BaseData->Xval[I] * FactorX);
			TmpPoints[I].y = 300 + (int)round(BaseData->Yval[I] * FactorY); //+ SCREEN_HEIGHT;
			int x = 0;
		}
	}
	else {
		TmpPoints = new SDL_Point[1000];// = { {0, 0}, {20, 140}, {40, 10}, {60, 80} };

		double FactorX = GRAPH_W / FreqData->Xval[999];
		double FactorY = (double)GRAPH_H * 2;
		for (int I = 0; I < 1000; I++) {
			TmpPoints[I].x = (int)round(FreqData->Xval[I] * FactorX);
			TmpPoints[I].y = 300 + (int)round(FreqData->Yval[I] * FactorY); //+ SCREEN_HEIGHT;
			int x = 0;
		}
	}

	char TmpTxt[50];
	//Clear screen
	SDL_SetRenderDrawColor(ghandles->Rdr, 230, 230, 230, 255); // This sets the color you clear the screen to ( see below )
	SDL_RenderClear(ghandles->Rdr); // This clears the rendering target with the draw color set above
	SDL_RenderPresent(GRender);

	/****    SET VIEWPORT TO MAIN SCREEN     ****/
	SDL_RenderSetViewport(ghandles->Rdr, &vp_Main);

	// Render Legend 
	SDL_SetRenderDrawColor(ghandles->Rdr, 255, 255, 255, 255);
	SDL_RenderFillRect(ghandles->Rdr, &LegendArea);

	txtTestTitle->RdrTbx();
	txtGraphTitle->RdrTbx();
	txtLegend->RdrTbx();
	ObjXlabel->RdrTbx();
	ObjYlabel->RdrTbx();


	double xxx = 453656.34;
	// X Values
	string MaxNum;
	MaxNum.assign(to_string(int(xxx)));

	int N;
	if (xxx < 10000) {
		for (int I = 0; I <= 10; I++) {
			sprintf_s(TmpTxt, "%0.2f", I * (xxx / 10));
//			txtRandom->Set(TmpTxt, "x", 50 + I * (GRAPH_W / 10), "y", 544, "TxtSize", 10, "w", 50, "h", 10, "Align", J_CENTRE);
			txtRandom->InitTbx(ghandles, TmpTxt, 50 + I * (GRAPH_W / 10), 545, 10, 50, 10);
			txtRandom->Align = J_CENTRE;
			txtRandom->RdrTbx();

		}
	}
	else {
		N = (int)MaxNum.length() - 4;
		for (int I = 0; I <= 10; I++) {
			sprintf_s(TmpTxt, "%0.2f", I * ((xxx / pow(10, N)) / 10));
			txtRandom->InitTbx(ghandles, TmpTxt, 50 + I * (GRAPH_W / 10), 545, 50, 15, 10);
			txtRandom->Align = J_CENTRE;
			txtRandom->RdrTbx();
		}

		txtRandom->InitTbx(ghandles, "x 10", 800, 527, 30, 14, 12);
		txtRandom->Align = J_RIGHT;
		txtRandom->RdrTbx();

		sprintf_s(TmpTxt, "%d", N);
		txtRandom->InitTbx(ghandles, TmpTxt, 831, 520, 30, 15, 10);
		txtRandom->Align = J_LEFT;
		txtRandom->RdrTbx();
	}

	// Y Values
	MaxNum.assign(to_string(int(xxx)));

	if (xxx < 10000) {
		for (int I = 10; I >= 0; I--) {
			sprintf_s(TmpTxt, "%0.2f", I * (xxx / 10));
			txtRandom->InitTbx(ghandles, TmpTxt, 28, 534 - I * (GRAPH_H / 10), 50, 10, 10);
			txtRandom->Align = J_CENTRE;
			txtRandom->Angle = -90;
			txtRandom->RdrTbx();
		}
	}
	else {
		N = (int)MaxNum.length() - 4;
		for (int I = 10; I >= 0; I--) {
			sprintf_s(TmpTxt, "%0.2f", I * ((xxx / pow(10, N)) / 10));
			txtRandom->InitTbx(ghandles, TmpTxt, 28, 534 - I * (GRAPH_H / 10), 50, 15, 10);
			txtRandom->Align = J_CENTRE;
			txtRandom->RdrTbx();
		}

		txtRandom->InitTbx(ghandles, "x 10", 32, 15, 30, 14, 12);
		txtRandom->Align = J_RIGHT;
		txtRandom->RdrTbx();

		sprintf_s(TmpTxt, "%d", N);
		txtRandom->InitTbx(ghandles, TmpTxt, 63, 8, 30, 14, 10);
		txtRandom->Align = J_LEFT;
		txtRandom->RdrTbx();
	}
	//	SDL_RenderPresent(GRender);

		/****    SET VIEWPORT TO GRAPH AREA     ****/
	SDL_RenderSetViewport(GRender, &vp_Graph);
	SDL_SetRenderDrawColor(GRender, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(GRender, &GraphArea); // Clear Graph

	// Draw X & Y Ticks
	SDL_SetRenderDrawColor(ghandles->Rdr, 0, 0, 0, 255);

	SDL_RenderDrawLine(GRender, 0, 0, 0, GRAPH_H);
	for (int I = 0; I < 10; I++) {
		SDL_RenderDrawLine(ghandles->Rdr, 0, I * (int)round(GRAPH_H / 10), 5, I * (int)round(GRAPH_H / 10));
	}

	SDL_RenderDrawLine(GRender, 0, GRAPH_H - 1, GRAPH_W, GRAPH_H - 1);
	for (int I = 0; I < 10; I++) {
		SDL_RenderDrawLine(ghandles->Rdr, I * (int)round(GRAPH_W / 10), GRAPH_H - 1, I * (int)round(GRAPH_W / 10), GRAPH_H - 6);
	}
	SDL_RenderDrawLine(ghandles->Rdr, 10 * (int)round(GRAPH_W / 10) - 1, GRAPH_H - 1, 10 * (int)round(GRAPH_W / 10) - 1, GRAPH_H - 6);

	// Plot Graphs
	SDL_SetRenderDrawColor(ghandles->Rdr, 255, 0, 0, 255);
	SDL_RenderDrawLines(ghandles->Rdr, TmpPoints, 1000);
	delete TmpPoints;
	SDL_RenderPresent(ghandles->Rdr);
}