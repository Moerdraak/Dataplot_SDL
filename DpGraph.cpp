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
DpGraph::DpGraph(const Dataplot* PtrDp) {

	Dp = PtrDp;

	// Create Graph window
	GraphWindow = SDL_CreateWindow("Data Plot", 500, 300, G_SCREEN_W, G_SCREEN_H, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	// Create renderer for Graph window
	GRender = SDL_CreateRenderer(GraphWindow, -1, SDL_RENDERER_ACCELERATED);
	// Initialize True Type Fonts
	TTF_Init();

	// Set up Screen Area

	/* TEXT: Test Title */
	//txtTestTitle = new Jbw_EditBox(GRender, J_TEXT, 75, 8, GRAPH_W, 15);
	//txtTestTitle->Set("Test Title", "TxtSize", 12, "Align", J_CENTRE);

	///* TEXT: Graph Title */
	//txtGraphTitle = new Jbw_EditBox(GRender, J_TEXT, 75, 24, GRAPH_W, 15);
	//txtGraphTitle->Set("Graph Title", "TxtSize", 12, "Align", J_CENTRE);

	///* TEXT: Legend */
	//txtLegend = new Jbw_EditBox(GRender, J_TEXT, G_SCREEN_W - 115, 40, 100);
	//txtLegend->Set("LEGEND", "TxtSize", 12, "Align", J_CENTRE);

	///* TEXT: X Label */
	//txtXlabel = new Jbw_EditBox(GRender, J_TEXT, 75, 570, GRAPH_W, 16); // Create Edit box
	//txtXlabel->Set("X-Axes Label", "TxtSize", 12, "Align", J_CENTRE);

	///* TEXT: Y Label */
	//txtYlabel = new Jbw_EditBox(GRender, J_TEXT, 10, 40, GRAPH_H, 15); // Create Edit box
	//txtYlabel->Set("Y-Axes Label", "TxtSize", 12, "Align", J_CENTRE, "Angle", -90);

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

	txtRandom = new Jbw_EditBox(GRender, J_TEXT, 0, 0, 10);

	//Legend Area
	//	SDL_Rect LegendArea;
	LegendArea.x = G_SCREEN_W - 115;
	LegendArea.y = 40;
	LegendArea.w = 100;
	LegendArea.h = 100;






	/**************       Do MYSTUFFS      *******************/
	BaseData = new TData("Data.txt"); // Read in data from a txt file
	FreqData = new TData;
	Time2Freq(BaseData, FreqData);// Call the function that converts time based data to Frequency domain



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
	SDL_SetRenderDrawColor(GRender, 230, 230, 230, 255); // This sets the color you clear the screen to ( see below )
	SDL_RenderClear(GRender); // This clears the rendering target with the draw color set above
	SDL_RenderPresent(GRender);

	/****    SET VIEWPORT TO MAIN SCREEN     ****/
	SDL_RenderSetViewport(GRender, &vp_Main);

	// Render Legend 
	SDL_SetRenderDrawColor(GRender, 255, 255, 255, 255);
	SDL_RenderFillRect(GRender, &LegendArea);

	txtLegend->Render();
//	txtGraphTitle->Set("Cannon Vibration");	txtGraphTitle->Render();
//	txtTestTitle->Set(Dp->edDataSet->Text); txtTestTitle->Render();
//	txtXlabel->Set(Dp->edXaxLabel->Text); txtXlabel->Render();
//	txtYlabel->Set("Vibration (g)"); txtYlabel->Render();

	double xxx = 453656.34;
	// X Values
	string MaxNum;
	MaxNum.assign(to_string(int(xxx)));

	int N;
	if (xxx < 10000) {
		for (int I = 0; I <= 10; I++) {
			sprintf_s(TmpTxt, "%0.2f", I * (xxx / 10));
//			txtRandom->Set(TmpTxt, "x", 50 + I * (GRAPH_W / 10), "y", 544, "TxtSize", 10, "w", 50, "h", 10, "Align", J_CENTRE);
			txtRandom->Render();
		}
	}
	else {
		N = (int)MaxNum.length() - 4;
		for (int I = 0; I <= 10; I++) {
			sprintf_s(TmpTxt, "%0.2f", I * ((xxx / pow(10, N)) / 10));
//			txtRandom->Set(TmpTxt, "x", 50 + I * (GRAPH_W / 10), "y", 545, "TxtSize", 10, "w", 50, "h", 10, "Align", J_CENTRE);
			txtRandom->Render();
		}

//		txtRandom->Set("x 10", "x", 800, "y", 527, "TxtSize", 12, "w", 30, "h", 14, "Align", J_RIGHT);
		txtRandom->Render();
		sprintf_s(TmpTxt, "%d", N);
//		txtRandom->Set(TmpTxt, "x", 831, "y", 520, "TxtSize", 10, "w", 30, "h", 10, "Align", J_LEFT);
		txtRandom->Render();
	}

	// Y Values
	MaxNum.assign(to_string(int(xxx)));

	if (xxx < 10000) {
		for (int I = 10; I >= 0; I--) {
			sprintf_s(TmpTxt, "%0.2f", I * (xxx / 10));
//			txtRandom->Set(TmpTxt, "x", 28, "y", 534 - I * (GRAPH_H / 10), "TxtSize", 10, "w", 50, "h", 10, "Align", J_CENTRE);
			txtRandom->Render();
		}
	}
	else {
		N = (int)MaxNum.length() - 4;
		for (int I = 10; I >= 0; I--) {
			sprintf_s(TmpTxt, "%0.2f", I * ((xxx / pow(10, N)) / 10));
	//		txtRandom->Set(TmpTxt, "x", 28, "y", 534 - I * (GRAPH_H / 10), "TxtSize", 10, "w", 50, "h", 10, "Align", J_CENTRE);
			txtRandom->Render();
		}

//		txtRandom->Set("x 10", "x", 32, "y", 15, "TxtSize", 12, "w", 30, "h", 14, "Align", J_RIGHT);
		txtRandom->Render();
		sprintf_s(TmpTxt, "%d", N);
//		txtRandom->Set(TmpTxt, "x", 63, "y", 8, "TxtSize", 10, "w", 30, "h", 10, "Align", J_LEFT);
		txtRandom->Render();
	}
	//	SDL_RenderPresent(GRender);

		/****    SET VIEWPORT TO GRAPH AREA     ****/
	SDL_RenderSetViewport(GRender, &vp_Graph);
	SDL_SetRenderDrawColor(GRender, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(GRender, &GraphArea); // Clear Graph

	// Draw X & Y Ticks
	SDL_SetRenderDrawColor(GRender, 0, 0, 0, 255);

	SDL_RenderDrawLine(GRender, 0, 0, 0, GRAPH_H);
	for (int I = 0; I < 10; I++) {
		SDL_RenderDrawLine(GRender, 0, I * (int)round(GRAPH_H / 10), 5, I * (int)round(GRAPH_H / 10));
	}

	SDL_RenderDrawLine(GRender, 0, GRAPH_H - 1, GRAPH_W, GRAPH_H - 1);
	for (int I = 0; I < 10; I++) {
		SDL_RenderDrawLine(GRender, I * (int)round(GRAPH_W / 10), GRAPH_H - 1, I * (int)round(GRAPH_W / 10), GRAPH_H - 6);
	}
	SDL_RenderDrawLine(GRender, 10 * (int)round(GRAPH_W / 10) - 1, GRAPH_H - 1, 10 * (int)round(GRAPH_W / 10) - 1, GRAPH_H - 6);

	// Plot Graphs
	SDL_SetRenderDrawColor(GRender, 255, 0, 0, 255);
	SDL_RenderDrawLines(GRender, TmpPoints, 1000);
	delete TmpPoints;
	SDL_RenderPresent(GRender);
}