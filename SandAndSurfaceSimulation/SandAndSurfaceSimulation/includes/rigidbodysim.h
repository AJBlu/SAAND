#include<box2d/box2d.h>
void b2d_init();

void b2d_clear();

void b2d_timestep();

b2BodyId createBody(float x, float y, float w, float h, b2WorldId* worldId, bool isDynamic);