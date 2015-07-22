#include "brk.h"
#include "win32_brk.h"

/*
  TODO(hugo):
  - Creating Debug Precompile instructions
  - Smooth the collision detection (use float for positioning ?)
  - Add a ball to play around with
  - Support Gamepad
 */


global_variable LONGLONG GlobalPerfCountFrequency;


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

    // NOTE(hugo): Window and Renderer creation
    int WindowWidth = 500;
    int WindowHeight = 546;
    SDL_Window* Window = SDL_CreateWindow("BRK",
					  SDL_WINDOWPOS_CENTERED,
					  SDL_WINDOWPOS_CENTERED,
					  WindowWidth, WindowHeight, 0);
    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, -1,
						SDL_RENDERER_ACCELERATED);

    bool Running = true;
    game_state GameState = {};
    GameState.Width = WindowWidth;
    GameState.Height = WindowHeight;
    game_paddle Paddle = {};
    Paddle.Width = 100;
    Paddle.Height = 25;
    Paddle.BottomLeftPos = {};
    Paddle.BottomLeftPos.X = 160;
    Paddle.BottomLeftPos.Y = 60;
    GameState.Paddle = Paddle;
    
    
    LARGE_INTEGER LastFrameTime = Win32GetWallClock();
    while(Running)	
    {
	// TODO(hugo): Should we create a game_input each frame ?
	game_input Input = {};
	Input.MoveLeft = false;
	Input.MoveRight = false;
	Input.ActionUp = false;

	
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
	    Input.MoveRight = true;
	}
	if(KeyboardState[SDL_SCANCODE_LEFT])
	{
	    Input.MoveLeft = true;
	}


	GameUpdateAndRender(Renderer, &Input, &GameState);
	
	// -------------------------------------
	//
	// NOTE(hugo): Frame Rate Enforcing part
	//
	// -------------------------------------

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
#if 0
	// NOTE(hugo): Debug Log for Frame Rate
	SDL_Log("%f", MSElapsedForFrame);
#endif
	LastFrameTime = Win32GetWallClock();
    }

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
    return(0);
}
