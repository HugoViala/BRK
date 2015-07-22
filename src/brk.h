#if !defined(BRK_H)
#define BRK_H

// IMPORTANT(hugo): It is not awesome to have to include SDL here
// Maybe it would be possible to create our own "proxy" to fill
// all the properties of the renderer that needs be implemented
#include <SDL.h>


#define internal static
#define local_persist static
#define global_variable static


typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32 bool32;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float real32;
typedef double real64;


struct game_input
{
    bool32 MoveLeft;
    bool32 MoveRight;
    bool32 ActionUp;
};


// NOTE(hugo): This represent a point in the math
// referentiel (bottom-left is (0,0))
struct game_point
{
    real32 X;
    real32 Y;
};

struct game_ball
{
    game_point Pos;
    real32 Width;
    real32 Height;
};

struct game_paddle
{
    game_point BottomLeftPos;
    real32 Width;
    real32 Height;
};

struct game_state
{
    // TODO(hugo): Should I make this a pointer ?
    game_paddle Paddle;
    game_ball Ball;

    int Width;
    int Height;
};

void
GameUpdateAndRender(SDL_Renderer* Renderer, game_input* Input, game_state* GameState);

#endif
