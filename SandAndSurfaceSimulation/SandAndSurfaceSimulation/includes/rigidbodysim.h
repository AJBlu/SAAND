#include<box2d/box2d.h>
void b2d_init();

void b2d_clear();

void b2d_timestep();

float m_to_px(float m);

float px_to_m(float px);

b2BodyId* createBody(float x, float y, float w, float h, b2WorldId* worldId) {
	b2BodyDef def = b2DefaultBodyDef();
	def.position = { x, y };
	b2BodyId id = b2CreateBody(*worldId, &def);
	b2Polygon Body = b2MakeBox(w /2.0f, h /2.0f);
	b2ShapeDef bodyShape = b2DefaultShapeDef();
	b2CreatePolygonShape(id, &bodyShape, &Body);
	printf("Established ground body\n");
}