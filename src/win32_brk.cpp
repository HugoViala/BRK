#include "win32_brk.h"

/*
  TODO(hugo):
  - Enforcing the frame rate (decide which frame rate to target)
  - Smooth the collision detection (use float for positioning ?)
  - Add a ball to play around with
  - Support Gamepad
 */


global_variable real32 GlobalPerfCountFrequency;


inline LARGE_INTEGER
Win32GetWallClock(void)
{
    LARGE_INTEGER Result;
    QueryPerformanceCounter(&Result);
    return(Result);
}

inline real32
Win32GetSecondsElapsed(LARGE_INTEGER Start, LARGE_INTEGER End)
{
    real32 Result = ((real32)(End.QuadPart - Start.QuadPart))/
	((real32)GlobalPerfCountFrequency);
    return(Result);
}

int main(int argc, char** argv)
{
    LARGE_INTEGER PerfCountFrequencyResult;
    QueryPerformanceFrequency(&PerfCountFrequencyResult);
    GlobalPerfCountFrequency = PerfCountFrequencyResult.QuadPart;

    // NOTE(hugo): Setting the sleep granularity of 1ms
    timeBeginPeriod(1);
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
    {
	// TODO(hugo): We can't load SDL. There is an issue.
	return(0);
    }

    const real32 FRAME_PER_SECOND = 30.0f;
    const real32 MS_PER_FRAME = 1000.0f / FRAME_PER_SECOND;
    
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

    LARGE_INTEGER LastFrameTime = Win32GetWallClock();
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

	LARGE_INTEGER CurrentFrameTime = Win32GetWallClock();
	real32 WorkSecondsElapsed = Win32GetSecondsElapsed(LastFrameTime, CurrentFrameTime);

	if(1000.0f * WorkSecondsElapsed < MS_PER_FRAME)
	{
	    DWORD SleepMS = (DWORD)(MS_PER_FRAME - 1000.0f * WorkSecondsElapsed);
	    if(SleepMS > 0)
	    {
		Sleep(SleepMS);
	    }
	}
	real32 SecondsElapsedForFrame = Win32GetSecondsElapsed(LastFrameTime,
							       Win32GetWallClock());

	while(1000.0f * SecondsElapsedForFrame < MS_PER_FRAME)
	{
	    SecondsElapsedForFrame = Win32GetSecondsElapsed(LastFrameTime,
							    Win32GetWallClock());
	}
	real32 MSElapsedForFrame = 1000.0f * Win32GetSecondsElapsed(LastFrameTime,
								    Win32GetWallClock()); 
	SDL_Log("%f", MSElapsedForFrame);
	LastFrameTime = Win32GetWallClock();
    }

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
    return(0);
}
