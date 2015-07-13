#include <SDL.h>
#include <iostream>
#undef main


int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
    {
	// TODO(hugo): We can't load SDL. There is an issue.
	return(0);
    }

    SDL_Window* window = SDL_CreateWindow("BRK",
					  SDL_WINDOWPOS_CENTERED,
					  SDL_WINDOWPOS_CENTERED,
					  500, 546, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
						SDL_RENDERER_ACCELERATED);

    SDL_Rect r;
    r.x = 50;
    r.y = 450;
    r.w = 100;
    r.h = 25;
    
    bool gameContinue = true;
    
    while(gameContinue)
	
    {
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
	    if(event.type == SDL_QUIT)
	    {
		gameContinue = false;
	    }
	    if(event.type == SDL_KEYDOWN)
	    {
		if(event.key.keysym.scancode == SDL_SCANCODE_LEFT)
		    r.x -= 4;
		if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		    r.x += 4;
	    }
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	    
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &r);
    
	SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return(0);
}
