#include "Jbw_Circle.h"

Jbw_Circle::Jbw_Circle(SDL_Renderer* Rdr, int x, int y, int Radius)
{
    Jrdr = Rdr;
    CirX = x;
    CirY = y;
    CirRad = Radius;

}
void Jbw_Circle::CircleOpen()
{
    SDL_SetRenderDrawColor(Jrdr, Border.r, Border.g, Border.b, Border.a);

    for (int X = 0; X < CirRad; X++)
    {
        int Y = sqrt(CirRad * CirRad - X * X);

        SDL_RenderDrawPoint(Jrdr, CirX + X, CirY + Y);
        SDL_RenderDrawPoint(Jrdr, CirX - X, CirY + Y);
        SDL_RenderDrawPoint(Jrdr, CirX + X, CirY - Y);
        SDL_RenderDrawPoint(Jrdr, CirX - X, CirY - Y);
    }


    for (int Y = 0; Y < CirRad; Y++)
    {
        int X = sqrt(CirRad * CirRad - Y * Y);

        SDL_RenderDrawPoint(Jrdr, CirX + X, CirY + Y);
        SDL_RenderDrawPoint(Jrdr, CirX  - X, CirY + Y);
        SDL_RenderDrawPoint(Jrdr, CirX  + X, CirY - Y);
        SDL_RenderDrawPoint(Jrdr, CirX - X, CirY - Y);
    }
}

void Jbw_Circle::CircleFill()
{
    SDL_SetRenderDrawColor(Jrdr, Fill.r, Fill.g, Fill.b, Fill.a);
    for (int w = 0; w < CirRad * 2; w++)
    {
        for (int h = 0; h < CirRad * 2; h++)
        {
            int dx = CirRad - w; // horizontal offset
            int dy = CirRad - h; // vertical offset
            if ((dx * dx + dy * dy) <= (CirRad * CirRad))
            {
                SDL_RenderDrawPoint(Jrdr, CirX + dx, CirY + dy);
            }
        }
    }
}