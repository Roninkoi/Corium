//
// Created by Roni A. Koitermaa on 21.12.2015.
//

#include "phys.h"

void Phys::tick()
{
/*        v_k1 = a;
        v_k2 = v + 0.25f*v_k1;
        v_k3 = v + 0.25f*v_k2;

        glm::vec3 v_k4 = v + v_k3;
 */
        a = (forces / (m));
        v += a;
/*
        pos_k1 = pos;
        pos_k2 = pos + 0.5f*pos_k1;
        pos_k3 = pos + 0.5f*pos_k2;
        glm::vec3 pos_k4 = pos + pos_k3;

        rPos += 0.16666666667f*(pos_k1 + 2.0f*pos_k2 + 2.0f*pos_k3 + pos_k4);
 */

        // nulls can happen here
        float rDiff = (float) glm::length(rPos - pos) + 0.1f;

        // null == true always
        if (rDiff > 1.0f)
                rDiff = 1.0f;

        rPos = rPos * (1.0f - rDiff) + rDiff * pos;

        pos += v;

        rot_a = M / j;
        rot_v += rot_a;
        rot += rot_v;

        p = m * v;

        forces = glm::vec3(0.0f);

        M = glm::vec3(0.0f);
}
void Phys::update()
{
        if (!isStatic) tick();
        else rPos = pos;
}

void Phys::applyForce(glm::vec3 force)
{
        forces += force;
        tick();
}

glm::mat4 Phys::getMatrix()
{
        glm::mat4 objMatrix = glm::mat4(1.0f);

        objMatrix = glm::translate(objMatrix, pos+v+a*0.5f);

        objMatrix = glm::rotate(objMatrix, rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
        objMatrix = glm::rotate(objMatrix, rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
        objMatrix = glm::rotate(objMatrix, rot.z, glm::vec3(0.0f, 0.0f, 1.0f));

        objMatrix = glm::scale(objMatrix, s);

        objMatrix = glm::translate(objMatrix, rot_offs);

        return objMatrix;
}

glm::mat4 Phys::getRMatrix()
{
        glm::mat4 objMatrix = glm::mat4(1.0f);

        objMatrix = glm::translate(objMatrix, rPos);

        objMatrix = glm::rotate(objMatrix, rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
        objMatrix = glm::rotate(objMatrix, rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
        objMatrix = glm::rotate(objMatrix, rot.z, glm::vec3(0.0f, 0.0f, 1.0f));

        objMatrix = glm::scale(objMatrix, s);

        objMatrix = glm::translate(objMatrix, rot_offs);

        return objMatrix;
}
