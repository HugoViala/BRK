#include "brk.h"

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
    vector2 dPaddle = {};
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
    if(Input->ActionUp && GameState->Ball.State == START_STATE)
    {
	GameState->Ball.State = RUNNING_STATE;
    }
    dPaddle.X *= PaddleSpeed;

    vector2 NewPaddlePosBottomLeft = {};
    NewPaddlePosBottomLeft.X = dPaddle.X + GameState->Paddle.Rect.Pos.X;
    NewPaddlePosBottomLeft.Y = GameState->Paddle.Rect.Pos.Y;

    vector2 NewPaddlePosBottomRight = {};
    NewPaddlePosBottomRight.X = dPaddle.X + GameState->Paddle.Rect.Pos.X + GameState->Paddle.Rect.Width;
    NewPaddlePosBottomRight.Y = GameState->Paddle.Rect.Pos.Y;    
    
    if(IsWorldEmpty(GameState, &NewPaddlePosBottomLeft) &&
       IsWorldEmpty(GameState, &NewPaddlePosBottomRight))
    {
	GameState->Paddle.Rect.Pos = NewPaddlePosBottomLeft;
	if(GameState->Ball.State == START_STATE)
	    GameState->Ball.Rect.Pos.X = GameState->Paddle.Rect.Pos.X + (GameState->Paddle.Rect.Width/2.0f);
    }
    if(GameState->Ball.State == RUNNING_STATE)
    {
	GameState->Ball.Rect.Pos.Y++;
    }

    // NOTE(hugo): Rendering
    SDL_SetRenderDrawColor(Renderer, 128, 128, 128, 255);	    
    SDL_RenderClear(Renderer);

    DrawRectangle(Renderer, &GameState->Paddle.Rect, 0, 255, 0);
    DrawRectangle(Renderer, &GameState->Ball.Rect, 255, 0, 0);
}
