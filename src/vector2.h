#if !defined(VECTOR2)
#define VECTOR2

#include <cmath>
#include "brk_types.h"

// NOTE(hugo): This represent a point in the math
// referentiel (bottom-left is (0,0))
struct v2
{
    real32 X;
    real32 Y;
    inline v2& operator*=(real32 Lambda);

};

v2 operator+(v2 A, v2 B);
v2 operator*(real32 Lambda, v2 A);
real32 norm(v2 A);


#endif
