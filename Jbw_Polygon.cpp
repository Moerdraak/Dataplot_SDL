#include "Jbw_Polygon.h"

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
Jbw_Polygon::Jbw_Polygon(Jbw_Handles* handles)
{
    Jhandle = handles;
}

/*---------------------------------------------------------------
FUNCTION: AddPoint
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
FUNCTION: RdrPoly
---------------------------------------------------------------*/
void Jbw_Polygon::RdrPoly(void)
{
    SDL_SetRenderDrawColor(Jhandle->Rdr, LineColor.r, LineColor.g, LineColor.b, LineColor.a);
    SDL_RenderDrawLines(Jhandle->Rdr, PolyLine, NumPoints);
}