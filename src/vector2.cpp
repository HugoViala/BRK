#include "vector2.h"

v2
operator+(v2 A, v2 B)
{
    v2 Result = {};
    Result.X = A.X + B.X;
    Result.Y = A.Y + B.Y;
    return(Result);
}

// TODO: buggy : unlinked
inline v2& v2::
operator*=(real32 Lambda)
{
    *this = Lambda * (*this);

    return(*this);
}

v2
operator*(real32 Lambda, v2 A)
{
    v2 Result;

    Result.X = Lambda * A.X;
    Result.Y = Lambda * A.Y;

    return(Result);
}

real32
norm(v2 A)
{
    return((real32) sqrt(A.X * A.X + A.Y * A.Y));
}
