#include "util.h"


#include <sys/time.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

/* Helpful conversion constants. */
static const unsigned usec_per_sec = 1000000;
static const unsigned usec_per_msec = 1000;

/* These functions are written to match the win32
   signatures and behavior as closely as possible.
*/
bool QueryPerformanceFrequency(int64_t *frequency)
{
    /* Sanity check. */
    assert(frequency != NULL);

    /* gettimeofday reports to microsecond accuracy. */
    *frequency = usec_per_sec;

    return true;
}

bool QueryPerformanceCounter(int64_t *performance_count)
{
    struct timeval time;

    /* Sanity check. */
    assert(performance_count != NULL);

    /* Grab the current time. */
    gettimeofday(&time, NULL);
    *performance_count = time.tv_usec + /* Microseconds. */
                         time.tv_sec * usec_per_sec; /* Seconds. */

    return true;
}

/**
*   Gets a timestamp to calculate the delta time from
*
*/
double GetTime(){
    int64_t freq, time;
    QueryPerformanceCounter(&time);
    QueryPerformanceFrequency(&freq);

    return (double)(time) / (double)freq;
}

/**
*   A function to return a random positive or negative 1 (+1, -1 but not 0)
*/
double getRandom(){
    double random = rand()%3-1;
    if(random == 0)
    {
        random = getRandom();
    }
    return random;
}

/**
*   Checks all possible chances of a collision between two axis aligned bounding boxes
*   This is standard code for checking 2D bounding boxes
*
*   @param &a reference to the first AABB structure
*   @param &b reference to the second AABB structure
*
*/

const bool AABBinstersect(const AABB &a, const AABB &b){
    //Check B topleft within A
    if(b.p1.x >= a.p1.x && b.p1.x <= a.p2.x && b.p1.y >= a.p1.y && b.p1.y <= a.p2.y)
        return true;
    //Check B bottomrright within A
    if(b.p2.x >= a.p1.x && b.p2.x <= a.p2.x && b.p2.y >= a.p1.y && b.p2.y <= a.p2.y)
        return true;
    //Check B topright within A
    if(b.p2.x >= a.p1.x && b.p2.x <= a.p2.x && b.p1.y >= a.p1.y && b.p1.y <= a.p2.y)
        return true;
    //Check B bottomleft within A
    if(b.p1.x >= a.p1.x && b.p1.x <= a.p2.x && b.p2.y >= a.p1.y && b.p2.y <= a.p2.y)
        return true;
    //Check A topleft within B
    if(a.p1.x >= b.p1.x && a.p1.x <= b.p2.x && a.p1.y >= b.p1.y && a.p1.y <= b.p2.y)
        return true;
    //Check A bottomrright within B
    if(a.p2.x >= b.p1.x && a.p2.x <= b.p2.x && a.p2.y >= b.p1.y && a.p2.y <= b.p2.y)
        return true;
    //Check A topright within B
    if(a.p2.x >= b.p1.x && a.p2.x <= b.p2.x && a.p1.y >= b.p1.y && a.p1.y <= b.p2.y)
        return true;
     //Check A bottomleft within B
    if(a.p1.x >= b.p1.x && a.p1.x <= b.p2.x && a.p2.y >= b.p1.y && a.p2.y <= b.p2.y)
        return true;
    return false;
}
