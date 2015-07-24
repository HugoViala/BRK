#include "brk.h"



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
    // TODO(hugo): Should these be encoded somewhere else ?
    // IMPORTANT(hugo): I have starter to encode them in the GameState
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
    
    vector2 dPaddle = {};
    dPaddle.X = 0.0f;
    dPaddle.Y = 0.0f;
    real32 PaddleSpeedNorm = 5.0f;
    
    if(Input->MoveLeft)
    {
	dPaddle.X = -1.0f;
    }
    if(Input->MoveRight)
    {
	dPaddle.X = 1.0f;
    }
    if(Input->ActionUp && Ball->State == START_STATE)
    {
	Ball->State = RUNNING_STATE;
    }
    dPaddle.X *= PaddleSpeedNorm;

    vector2 NewPos = dPaddle + Paddle->Rect.Pos;
    //NewPos.X = dPaddle.X + Paddle.Rect.Pos.X;
    //NewPos.Y = Paddle.Rect.Pos.Y;

    vector2 NewPaddlePosBottomRight = {};
    NewPaddlePosBottomRight.X = dPaddle.X + Paddle->Rect.Pos.X + Paddle->Rect.Width;
    NewPaddlePosBottomRight.Y = Paddle->Rect.Pos.Y;    
    
    if(IsWorldEmpty(GameState, &NewPos) &&
       IsWorldEmpty(GameState, &NewPaddlePosBottomRight))
    {
	Paddle->Rect.Pos = NewPos;
	if(Ball->State == START_STATE)
	    Ball->Rect.Pos.X = Paddle->Rect.Pos.X + (Paddle->Rect.Width/2.0f);
    }
    if(Ball->State == RUNNING_STATE)
    {
	// NOTE(hugo): if we just got into running state
	if(Ball->Speed.X == 0 &&
	   Ball->Speed.Y == 0)
	{
	    Ball->Speed.X = 3.0f;
	    Ball->Speed.Y = 3.0f;
	}

	// TODO(hugo): collision check for the ball
	vector2 BallPos = Ball->Rect.Pos;
	vector2 NewBallPos = BallPos + Ball->Speed;
	/*vector2 NewBallPosUpLeft;
	NewBallPosUpLeft.X = NewBallPos.X;
	NewBallPosUpLeft.Y = NewBallPos.Y + Ball->Rect.Height;

	vector2 NewBallPosUpRight;
	NewBallPosUpLeft.X = NewBallPos.X + Ball->Rect.Width;
	NewBallPosUpLeft.Y = NewBallPos.Y + Ball->Rect.Height;

	vector2 NewBallPosBotRight;
	NewBallPosUpLeft.X = NewBallPos.X + Ball->Rect.Width;
	NewBallPosUpLeft.Y = NewBallPos.Y;*/

	if(NewBallPos.X <= 0 ||
	   NewBallPos.X >= GameState->Width ||
	   NewBallPos.X + Ball->Rect.Width <= 0 ||
	   NewBallPos.X + Ball->Rect.Width >= GameState->Width)
	{
	    Ball->Speed.X = -Ball->Speed.X;
	}


	if(NewBallPos.Y >= GameState->Height ||
	   NewBallPos.Y + Ball->Rect.Height >= GameState->Height)
	{
	    Ball->Speed.Y = -Ball->Speed.Y;
	}

	// NOTE(hugo): if the ball collides the paddle
	if(NewBallPos.Y < Paddle->Rect.Pos.Y + Paddle->Rect.Height &&
	   NewBallPos.X + Ball->Rect.Width >= Paddle->Rect.Pos.X &&
	   NewBallPos.X <= Paddle->Rect.Pos.X + Paddle->Rect.Width)
	{
	    Ball->Speed.Y = -Ball->Speed.Y;
	}
	
	
	Ball->Rect.Pos = Ball->Rect.Pos + Ball->Speed;
    }

    // NOTE(hugo): Rendering
    SDL_SetRenderDrawColor(Renderer, 128, 128, 128, 255);	    
    SDL_RenderClear(Renderer);
    DrawRectangle(Renderer, &Paddle->Rect, 0, 255, 0);
    DrawRectangle(Renderer, &Ball->Rect, 255, 0, 0);
}
