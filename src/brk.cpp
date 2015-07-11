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

    SDL_Window* window;
    SDL_Renderer* renderer;

    if(SDL_CreateWindowAndRenderer(512, 256, 0,
				   &window, &renderer) == -1)
    {
	// TODO(hugo): Error in creation
    }

    SDL_SetWindowTitle(window, "BRK");

    SDL_Surface* background = SDL_CreateRGBSurface(0, 512, 256,
						   32, 0, 0, 0, 0);


    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, background);
    if(texture)
	SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
		   
    SDL_Delay(2000);
    
    SDL_FreeSurface(background);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return(0);
}
