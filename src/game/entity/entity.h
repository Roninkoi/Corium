//
// Created by Roni A. Koitermaa on 18.12.2015.
//

#ifndef CORIUM_ENTITY_H
#define CORIUM_ENTITY_H

#include "../obj/obj.h"
#include "../../phys.h"

class Entity : public Obj {
public:
float health = 100.0f;

bool colliding = false;

bool onGround = true;

float ticks = 0.0f;

bool sprinting = false;

bool hurt = false;

bool jumping = false;

bool moving = false;

float spd = 1.0f;

void draw(Renderer* renderer);
void drawShadows(Renderer* renderer);

void tick();

Entity() : Obj()
{

}
};

#endif //CORIUM_ENTITY_H
