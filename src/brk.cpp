#include <SDL.h>

#undef main


int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
    {
	// TODO(hugo): We can't load SDL. There is an issue.
	return(0);
    }

    SDL_Window* window = SDL_CreateWindow("BRK",
					  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					  256, 512, SDL_WINDOW_SHOWN);
    if(window)
    {
	SDL_Delay(3000);
	SDL_DestroyWindow(window);
    }
    else
    {
    }
   

    SDL_Quit();
    return(0);
}
