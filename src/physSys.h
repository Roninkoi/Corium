//
// Created by Roni A. Koitermaa on 2.2.2016.
//

#ifndef CORIUM_PHYSSYS_H
#define CORIUM_PHYSSYS_H

#include <game/obj/obj.h>
#include "mesh.h"
#include <thread>
#include <mutex>
//#include <mingw.thread.h>
//#include <mingw.mutex.h>

class PhysSys {
public:
std::vector<Obj *> objects;

glm::vec3 field;

float air_resistance = 0.05f;
float friction = 0.05f;
float collision_energy_loss = 1.0f;

float bouncyness = 0.1f;         // 0.17

std::mutex mtx;

int collisions = 0;

void updateObjs(int i_min, int i_max, int j_min, int j_max)
{
        for (int i = i_min; i < i_max; ++i) {
                for (int j = std::max(i + 1, j_min); j < j_max; ++j) {
                        // culling of objects
                        bool bst = objects[i]->physMesh.bsi(&objects[j]->physMesh);
                        bool st = !objects[i]->phys.isStatic || !objects[j]->phys.isStatic;
                        bool iz = btz(objects[i]->phys.v) || btz(objects[j]->phys.v);
                        bool ir = objects[i]->phys.inRange && objects[j]->phys.inRange;

                        if (bst && st && iz && ir) {
                                // triangle intersection test of meshes ~n^2
                                bool isects = objects[i]->physMesh.intersects(&objects[j]->physMesh);

                                if (isects) {
                                        ++collisions;
                                        objects[i]->phys.isColliding = true;
                                        objects[j]->phys.isColliding = true;
                                        ++objects[i]->phys.collision_num;
                                        ++objects[j]->phys.collision_num;

                                        glm::vec3 collisionVeci = glm::normalize(objects[i]->physMesh.collision_normal);
                                        glm::vec3 collisionVecj = glm::normalize(objects[j]->physMesh.collision_normal);

                                        glm::vec3 newForce = glm::vec3(0.0f);

                                        glm::mat3 vecProj = glm::mat3(1.0f);
                                        glm::vec3 normalVec = glm::normalize(collisionVeci);

                                        if (!objects[i]->phys.isStatic)
                                                newForce +=
                                                        ((objects[i]->phys.v + objects[i]->phys.a)) * objects[i]->phys.m;

                                        if (!objects[j]->phys.isStatic)
                                                newForce +=
                                                        ((objects[j]->phys.v + objects[j]->phys.a)) * objects[j]->phys.m;

                                        newForce *= collision_energy_loss;

                                        if (!objects[i]->phys.isStatic && !(collisionVeci * newForce != collisionVeci * newForce)) {
                                                vecProj = getVecProjMatrix(normalVec);

                                                glm::vec3 delta = (collisionVeci *
                                                                   (glm::length(newForce * vecProj)));

                                                objects[i]->phys.forces += delta * (bouncyness * glm::length(objects[i]->phys.v) + 1.0f);
                                                objects[i]->phys.pos += collisionVeci * glm::length(objects[i]->phys.v) * bouncyness;
                                        }
                                        vecProj = glm::mat3(1.0f);
                                        normalVec = glm::normalize(collisionVecj);

                                        if (!objects[j]->phys.isStatic && !(collisionVecj * newForce != collisionVecj * newForce)) {
                                                vecProj = getVecProjMatrix(normalVec);

                                                glm::vec3 delta = (collisionVecj *
                                                                   (glm::length(newForce * vecProj)));

                                                objects[j]->phys.forces += delta * (bouncyness * glm::length(objects[j]->phys.v) + 1.0f);
                                                objects[j]->phys.pos += collisionVecj * glm::length(objects[j]->phys.v) * bouncyness;
                                        }
                                }
                        }
                }
        }
}

void updateObjsM(int i_min, int i_max, int j_min, int j_max)
{
        mtx.lock();
        updateObjs(i_min, i_max, j_min, j_max);
        mtx.unlock();
}

// be careful with threads
bool multithreading = false;

std::thread t1;
std::thread t2;
std::thread t3;

int physTicks = 0;

void finish()
{
        if (multithreading) {
                if (t1.joinable())
                        t1.join();
                if (t2.joinable())
                        t2.join();
                if (t3.joinable())
                        t3.join();
        }
}

void update()
{
        ++physTicks;

        finish();
        collisions = 0;

        for (int i = 0; i < objects.size(); ++i) {
                if (!objects[i]->phys.isStatic && objects[i]->phys.inRange) {
                        if (objects[i]->phys.collision_num > 1) {
                                // hack, solves problems at edges of chunks
                                objects[i]->phys.forces /= objects[i]->phys.collision_num*(1.0 - bouncyness);
                        }
                        objects[i]->phys.collision_num = 0;
                        objects[i]->update();
                }
        }

        for (int i = 0; i < objects.size(); ++i) {
                if (!objects[i]->phys.isStatic && objects[i]->phys.inRange) {
                        if (bte(objects[i]->phys.v)) {
                                if (objects[i]->phys.isGravity) {
                                        objects[i]->phys.forces += field * objects[i]->phys.m;
                                }

                                objects[i]->phys.forces -=
                                        objects[i]->phys.v * glm::length(objects[i]->phys.v) * air_resistance;// air resistance
                                if (objects[i]->phys.isColliding)
                                        objects[i]->phys.forces -= objects[i]->phys.v * friction * objects[i]->phys.m; // fr
                        }

                        objects[i]->phys.update();

                        if (lte(objects[i]->phys.v) && objects[i]->phys.isColliding) {
                                objects[i]->phys.v = glm::vec3(0.0f);
                                objects[i]->phys.forces = glm::vec3(0.0f);
                                objects[i]->phys.a = glm::vec3(0.0f);
                        }
                        objects[i]->phys.isColliding = false;

                }
        }
        if (multithreading) {
                t1 = std::thread(
                        &PhysSys::updateObjs, this, 0, (int) (objects.size() / 2.0f), 0,
                        (int) (objects.size() / 2.0f));
                t2 = std::thread(
                        &PhysSys::updateObjs, this, (int) (objects.size() / 2.0f), objects.size(),
                        (int) (objects.size() / 2.0f), objects.size());

                t3 = std::thread(&PhysSys::updateObjsM, this, 0, (int) (objects.size() / 2.0f),
                                 (int) (objects.size() / 2.0f), objects.size());
                /*t1.detach();
                   t2.detach();
                   t3.detach();*/
        }
        else {
                updateObjs(0, objects.size(), 0, objects.size());
        }
}

PhysSys()
{
        field = glm::vec3(0.0f);
}
};

#endif //CORIUM_PHYSSYS_H
