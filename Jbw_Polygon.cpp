#include "Jbw_Polygon.h"

/*-----------------------------------------------------------------------------------------
    CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Polygon::Jbw_Polygon()
{

}

/*-----------------------------------------------------------------------------------------
    CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Polygon::Jbw_Polygon(Jbw_Handles* handles, int x, int y)
{
    Jhandle = handles;
    AddPoint(x, y);
}

/*-----------------------------------------------------------------------------------------
    DENSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Polygon::~Jbw_Polygon()
{
    delete[] PolyLine;
    PolyLine = NULL;
}

/*-----------------------------------------------------------------------------------------
    COPY CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Polygon::Jbw_Polygon(const Jbw_Polygon& cp) : Jbw_Base(cp)
{
    NumPoints = cp.NumPoints;
    LineColor = cp.LineColor;

    PolyLine = new SDL_Point[NumPoints];
    for (int I = 0; I < NumPoints; I++) {
        PolyLine[I] = cp.PolyLine[I];
    }
}

/*-----------------------------------------------------------------------------------------
    ASIGNMENT OPERATOR OVERLOAD
------------------------------------------------------------------------------------------*/
Jbw_Polygon& Jbw_Polygon::operator=(const Jbw_Polygon& cp)
{
    if (this != &cp) {
        NumPoints = cp.NumPoints;
        LineColor = cp.LineColor;

        delete PolyLine;
        PolyLine = new SDL_Point[NumPoints];
        for (int I = 0; I < NumPoints; I++) {
            PolyLine[I] = cp.PolyLine[I];
        }
    }
    return *this;
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
        delete[] PolyLine;
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
    //  Set Viewport
    SDL_Rect Viewport = { 0, 0, Jhandle->GuiArea.w, Jhandle->GuiArea.h };
    SDL_RenderSetViewport(Jhandle->Rdr, &Viewport);

    SDL_SetRenderDrawColor(Jhandle->Rdr, LineColor.r, LineColor.g, LineColor.b, LineColor.a);
    SDL_RenderDrawLines(Jhandle->Rdr, PolyLine, NumPoints);
    SDL_RenderPresent(Jhandle->Rdr);
}