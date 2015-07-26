#include "vector2.h"

vector2 operator+(vector2 A, vector2 B)
{
    vector2 Result = {};
    Result.X = A.X + B.X;
    Result.Y = A.Y + B.Y;
    return(Result);
}
