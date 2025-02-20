#include "rigidbodysim.h"


const float pxpm = 128.0f;

//origin points
const float GROUND_X = 0.0f;
const float GROUND_Y = 0.0f;

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;



float m_to_px(float m) { return m * pxpm;  }

float px_to_m(float px) { return px / pxpm; }

void b2d_init() {

	//box2d init
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = b2Vec2{ 0.0f, -9.81f };
	b2WorldId worldId = b2CreateWorld(&worldDef);

	//line body
	b2BodyDef groundDef;
	groundDef.type = b2_staticBody;
	groundDef.position = { GROUND_X, GROUND_Y };
	groundDef.rotation = { 0.0f, 0.0f };
	b2BodyId groundId = b2CreateBody(worldId, &groundDef);


	b2Vec2 groundExtent = { px_to_m(SCREEN_WIDTH), px_to_m(SCREEN_HEIGHT / 2.0f) };
	//shape for body
	b2Polygon box = b2MakeBox(groundExtent.x, groundExtent.y);




}

void b2d_clear() {
	//b2DestroyWorld(worldId);
	//worldId = b2_nullWorldId;
}