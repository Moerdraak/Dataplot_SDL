#include "Jbw_Frame.h"

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
Jbw_Frame::Jbw_Frame(SDL_Renderer* Rdr, int Xo, int Yo, int Width, int Height)
{
	CreateFrame(Rdr, Xo, Yo, Width, Height);
}

/*---------------------------------------------------------------
FUNCTION: Create the PolyLine that renders a Frame
---------------------------------------------------------------*/
void Jbw_Frame::SetFrame()
{
	PolyLine = new SDL_Point[5];

	PolyLine[0].x = FrameX;
	PolyLine[0].y = FrameY;

	PolyLine[1].x = FrameX + FrameW - 1;
	PolyLine[1].y = FrameY;

	PolyLine[2].x = FrameX + FrameW - 1;
	PolyLine[2].y = FrameY + FrameH - 1;

	PolyLine[3].x = FrameX;
	PolyLine[3].y = FrameY + FrameH - 1;

	PolyLine[4].x = FrameX;
	PolyLine[4].y = FrameY;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Frame::CreateFrame(SDL_Renderer* Rdr, int Xo, int Yo, int Width, int Height) {
	Prdr = Rdr;
	FrameX = Xo;
	FrameY = Yo;
	FrameW = Width;
	FrameH = Height;
	SetFrame();
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Frame::FrameRdr(void) {

	SDL_SetRenderDrawColor(Prdr, LineColor.r, LineColor.g, LineColor.b, LineColor.a);
	SDL_RenderDrawLines(Prdr, PolyLine, 5);
}