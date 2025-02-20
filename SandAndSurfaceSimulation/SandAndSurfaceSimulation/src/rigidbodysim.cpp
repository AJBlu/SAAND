#include "rigidbodysim.h"
#include <stdio.h>
const float TIMESTEP = 1.0f / 60.0f;
const float PXPM = 128.0f;
const int SSC = 4;
float m_to_px(float m) { return m * PXPM;  }

float px_to_m(float px) { return px / PXPM; }

void b2d_init() {

    //box2d init
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ 0.0f, -9.81f };
    b2WorldId worldId = b2CreateWorld(&worldDef);

    //line body
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = { 0.0f, -10.0f };
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);



    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = { 0.0f, 4.0f };
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);
    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
    for (int i = 0; i < 90; ++i)
    {
        b2World_Step(worldId, TIMESTEP, SSC);
        b2Vec2 position = b2Body_GetPosition(bodyId);
        b2Rot rotation = b2Body_GetRotation(bodyId);
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, b2Rot_GetAngle(rotation));
    }
}

void b2d_clear() {
	//b2DestroyWorld(worldId);
	//worldId = b2_nullWorldId;
}