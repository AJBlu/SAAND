#include "rigidbodysim.h"
#include <stdio.h>

b2BodyId createBody(float x, float y, float w, float h, b2WorldId* worldId, bool isDynamic) {
	b2BodyDef def = b2DefaultBodyDef();
	def.position = { x, y };
	if (isDynamic)
		def.type = b2_dynamicBody;

	b2BodyId id = b2CreateBody(*worldId, &def);
	b2Polygon Body = b2MakeBox(w / 2.0f, h / 2.0f);
	b2ShapeDef bodyShape = b2DefaultShapeDef();
	b2CreatePolygonShape(id, &bodyShape, &Body);
	printf("Established ground body\n");
	return id;
}

void b2d_init() {



}

void b2d_timestep() {


}

void b2d_clear() {
	//b2DestroyWorld(worldId);
	//worldId = b2_nullWorldId;
}