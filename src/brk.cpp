#include "brk.h"

/*
 * TODO(hugo)
 *  - cleaning things up in different file
 *  - add blocks !!!
 *  - loading BMP
 *  - do art assets for the paddle and the ball
 *  - improve paddle collision (smoother)
 *  - debug collision case to see if it is pixel-right
 *  - fix the bug when you collide the ball with the paddle on the side
 *  - put the ball 
 */

vector2 operator+(vector2 A, vector2 B)
{
    vector2 Result = {};
    Result.X = A.X + B.X;
    Result.Y = A.Y + B.Y;
    return(Result);
}


// NOTE(hugo): This function draws a rectangle in
// math canonical coordinates
void
DrawRectangle(SDL_Renderer *Renderer, int x, int y, int w, int h,
	      Uint8 r, Uint8 g, Uint8 b)
{
    int WindowWidth;
    int WindowHeight;
    SDL_GetRendererOutputSize(Renderer,
			      &WindowWidth, &WindowHeight);

    SDL_Rect DrawingRect = {};
    DrawingRect.x = x;
    DrawingRect.y = WindowHeight - y - h;
    DrawingRect.w = w;
    DrawingRect.h = h;

    SDL_SetRenderDrawColor(Renderer, r, g, b, 255);
    SDL_RenderFillRect(Renderer, &DrawingRect);
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

}


void
DrawRectangle(SDL_Renderer* Renderer, vector2 P,
	      int w, int h, Uint8 r, Uint8 g, Uint8 b)
{
    DrawRectangle(Renderer,
		  (int) P.X, (int) P.Y, w, h, r, g, b);
}
void
DrawRectangle(SDL_Renderer *Renderer,
	      game_rect *Rect, Uint8 r, Uint8 g, Uint8 b)
{
    DrawRectangle(Renderer,
		  (int) Rect->Pos.X,
		  (int) Rect->Pos.Y,
		  (int) Rect->Width,
		  (int) Rect->Height,
		  r, g, b);
}


bool32
IsWorldEmpty(game_state* GameState, vector2* Point)
{
    if(Point->X < 0 ||
       Point->X >= GameState->Width ||
       Point->Y < 0 ||
       Point->Y >= GameState->Height)
    {
	return(false);
    }

    return(true);
}

void
GameUpdateAndRender(SDL_Renderer* Renderer,
		    game_input* Input,
		    game_state* GameState)
{
    game_ball *Ball = &GameState->Ball;
    game_paddle *Paddle = &GameState->Paddle;
    
    Paddle->dP = {0.0f, 0.0f};
    if(Input->MoveLeft)
    {
	Paddle->dP = {-1.0f, 0.0f};
    }
    if(Input->MoveRight)
    {
	Paddle->dP = {1.0f, 0.0f};
    }
    if(Input->ActionUp && Ball->State == START_STATE)
    {
	Ball->State = RUNNING_STATE;
    }
    Paddle->dP.X *= Paddle->Speed;

    vector2 NewP = Paddle->P + Paddle->dP;


    vector2 NewPaddlePBottomRight = {};
    NewPaddlePBottomRight.X = Paddle->dP.X + Paddle->P.X + Paddle->Width;
    NewPaddlePBottomRight.Y = Paddle->P.Y;    
    
    if(IsWorldEmpty(GameState, &NewP) &&
       IsWorldEmpty(GameState, &NewPaddlePBottomRight))
    {
	Paddle->P = NewP;
	if(Ball->State == START_STATE)
	    Ball->P.X = Paddle->P.X + (Paddle->Width/2.0f);
    }
    if(Ball->State == RUNNING_STATE)
    {
	// TODO(hugo) : Look for collisions with blocks
	// ==> need for something more complete
	// WRITE THE USAGE CODE FIRST
	
	// NOTE(hugo): if we just got into running state
	if(Ball->dP.X == 0 &&
	   Ball->dP.Y == 0)
	{
	    Ball->dP = {Ball->Speed, Ball->Speed};
	}

	vector2 NewBallP = Ball->P + Ball->dP;

	if(NewBallP.X <= 0 ||
	   NewBallP.X >= GameState->Width ||
	   NewBallP.X + Ball->Width <= 0 ||
	   NewBallP.X + Ball->Width >= GameState->Width)
	{
	    Ball->dP.X = -Ball->dP.X;
	}


	if(NewBallP.Y >= GameState->Height ||
	   NewBallP.Y + Ball->Height >= GameState->Height)
	{
	    Ball->dP.Y = -Ball->dP.Y;
	}

	// NOTE(hugo): if the ball collides the paddle
	if(NewBallP.Y < Paddle->P.Y + Paddle->Height &&
	   NewBallP.Y >= Paddle->P.Y + 0.75f*Paddle->Height &&
	   NewBallP.X + Ball->Width >= Paddle->P.X &&
	   NewBallP.X <= Paddle->P.X + Paddle->Width)
	{
	    Ball->dP.Y = -Ball->dP.Y;
	}
	if(NewBallP.Y + Ball->Height <= 0)
	{
	    GameState->Running = false;
	}
	
	Ball->P = Ball->P + Ball->dP;
    }

    // NOTE(hugo): Rendering
    SDL_SetRenderDrawColor(Renderer, 128, 128, 128, 255);	    
    SDL_RenderClear(Renderer);
    DrawRectangle(Renderer,
		  Paddle->P,
		  (int) Paddle->Width,
		  (int) Paddle->Height,
		  0, 255, 0);
    DrawRectangle(Renderer,
		  Ball->P,
		  (int) Ball->Width,
		  (int) Ball->Height, 255, 0, 0);
}
