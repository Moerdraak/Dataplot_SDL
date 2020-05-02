#include "Jbw_Frame.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTORS:
------------------------------------------------------------------------------------------*/
Jbw_Frame::Jbw_Frame(SDL_Renderer* Rdr, int Xo, int Yo, int Width, int Height, bool DoFill)
{
	J_Properties P;
	P.Rdr = Rdr;
	P.x = Xo;
	P.y = Yo;
	P.w = Width;
	P.h = Height;
	Fill = DoFill;
	LineColor = J_C_Frame;
	InitFrame(&P);
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Frame::InitFrame(J_Properties* Prop) {
	Jrdr = Prop->Rdr;
	FrameX = Prop->x;
	FrameY = Prop->y;
	FrameW = Prop->w;
	FrameH = Prop->h;
	CreatePts();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CreatePts
------------------------------------------------------------------------------------------*/
void Jbw_Frame::CreatePts()
{
	PolyLine = new SDL_Point[5];

	PolyLine[0].x = 0; // FrameX;
	PolyLine[0].y = 0; // FrameY;

	PolyLine[1].x = /*FrameX +*/ FrameW - 1;
	PolyLine[1].y = 0; // FrameY;

	PolyLine[2].x = /*FrameX +*/ FrameW - 1;
	PolyLine[2].y = /*FrameY +*/ FrameH - 1;

	PolyLine[3].x = 0; // FrameX;
	PolyLine[3].y = /*FrameY +*/ FrameH - 1;

	PolyLine[4].x = 0; // FrameX;
	PolyLine[4].y = 0; // FrameY;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Frame::RdrFrame(void)
{
	//  Set Viewport
	SDL_Rect Viewport = { FrameX, FrameY, FrameW, FrameH };
	SDL_RenderSetViewport(Jrdr, &Viewport);

	SDL_SetRenderDrawColor(Jrdr, LineColor.r, LineColor.g, LineColor.b, LineColor.a);
	SDL_RenderDrawLines(Jrdr, PolyLine, 5);

	if (Fill == true) {

		SDL_Rect FillArea{ 1, 1, FrameW - 2, FrameH - 2 };

		SDL_SetRenderDrawColor(Jrdr, FillColor.r, FillColor.g, FillColor.b, FillColor.a);
		SDL_RenderFillRect(Jrdr, &FillArea);
	}
	SDL_RenderPresent(Jrdr);// Render to screen
}