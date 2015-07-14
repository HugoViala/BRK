#include <SDL.h>

#undef main

/*
  TODO(hugo):
  - Enforcing the frame rate (decide which frame rate to target)
  - Smooth the collision detection (use float for positioning ?)
  - Add a ball to play around with
  - Support Gamepad
 */


int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
    {
	// TODO(hugo): We can't load SDL. There is an issue.
	return(0);
    }

    const float FRAME_PER_SECOND = 30.0f;
    const float MS_PER_FRAME = 1000.0f / FRAME_PER_SECOND;
    
    int WindowWidth = 500;
    int WindowHeight = 546;
    SDL_Window* Window = SDL_CreateWindow("BRK",
					  SDL_WINDOWPOS_CENTERED,
					  SDL_WINDOWPOS_CENTERED,
					  WindowWidth, WindowHeight, 0);
    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, -1,
						SDL_RENDERER_ACCELERATED);

    SDL_Rect Paddle;
    Paddle.x = 50;
    Paddle.y = 450;
    Paddle.w = 100;
    Paddle.h = 25;
    
    bool Running = true;

    Uint64 TimeCount = 0;
    Uint64 FrameCount = 0;
    
    Uint32 LastFrameTime = SDL_GetTicks();
    while(Running)	
    {
	SDL_Event Event;
	const Uint8* KeyboardState = SDL_GetKeyboardState(0);
	while(SDL_PollEvent(&Event))
	{
	    if(Event.type == SDL_QUIT)
	    {
		Running = false;
	    }
	}

	// NOTE(hugo): Keyboard events handling
	if(KeyboardState[SDL_SCANCODE_RIGHT])
	{
	    if(Paddle.x + Paddle.w + 1 <= WindowWidth)
		Paddle.x += 5;	    
	}
	if(KeyboardState[SDL_SCANCODE_LEFT])
	{
	    if(Paddle.x - 1 >= 0)
		Paddle.x -= 5;	    
	}

	
	SDL_SetRenderDrawColor(Renderer, 128, 128, 128, 255);	    
	SDL_RenderClear(Renderer);	
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(Renderer, &Paddle);
	SDL_RenderPresent(Renderer);

	Uint32 CurrentFrameTime = SDL_GetTicks();

	if(CurrentFrameTime - LastFrameTime < MS_PER_FRAME)
	{
	    SDL_Delay(MS_PER_FRAME - CurrentFrameTime + LastFrameTime);
	}
	LastFrameTime = CurrentFrameTime;
    }

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
    return(0);
}
