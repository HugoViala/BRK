#if !defined(BRK_H)
#define BRK_H

// IMPORTANT(hugo): It is not awesome to have to include SDL here
// Maybe it would be possible to create our own "proxy" to fill
// all the properties of the renderer that needs be implemented
#include <SDL.h>
#include "brk_types.h"
#include "vector2.h"

struct game_input
{
    bool32 MoveLeft;
    bool32 MoveRight;
    bool32 ActionUp;

    // TODO(hugo): find a better name
    bool32 SpeedUp;
};


struct game_rect
{
    vector2 Pos;
    real32 Width;
    real32 Height;
};

enum ball_state
{
    START_STATE,
    RUNNING_STATE
};

struct game_ball
{
    vector2 P;
    vector2 dP;
    real32 Width;
    real32 Height;
    real32 Speed;
    
    ball_state State;    
};

struct game_paddle
{
    vector2 P;
    vector2 dP;
    real32 Width;
    real32 Height;
    real32 Speed;
};

struct game_state
{
    // TODO(hugo): Should I make this a pointer ?
    game_paddle Paddle;
    game_ball Ball;

    int Width;
    int Height;

    bool32 Running;
};

void
GameUpdateAndRender(SDL_Renderer* Renderer,
		    game_input* Input,
		    game_state* GameState);

#endif
