//
// Created by Roni A. Koitermaa on 18.12.2015.
//

#include "player.h"
#include <util/objParser.h>

void Player::getPlayerCam()
{
        bool camMoved = false;
        if (glm::length(phys.rot_v) > 0.0f)
                camMoved = true;

        if (camera->camai && !flying) {
                if (camMoved) {
                        camera->rot = phys.rot;
                }
                else if (moving) {
                        float lma = -lastmovangle + M_PI;

                        if (fabs(lma - camera->rot.y) > M_PI) // discontinuity
                                camera->rot.y += 2 * M_PI * ((lma - camera->rot.y) / fabs(lma - camera->rot.y));

                        camera->rot.y = camera->rot.y * 0.95f + 0.05f * lma;

                        phys.rot.y = camera->rot.y;
                        phys.rot.x = camera->rot.x;
                }
                if (!camMoved && (moving || glm::length(phys.v) > 0.1f))
                        camera->rot.x = (asin(playerLastMov.y) * 1.0f + 0.4f) * 0.05f + 0.95f * camera->rot.x;
        }
        else {
                camera->rot = phys.rot;
        }
        camera->pos = -renderPos;
}

void Player::getInput(Input *input)
{
        phys.rot_v = glm::vec3(0.0f);

        if (input->focused) phys.rot_v.y = (float) input->mouse_posDiff.x / (1000.0f / input->mouse_spd);
        if (input->focused) phys.rot_v.x = (float) input->mouse_posDiff.y / (1000.0f / input->mouse_spd);

        int count;
        const float *axes = glfwGetJoystickAxes(input->jsnum, &count);

        if (count >= 4) {
                float ax = axes[2] * 0.05f;
                float ay = axes[3] * 0.05f;

                if (fabs(ax) < 0.01f)
                        ax = 0.0f;
                if (fabs(ay) < 0.01f)
                        ay = 0.0f;

                phys.rot_v.y += ax;
                phys.rot_v.x += ay;
        }

        if (input->getKey(GLFW_KEY_LEFT)) {
                phys.rot_v.y = -0.05;
        }
        if (input->getKey(GLFW_KEY_RIGHT)) {
                phys.rot_v.y = 0.05;
        }
        if (input->getKey(GLFW_KEY_UP)) {
                phys.rot_v.x = -0.05;
        }
        if (input->getKey(GLFW_KEY_DOWN)) {
                phys.rot_v.x = 0.05;
        }

        //getPlayerCam();

        moving = false;
        playerMov = phys.v;

        if (onGround || flying) {
                if (input->keyDown[65]) {
                        phys.v.z += -0.05 * cos(phys.rot.y - 3.14159 / 2.0) * spd * (1.0f + (int) flying * 3);
                        phys.v.x += 0.05 * sin(phys.rot.y - 3.14159 / 2.0) * spd * (1.0f + (int) flying * 3);
                        moving = true;
                }
                if (input->keyDown[68]) {
                        phys.v.z += 0.05 * cos(phys.rot.y - 3.14159 / 2.0) * spd * (1.0f + (int) flying * 3);
                        phys.v.x += -0.05 * sin(phys.rot.y - 3.14159 / 2.0) * spd * (1.0f + (int) flying * 3);
                        moving = true;
                }
                if (input->keyDown[87]) {
                        phys.v.z += -0.05 * cos(phys.rot.y) * spd * (1.0f + (int) flying * 3);
                        phys.v.x += 0.05 * sin(phys.rot.y) * spd * (1.0f + (int) flying * 3);
                        moving = true;
                }
                if (input->keyDown[83]) {
                        phys.v.z += 0.05 * cos(phys.rot.y) * spd * (1.0f + (int) flying * 3);
                        phys.v.x += -0.05 * sin(phys.rot.y) * spd * (1.0f + (int) flying * 3);
                        moving = true;
                }
                if (count >= 2) {
                        float ax = axes[0];
                        float ay = axes[1];

                        if (fabs(ax) < 0.2f)
                                ax = 0.0f;
                        if (fabs(ay) < 0.2f)
                                ay = 0.0f;
                        if (fabs(ax) > 0.0f || fabs(ay) > 0.0f) {
                                moving = true;
                                phys.v.z += 0.05 * cos(phys.rot.y - 3.14159 / 2.0) * spd * (1.0f + (int) flying * 3) * ax;
                                phys.v.x += -0.05 * sin(phys.rot.y - 3.14159 / 2.0) * spd * (1.0f + (int) flying * 3) * ax;

                                phys.v.z += 0.05 * cos(phys.rot.y) * spd * (1.0f + (int) flying * 3) * ay;
                                phys.v.x += -0.05 * sin(phys.rot.y) * spd * (1.0f + (int) flying * 3) * ay;
                        }
                }
        }

        if (input->keyDown[70] && flying) {
                phys.v.y += -0.05 * spd * (1.0f + (int) flying * 3);
        }
        if (input->keyDown[82] && flying) {
                phys.v.y += 0.05 * spd * (1.0f + (int) flying * 3);
        }

        playerMov -= phys.v;
}

