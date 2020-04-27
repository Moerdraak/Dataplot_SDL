#include "Jbw_Circle.h"

Jbw_Circle::Jbw_Circle(SDL_Renderer* Rdr, int x, int y, int Radius)
{
    Crdr = Rdr;
    CirX = x;
    CirY = y;
    CirRad = Radius;

}
void Jbw_Circle::CircleOpen()
{
    SDL_SetRenderDrawColor(Crdr, Border.r, Border.g, Border.b, Border.a);

    for (int X = 0; X < CirRad; X++)
    {
        int Y = sqrt(CirRad * CirRad - X * X);

        SDL_RenderDrawPoint(Crdr, CirX + X, CirY + Y);
        SDL_RenderDrawPoint(Crdr, CirX - X, CirY + Y);
        SDL_RenderDrawPoint(Crdr, CirX + X, CirY - Y);
        SDL_RenderDrawPoint(Crdr, CirX - X, CirY - Y);
    }


    for (int Y = 0; Y < CirRad; Y++)
    {
        int X = sqrt(CirRad * CirRad - Y * Y);

        SDL_RenderDrawPoint(Crdr, CirX + X, CirY + Y);
        SDL_RenderDrawPoint(Crdr, CirX  - X, CirY + Y);
        SDL_RenderDrawPoint(Crdr, CirX  + X, CirY - Y);
        SDL_RenderDrawPoint(Crdr, CirX - X, CirY - Y);
    }
}

void Jbw_Circle::CircleFill()
{
    SDL_SetRenderDrawColor(Crdr, Fill.r, Fill.g, Fill.b, Fill.a);
    for (int w = 0; w < CirRad * 2; w++)
    {
        for (int h = 0; h < CirRad * 2; h++)
        {
            int dx = CirRad - w; // horizontal offset
            int dy = CirRad - h; // vertical offset
            if ((dx * dx + dy * dy) <= (CirRad * CirRad))
            {
                SDL_RenderDrawPoint(Crdr, CirX + dx, CirY + dy);
            }
        }
    }
}