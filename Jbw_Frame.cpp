#include "Jbw_Frame.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTORS:
------------------------------------------------------------------------------------------*/
Jbw_Frame::Jbw_Frame(Jbw_Handles* handles, int x, int y, int w, int h, bool DoFill)
{
	Jhandle = handles;
	FrameX = x;
	FrameY = y;
	FrameW = w;
	FrameH = h;
	Fill = DoFill;
	LineColor = J_C_Frame;
	CreatePts();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CreatePts
------------------------------------------------------------------------------------------*/
void Jbw_Frame::CreatePts()
{
	PolyLine = new SDL_Point[5];

	PolyLine[0].x = 0; 
	PolyLine[0].y = 0; 

	PolyLine[1].x =  FrameW - 1;
	PolyLine[1].y = 0; 

	PolyLine[2].x =  FrameW - 1;
	PolyLine[2].y = FrameH - 1;

	PolyLine[3].x = 0; 
	PolyLine[3].y = FrameH - 1;

	PolyLine[4].x = 0; 
	PolyLine[4].y = 0; 
}

/*---------------------------------------------------------------
FUNCTION: RdrFrame
---------------------------------------------------------------*/
void Jbw_Frame::RdrFrame(void)
{
	//  Set Viewport
	SDL_Rect Viewport = { FrameX, FrameY, FrameW, FrameH };
	SDL_RenderSetViewport(Jhandle->Rdr, &Viewport);

	SDL_SetRenderDrawColor(Jhandle->Rdr, LineColor.r, LineColor.g, LineColor.b, LineColor.a);
	SDL_RenderDrawLines(Jhandle->Rdr, PolyLine, 5);

	if (Fill == true) {

		SDL_Rect FillArea{ 1, 1, FrameW - 2, FrameH - 2 };

		SDL_SetRenderDrawColor(Jhandle->Rdr, FillColor.r, FillColor.g, FillColor.b, FillColor.a);
		SDL_RenderFillRect(Jhandle->Rdr, &FillArea);
	}
	SDL_RenderPresent(Jhandle->Rdr);
}