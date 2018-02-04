//
// Created by Roni A. Koitermaa on 21.12.2015.
//

#include "map.h"
#include <util/mapParser.h>

bool Map::visible(Obj *object)
{
        bool behind = true;

        glm::vec3 lookVec = glm::vec3(0.0f);
        glm::mat4 lookDir = glm::mat4(1.0f);

        lookDir = glm::rotate(lookDir, camera->rot.y,
                              glm::vec3(0.0f, 1.0f, 0.0f));
        lookDir = glm::rotate(lookDir, camera->rot.x,
                              glm::vec3(cos(camera->rot.y), 0.0, sin(camera->rot.y)));

        lookVec = glm::vec3(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f) * lookDir); // vector of player look dir?

        glm::vec3 camPos = camera->pos + lookVec * camera->z;

        glm::vec3 po = object->physMesh.boundingSphereCenter + camPos;

        po += (glm::normalize(-po) + glm::normalize(lookVec)) *
              object->physMesh.boundingSphereRadius; // there's quite a bit of error (hack)

        float visAngle = glm::dot(glm::normalize(po), glm::normalize(lookVec));

        if (visAngle > 0.3f) // < 0.0f is behind
                behind = false;

        bool isVisible = inRange(object->physMesh.boundingSphereCenter,
                                 object->physMesh.boundingSphereRadius) &&
                         (!behind || glm::length(-camPos - object->physMesh.boundingSphereCenter) < object->physMesh.boundingSphereRadius);

        object->visible = isVisible;

        return isVisible;
}

inline bool Map::inRange(Obj *object)
{
        bool ir = inRange(object->physMesh.boundingSphereCenter, object->physMesh.boundingSphereRadius);
        object->phys.inRange = ir;

        return ir;
}

inline bool Map::inRange(glm::vec3 bsc, float bsr)
{
        return (glm::length(-camera->pos - bsc) < bsr + renderer->far_plane * renderer->render_dist);
}

void Map::drawShadows(Renderer *renderer)
{
        renderer->clearShadows();

        for (int i = 0; i < environs.size(); ++i) {
                if (environs[i].rendered && environs[i].shadows && inRange(&environs[i])) {
                        environs[i].drawShadows(renderer);
                }
        }

        for (int i = 0; i < objs.size(); ++i) {
                if (objs[i].rendered && objs[i].shadows && inRange(&objs[i]) &&
                    (shadowDyn || objs[i].phys.isStatic)) {
                        objs[i].drawShadows(renderer);
                }
        }

        if (shadowDyn) {
                thisPlayer->drawShadows(renderer);
        }

        renderer->flushShadows();
}

void Map::drawObjs(Renderer *renderer)
{
        //objs[0].mesh.render(renderer);
        for (int i = 0; i < objs.size(); ++i) {
                if (objs[i].rendered && objs[i].visible) {
                        objs[i].draw(renderer);
                }
        }
        for (int i = 0; i < environs.size(); ++i) {
                if (environs[i].rendered && environs[i].visible) environs[i].draw(renderer);
        }

        thisPlayer->draw(renderer);

        renderer->flushBatch();
        if (sky.rendered) {
                renderer->disableShadows = true;
                renderer->far_plane *= skyplane;
                renderer->flushUpdate();
                sky.draw(renderer);
                renderer->flushBatch();

                renderer->far_plane /= skyplane;
                renderer->disableShadows = false;
        }
}

void Map::draw(Renderer *renderer)
{
        this->renderer = renderer;

        //gamePrint("sr "+to_string(shadowRender));
        if (shadowRender) {
                shadowRender = false;
                drawShadows(renderer);
        }
        //drawShadows(renderer);
        renderer->flushUpdate();

        drawObjs(renderer);
}

void Map::mapParser()
{
        lights.clear();
        sky.rendered = false;

        std::vector<std::string> words = fileLexer(mapPath);

        for (int i = 0; i < words.size() && *running; ++i) {
                mapCmd(words, i, this);
        }
        reloading = false;
}

void Map::tickPhysics()
{
        physSys.field = gravity;

        if (physicsEnabled && physadded) {
                physSys.update();
        }

        if (!thisPlayer->flying && physadded) thisPlayer->collide(&physSys);
}
