#include "rigidbodysim.hpp"

void b2d_init() {
	//box2d init
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = b2Vec2{ 0.0f, -9.81f };
	b2WorldId worldId = b2CreateWorld(&worldDef);

	//line body
	b2BodyDef groundDef;
	groundDef.type = b2_staticBody;
	groundDef.position.Set(ground_x, ground_y);
	groundDef.angle = 0;

	b2Body* groundEntity = world->CreateBody(groundDef);

	b2EdgeShape edgeShape;
	edgeShape.Set(startpoint, endpoint);
	b2FixtureDef edgeFixtureDef.shape = &edgeShape;
	groundLineBody->CreateFixture(&edgeFixtureDef);


}

void b2d_clear() {
	b2DestroyWorld(worldId);

}