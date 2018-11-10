#include "character.h"

#define BLOCK_SIZE 20

/*
struct vector2 *jump(struct Character *character)
{
    struct vector2 position;
    struct vector2 velocity;
    struct vector2 f
}
*/

// Jump
//
// f(t) = 1/2 * gt^2 + vt + p   g gravity
//                              v initial velocity
//                              p initital position
//
// v = 2h / (th)   th time at which peak height is reached
//
// g = -2h / (th)^2   h peak height
//
// th = xh / (vx)
// v = 2h(vx) / (xh)
// g = -2h(vx)^2 / (xh)^2
