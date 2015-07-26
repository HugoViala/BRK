#include "vector2.h"

v2 operator+(v2 A, v2 B)
{
    v2 Result = {};
    Result.X = A.X + B.X;
    Result.Y = A.Y + B.Y;
    return(Result);
}