Texture test;

void Player::loadPlayer()
{
        loadMesh("gfx/models/ico.obj", "gfx/models/icos.obj");
        clipMesh = loadObj("gfx/models/ico.obj");

        test.loadTexture("gfx/test2.png");

        playerAnims.clearAnims();
        playerAnims.loadTemplate("gfx/models/anim/dragon_3.obj", "gfx/dragon.png");
        playerAnims.addAnim("gfx/models/anim/dragon_", 5, 0.09f, {0});
        playerAnims.addAnim("gfx/models/anim/dragonflame", 3, 0.05f, {0, 1, 2});
        playerAnims.addAnim("gfx/models/anim/dragon_4.obj", 0, 0.05f, {0});
}

void Player::restartPlayer()
{
        health = 100.0f;

        phys.v = glm::vec3(0.0f);

        phys.pos = startPos;
        phys.rot = startRot;
        renderPos = startPos;
}

void Player::draw(Renderer *renderer)
{
        playerAnims.draw(renderer);
        //physMesh.draw(renderer, &test);
}

void Player::drawShadows(Renderer *renderer)
{
        playerAnims.drawShadows(renderer);
}

void Player::collide(PhysSys *ps)
{
        // pm r 1.46
        // cm r 2.33

        physMesh.objMatrix = glm::mat4(1.0f);
        physMesh.objMatrix = glm::translate(physMesh.objMatrix, phys.pos);
        physMesh.objMatrix = glm::translate(physMesh.objMatrix, glm::vec3(0.0f, -1.5f, 0.0f));
        physMesh.objMatrix = glm::rotate(physMesh.objMatrix, lastmovangle, glm::vec3(0.0f, 1.0f, 0.0f));
        physMesh.objMatrix = glm::scale(physMesh.objMatrix, glm::vec3(1.2f));

        physMesh.update();
        mesh.objMatrix = physMesh.objMatrix;
        mesh.update();

        //clipMesh.phys.pos.y -= 1.0f;
        clipMesh.objMatrix = glm::mat4(1.0f);
        clipMesh.objMatrix = glm::translate(clipMesh.objMatrix, phys.pos);
        clipMesh.objMatrix = glm::translate(clipMesh.objMatrix,
                                            glm::vec3(0.0f, -1.7f, 0.0f) + glm::vec3(0.0f, 0.0f, 0.0f));
        clipMesh.objMatrix = glm::scale(clipMesh.objMatrix, glm::vec3(0.5f, 3.0f, 0.5f));

        clipMesh.update();

        if (glm::length(ps->field) > 0.0f && onGround) {
                // friction
                phys.v.x *= 0.8f;
                phys.v.z *= 0.8f;
        }
        else {
                // air resistance
                phys.v *= glm::vec3(0.99f);
        }

        colliding = false;

        onGround = false;

        float bouncyness = 0.01f;

        for (int i = 0; i < ps->objects.size(); ++i) {
                if (clipMesh.bsi(&ps->objects[i]->physMesh)) {
                        if (ps->objects[i]->physMesh.intersects(&clipMesh)) {
                                if (!(clipMesh.collision_normal != clipMesh.collision_normal)) {
                                        onGround = true;
                                }
                        }
                }
                if (physMesh.bsi(&ps->objects[i]->physMesh)) {         // bounding sphere test
                        if (ps->objects[i]->physMesh.intersects(&physMesh)) {
                                if (ps->objects[i]->phys.isStatic && !ps->objects[i]->phys.isSemiStatic) { // map geometry only
                                        colliding = true;

                                        // gravity damping
                                        phys.v.y *= 0.2;

                                        glm::vec3 normalVec = glm::normalize(physMesh.collision_normal);
                                        glm::mat3 vecProj = getVecProjMatrix(normalVec);

                                        glm::vec3 newForce = normalVec * (glm::length((phys.v - playerMov) * vecProj) + bouncyness)*phys.m;

                                        if (!(newForce != newForce)) {
                                                phys.forces += newForce;
                                        }
                                }
                                else {
                                        ps->objects[i]->phys.isStatic = false;

                                        glm::vec3 normalVec = glm::normalize(physMesh.collision_normal);
                                        glm::mat3 vecProj = getVecProjMatrix(normalVec);

                                        glm::vec3 newForce = (normalVec) *(glm::length(((phys.v - playerMov)*phys.m + (ps->objects[i]->phys.v)*ps->objects[i]->phys.m) * vecProj) + bouncyness);

                                        if (!(newForce != newForce)) {
                                                if (sprinting) ps->objects[i]->phys.forces += -newForce;
                                                else ps->objects[i]->phys.forces += -newForce * 0.5f;
                                                phys.forces += newForce;
                                        }
                                }
                        }
                }
        }

        if (!colliding) phys.forces += ps->field*phys.m;

        float c = std::max(0.0f, std::min(0.95f, glm::length(phys.v)));
        if (glm::length(renderPos - phys.pos) > 0.05f)
                renderPos = phys.pos * (0.05f + c) + renderPos * (0.95f - c);

        if (glm::length(phys.v) > 0.05f) playerLastMov = -phys.v * 0.07f + playerLastMov * 0.93f;
}

