#include "Jbw_Circle.h"

Jbw_Circle::Jbw_Circle(Jbw_Handles* handles, int x, int y, int Radius)
{
    Jhandle = handles;
    CirX = x;
    CirY = y;
    CirRad = Radius;

}

/*-----------------------------------------------------------------------------------------
    FUNCTION: CircleOpen
------------------------------------------------------------------------------------------*/
void Jbw_Circle::CircleOpen()
{
    SDL_SetRenderDrawColor(Jhandle->Rdr, Border.r, Border.g, Border.b, Border.a);

    for (int X = 0; X < CirRad; X++)
    {
        int Y = (int)sqrt(CirRad * CirRad - X * X);

        SDL_RenderDrawPoint(Jhandle->Rdr, CirX + X, CirY + Y);
        SDL_RenderDrawPoint(Jhandle->Rdr, CirX - X, CirY + Y);
        SDL_RenderDrawPoint(Jhandle->Rdr, CirX + X, CirY - Y);
        SDL_RenderDrawPoint(Jhandle->Rdr, CirX - X, CirY - Y);
    }


    for (int Y = 0; Y < CirRad; Y++)
    {
        int X = (int)sqrt(CirRad * CirRad - Y * Y);

        SDL_RenderDrawPoint(Jhandle->Rdr, CirX + X, CirY + Y);
        SDL_RenderDrawPoint(Jhandle->Rdr, CirX  - X, CirY + Y);
        SDL_RenderDrawPoint(Jhandle->Rdr, CirX  + X, CirY - Y);
        SDL_RenderDrawPoint(Jhandle->Rdr, CirX - X, CirY - Y);
    }
}


/*-----------------------------------------------------------------------------------------
    FUNCTION: CircleFill
------------------------------------------------------------------------------------------*/
void Jbw_Circle::CircleFill()
{
    SDL_SetRenderDrawColor(Jhandle->Rdr, Fill.r, Fill.g, Fill.b, Fill.a);
    for (int w = 0; w < CirRad * 2; w++)
    {
        for (int h = 0; h < CirRad * 2; h++)
        {
            int dx = CirRad - w; // horizontal offset
            int dy = CirRad - h; // vertical offset
            if ((dx * dx + dy * dy) <= (CirRad * CirRad))
            {
                SDL_RenderDrawPoint(Jhandle->Rdr, CirX + dx, CirY + dy);
            }
        }
    }
}