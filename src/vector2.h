#if !defined(VECTOR2)
#define VECTOR2

#include "brk_types.h"

// NOTE(hugo): This represent a point in the math
// referentiel (bottom-left is (0,0))
struct v2
{
    real32 X;
    real32 Y;
};

v2 operator+(v2 A, v2 B);


#endif