void Player::tick()
{
        if (health < 0.0f) {
                health = 0.0f;
        }
        if (flying) {
                phys.v.y *= 0.4f;
                phys.v.x *= 0.5f;
                phys.v.z *= 0.5f;
                renderPos = phys.pos;
                health = 1000.0f;
        }

        getPlayerCam();

        playerAnims.phys.pos = renderPos;

        lastmovangle = 0.0f;
        glm::vec3 movvec = glm::vec3(playerLastMov.x, 0.0f, playerLastMov.z);
        if (glm::length(movvec) > 0.0f)
                lastmovangle = (acos(glm::dot(glm::normalize(movvec), glm::vec3(0.0f, 0.0f, -1.0f))));

        if (playerLastMov.x > 0.0f) {
                lastmovangle = -lastmovangle;
        }

        playerAnims.phys.rot.y = lastmovangle;

        playerAnims.phys.pos.y -= 2.5f;

        playerAnims.anim_running[0] = true;
        playerAnims.anim_running[1] = flaming;
        playerAnims.anim_running[2] = sprinting;

        if (moving && !flying) {
                // main running animation
                playerAnims.anims[0].setAnim(0.09f, {0, 1, 2});

                // set animation speed based on player speed
                playerAnims.anims[0].setSpd(0.09f * sqrt(glm::length(playerMov)) * 4.0f);
        }
        else {
                playerAnims.anims[0].setAnim(0.2f, {3});
        }
        if (!onGround) {
                // falling animation
                playerAnims.anims[0].setAnim(0.2f, {1}, true);
        }

        if (flaming) {
                // flaming animation
                playerAnims.anims[1].setAnim(0.05f, {0, 1, 2});
        }
        else {
                playerAnims.anims[1].setAnim(0.1f, {2});
        }

        if (!flying)
                playerAnims.tick();
}
