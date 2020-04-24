#include "Jbw_Frame.h"

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
Jbw_Frame::Jbw_Frame(SDL_Renderer* Rdr, int Xo, int Yo, int w, int h)
{
	CreateFrame(Rdr, Xo, Yo, w, h);
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Frame::CreateFrame(SDL_Renderer* Rdr, int Xo, int Yo, int w, int h)
{
	Prdr = Rdr;

	Points = new SDL_Point[5];

	Points[0].x = Xo;
	Points[0].y = Yo;

	Points[1].x = Xo + w;
	Points[1].y = Yo;

	Points[2].x = Xo + w;
	Points[2].y = Yo + h;

	Points[3].x = Xo;
	Points[3].y = Yo + h;

	Points[4].x = Xo;
	Points[4].y = Yo;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Frame::FrameRdr(void) {

	SDL_SetRenderDrawColor(Prdr, LineColor.r, LineColor.g, LineColor.b, LineColor.a);
	SDL_RenderDrawLines(Prdr, Points, 5);
}