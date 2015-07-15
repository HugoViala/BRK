#include "brk.h"


void
GameUpdateAndRender(SDL_Renderer* Renderer, game_input* Input, SDL_Rect* Paddle)
{

    if(Input->MoveLeft)
    {
	Paddle->x -= 5;
    }
    if(Input->MoveRight)
    {
	Paddle->x += 5;
    }
    
    SDL_SetRenderDrawColor(Renderer, 128, 128, 128, 255);	    
    SDL_RenderClear(Renderer);	
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(Renderer, Paddle);
    SDL_RenderPresent(Renderer);
}
