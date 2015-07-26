#if !defined(VECTOR2)
#define VECTOR2

#include "brk_types.h"

// NOTE(hugo): This represent a point in the math
// referentiel (bottom-left is (0,0))
struct vector2
{
    real32 X;
    real32 Y;
};

vector2 operator+(vector2 A, vector2 B);


#endif
