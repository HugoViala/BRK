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
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);;
    SDL_Surface* background = SDL_LoadBMP("../data/duck.bmp");
    
    SDL_RenderClear(renderer);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, background);
    if(texture)
	SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

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
	}
    }
    
    SDL_FreeSurface(background);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return(0);
}
