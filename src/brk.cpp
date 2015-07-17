#include "brk.h"


// NOTE(hugo): This function draws a rectangle in
// math canonical coordinates
void
DrawRectangle(SDL_Renderer *Renderer, int x, int y, int w, int h)
{
    // TODO(hugo): Should these be encoded somewhere else ?
    // IMPORTANT(hugo): I have starter to encode them in the GameState
    int WindowWidth;
    int WindowHeight;
    SDL_GetRendererOutputSize(Renderer,
			      &WindowWidth, &WindowHeight);

    SDL_Rect DrawingRect = {};
    DrawingRect.x = x;
    DrawingRect.y = WindowHeight - y;
    DrawingRect.w = w;
    DrawingRect.h = h;

    SDL_RenderFillRect(Renderer, &DrawingRect);
}

bool32
IsWorldEmpty(game_state* GameState, game_point* Point)
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


    game_point dPaddle = {};
    dPaddle.X = 0.0f;
    real32 PaddleSpeed = 5.0f;
    
    if(Input->MoveLeft)
    {
	dPaddle.X = -1.0f;
    }
    if(Input->MoveRight)
    {
	dPaddle.X = 1.0f;
    }
    dPaddle.X *= PaddleSpeed;

    game_point NewPaddlePosBottomLeft = {};
    NewPaddlePosBottomLeft.X = dPaddle.X + GameState->Paddle.BottomLeftPos.X;
    NewPaddlePosBottomLeft.Y = GameState->Paddle.BottomLeftPos.Y;

    game_point NewPaddlePosBottomRight = {};
    NewPaddlePosBottomRight.X = dPaddle.X + GameState->Paddle.BottomLeftPos.X + GameState->Paddle.Width;
    NewPaddlePosBottomRight.Y = GameState->Paddle.BottomLeftPos.Y;    
    
    if(IsWorldEmpty(GameState, &NewPaddlePosBottomLeft) &&
       IsWorldEmpty(GameState, &NewPaddlePosBottomRight))
    {
	GameState->Paddle.BottomLeftPos = NewPaddlePosBottomLeft;
	SDL_Log("%f", NewPaddlePosBottomLeft.X);
    }

    // NOTE(hugo): Rendering
    SDL_SetRenderDrawColor(Renderer, 128, 128, 128, 255);	    
    SDL_RenderClear(Renderer);
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    DrawRectangle(Renderer,
		  (int) GameState->Paddle.BottomLeftPos.X,
		  (int) GameState->Paddle.BottomLeftPos.Y,
		  (int) GameState->Paddle.Width,
		  (int) GameState->Paddle.Height);
}
