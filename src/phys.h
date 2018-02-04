//
// Created by Roni A. Koitermaa on 21.12.2015.
//

#ifndef CORIUM_PHYS_H
#define CORIUM_PHYS_H

#include <crm.h>

const float PHYS_EPSILON = 0.0005f;

class Phys {
public:
glm::vec3 pos = glm::vec3(0.0f);

glm::vec3 pos_k1 = glm::vec3(0.0f);
glm::vec3 pos_k2 = glm::vec3(0.0f);
glm::vec3 pos_k3 = glm::vec3(0.0f);

glm::vec3 rot = glm::vec3(0.0f);

glm::vec3 rot_v = glm::vec3(0.0f);
glm::vec3 rot_a = glm::vec3(0.0f);

glm::vec3 s = glm::vec3(1.0f);

glm::vec3 rPos = glm::vec3(0.0f);

glm::vec3 rot_offs = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec3 v = glm::vec3(0.0f);

glm::vec3 v_k1 = glm::vec3(0.0f);
glm::vec3 v_k2 = glm::vec3(0.0f);
glm::vec3 v_k3 = glm::vec3(0.0f);

glm::vec3 a = glm::vec3(0.0f);
glm::vec3 forces = glm::vec3(0.0f);

bool inRange = true;

bool isColliding = false;
int collision_num = 0;

glm::vec3 p = glm::vec3(0.0f);
float m = 1.0f;

glm::vec3 l = glm::vec3(0.0f);
float j = 100.0f;
glm::vec3 M = glm::vec3(0.0f);

bool isStatic = false;
bool isSemiStatic = false;

bool isGravity = true;

void update();

void tick();

void applyForce(glm::vec3 force);

glm::mat4 getMatrix();
glm::mat4 getRMatrix();

Phys()
{
}
};

// build vector projection matrix
glm::mat3 getVecProjMatrix(glm::vec3 vector)
{
        glm::mat3 vecProj = glm::mat3(1.0f);

        // projection matrix
        vecProj[0] = glm::vec3(vector.x * vector.x, vector.x * vector.y,vector.x * vector.z);
        vecProj[1] = glm::vec3(vector.y * vector.x, vector.y * vector.y,vector.y * vector.z);
        vecProj[2] = glm::vec3(vector.z * vector.x, vector.z * vector.y,vector.z * vector.z);

        return vecProj;
}

// bigger than zero
bool btz(glm::vec3 vector)
{
        if (glm::length(vector) > 0.0f)
                return true;
        else
                return false;
}

// bigger than epsilon
bool bte(glm::vec3 vector)
{
        if (glm::length(vector) > PHYS_EPSILON)
                return true;
        else
                return false;
}

// less than epsilon
bool lte(glm::vec3 vector)
{
        if (glm::length(vector) <= PHYS_EPSILON)
                return true;
        else
                return false;
}

#endif //CORIUM_PHYS_H
