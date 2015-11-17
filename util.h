#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <stdlib.h>

double GetTime();

double getRandom();

/**
*   structure containing a pair of 2D coordinates
*/

struct Vec2d {
    double x;
    double y;
};

/**
*   Axis Aligned bounding box structure containing 2 Vec2D structures of coordinates
*/
struct AABB {
    Vec2d p1;
    Vec2d p2;
};

const bool AABBinstersect(const AABB &a, const AABB &b);

#endif // UTIL_H_INCLUDED
