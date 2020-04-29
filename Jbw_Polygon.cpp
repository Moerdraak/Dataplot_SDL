#include "Jbw_Polygon.h"

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
Jbw_Polygon::Jbw_Polygon(SDL_Renderer* PRdr)
{
	Jrdr = PRdr;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Polygon::AddPoint(int x, int y)
{
    if (NumPoints == 0) {
       PolyLine = new SDL_Point;
    }
    else{
        SDL_Point *Tmp = new SDL_Point[NumPoints + 1];
        for (int I = 0; I < NumPoints; I++) {
            Tmp[I] = PolyLine[I];
        }
        delete PolyLine;
        PolyLine = Tmp;
    }
    PolyLine[NumPoints].x = x;
    PolyLine[NumPoints++].y = y;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Polygon::PolyRdr(void)
{
    SDL_SetRenderDrawColor(Jrdr, LineColor.r, LineColor.g, LineColor.b, LineColor.a);
    SDL_RenderDrawLines(Jrdr, PolyLine, NumPoints);
}