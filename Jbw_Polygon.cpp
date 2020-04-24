#include "Jbw_Polygon.h"

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
Jbw_Polygon::Jbw_Polygon(SDL_Renderer* Rdr)
{
	Prdr = Rdr;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Polygon::AddPoint(int x, int y)
{
    if (NumPoints == 0) {
        Points = new SDL_Point;
    }
    else{
        SDL_Point *Tmp = new SDL_Point[NumPoints + 1];
        for (int I = 0; I < NumPoints; I++) {
            Tmp[I] = Points[I];
        }
        delete Points;
        Points = Tmp;
    }
    Points[NumPoints].x = x;
    Points[NumPoints++].y = y;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Polygon::PolyRdr(void)
{
    SDL_SetRenderDrawColor(Prdr, LineColor.r, LineColor.g, LineColor.b, LineColor.a);
    SDL_RenderDrawLines(Prdr, Points, NumPoints);
}