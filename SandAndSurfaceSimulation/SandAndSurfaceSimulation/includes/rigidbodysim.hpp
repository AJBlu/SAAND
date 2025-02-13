#include <box2d/box2d.h>

void b2d_init();

void b2d_clear();

//origin points
const float GROUND_X = 0.0f;
const float GROUND_Y = 0.0f;


//starting point
b2Vec2 ground_start = { -3.0f, 2.0f };
b2Vec2 ground_end = { 3.0f, 2.0f };


