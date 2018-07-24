//
// Created by Ronin748 on 21.12.2015.
//

#ifndef CORIUM_MAP_H
#define CORIUM_MAP_H

#include <crm.h>
#include <quad.h>
#include <render/renderer.h>
#include <game/entity/player.h>
#include <util/randomRange.h>
#include <physSys.h>
#include <math.h>
#include <game/obj/obj.h>
#include <util/objParser.h>
#include <audio.h>
#include "gen.h"
#include <anim.h>
#include <game/obj/camera.h>

template<typename T>
std::vector<T>* clearVector(std::vector<T>* vec)
{
        std::vector<T>().swap(*vec);
        return vec;
}

class Map {
public:
std::vector<Player> player;
Player *thisPlayer;
int playerID;

std::string mapPath = "";

std::string mapName = "";

float ticks = 0.0f;

Renderer *renderer;

Camera *camera;

Audio *aud;

bool *running;

PhysSys physSys;
bool physicsEnabled = true;
bool physadded = false;

bool shadowRender = false;
bool shadowsEnabled = true;

std::vector<Texture> textures;

std::vector<Obj> objs;
std::vector<Obj> environs;

Obj sky;     // skybox
float skyplane = 1.0f;

std::vector<Light> lights;

glm::vec3 gravity = glm::vec3(0.0f, -0.005f, 0.0f);

bool inRange(glm::vec3 bsc, float bsr);

bool inRange(Obj *object);

bool visible(Obj *object);

void tickPhysics();

void draw(Renderer *renderer);

void drawObjs(Renderer *renderer);

void drawShadows(Renderer *renderer);

void update();

Player *getPlayer()
{
        playerID = 0;
        thisPlayer = &player[playerID];

        return thisPlayer;
}

Camera* getCamera()
{
        return camera;
}

void start(Renderer *renderer, Audio *aud, bool *running)
{
        this->renderer = renderer;
        this->aud = aud;
        this->running = running;

        getPlayer();
}

void reload(Renderer *renderer)
{
        physSys.finish();

        clearVector(&objs);
        clearVector(&environs);

        //for (int i = 0; i < textures.size(); ++i)
        //        textures[i].deleteTexture();

        //clearVector(&textures);

        clearLights(renderer);

        mapParser();

        //thisPlayer->restartPlayer();

        addPhysObjects();

        baked = false;
}

float newobjmass = 0.0f;

void addObj(std::string s, std::string p, std::string t, glm::vec3 pos,
            glm::vec3 rot, glm::vec3 scale, bool st, bool ph)
{
        if (ph) {
                int i = objs.size();

                objs.resize(i + 1);

                objs[i].loadMesh(s, p);

                // check if texture is already loaded
                int fi = -1;
                for (int ti = 0; ti < textures.size() && fi < 0; ++ti) {
                        if (textures[ti].path == t) {
                                fi = ti;
                        }
                }
                if (fi < 0) {
                        textures.resize(textures.size() + 1);
                        fi = textures.size() - 1;
                        textures[fi].loadTexture(t.c_str());
                }
                objs[i].tex = textures[fi];


                objs[i].phys.pos = glm::vec3(pos.x, pos.y, pos.z);
                objs[i].phys.rot = rot;
                objs[i].phys.s = scale;
                objs[i].phys.v = glm::vec3(0.0f);

                objs[i].phys.isStatic = st;

                if (!objs[i].phys.isStatic) {
                        objs[i].phys.v = normalize(gravity)*2.0f*PHYS_EPSILON;
                        objs[i].phys.sv = normalize(gravity)*2.0f*PHYS_EPSILON;
                }
                objs[i].update();
                objs[i].physMesh.triangleSizeCheck();

                if (newobjmass > 0.0f)
                        objs[i].phys.m = newobjmass;
                else {
                        objs[i].phys.m = pow(fabs(objs[i].physMesh.boundingSphereRadius), 2)*0.75f*M_PI + 1.0f;
                }
                objs[i].phys.I = objs[i].phys.m*objs[i].physMesh.boundingSphereRadius*objs[i].physMesh.boundingSphereRadius*0.3f;

                if (objs[i].mesh.indexBufferData.size() > BATCH_SIZE * 0.1f)
                        objs[i].ro = true;
        }
        else {
                int i = environs.size();

                environs.resize(i + 1);
                i = environs.size() - 1;
                environs[i].loadMesh(s); // true -> false ???

                int fi = -1;
                for (int ti = 0; ti < textures.size() && fi < 0; ++ti) {
                        if (textures[ti].path == t) {
                                fi = ti;
                        }
                }
                if (fi < 0) {
                        textures.resize(textures.size() + 1);
                        fi = textures.size() - 1;
                        textures[fi].loadTexture(t.c_str());
                }
                environs[i].tex = textures[fi];

                environs[i].phys.pos = glm::vec3(pos.x, pos.y, pos.z);
                environs[i].phys.rot = rot;
                environs[i].phys.s = scale;
                environs[i].phys.v = glm::vec3(0.0f);

                environs[i].phys.isStatic = st;

                environs[i].update();
        }
        gameRefresh();
}

void addPhysObjects()
{
        physSys.objects.resize(objs.size());
        for (int j = 0; j < objs.size(); ++j) {
                physSys.objects[j] = &objs[j];
        }
}

void clearLights(Renderer *renderer)
{
        for (int l = 0; l < renderer->MAX_LIGHTS; ++l) {
                renderer->lights[l].col = glm::vec3(0.0f);
        }
}

int lightNum = 0;

std::vector<int> closestLights;

void findLights()
{
        closestLights.resize(renderer->MAX_LIGHTS);
        std::fill(closestLights.begin(), closestLights.end(), -1);

        lightNum = 0;
        bool found = true;

        for (int i = 0; i < renderer->MAX_LIGHTS && found; ++i) {
                float closestDist = renderer->far_plane; // lights within zfar
                int closestJ = 0;
                found = false;

                for (int j = 0; j < lights.size(); ++j) {
                        float dist = glm::length((player[playerID].phys.pos) - lights[j].pos);

                        bool included = false;
                        for (int k = 0; k < renderer->MAX_LIGHTS; ++k) {
                                if (closestLights[k] == j) {
                                        included = true;
                                }
                        }

                        if (dist < closestDist && !included && glm::length(lights[j].col) > 0.0f) {
                                closestDist = dist;
                                closestJ = j;
                                found = true;
                        }
                }
                if (found) {
                        if (shadowsEnabled) {
                                renderer->lights[i].pos = lights[closestJ].pos;
                                renderer->lights[i].col = lights[closestJ].col;
                        }
                        else {
                                renderer->lights[i] = lights[closestJ];
                        }
                        closestLights[i] = closestJ;
                        ++lightNum;
                }
        }
}

void mapParser();

void load(Renderer *renderer)
{
        gamePrint("loading map " + mapPath + "...\n");
        thisPlayer->loadPlayer();

        thisPlayer->camera = camera;

        clearLights(renderer);

        mapParser();

        thisPlayer->restartPlayer();

        addPhysObjects();

        baked = false;
}

// are shadows 420
bool baked = false;
void bakeShadows();

void restart()
{
        thisPlayer->restartPlayer();
}

void quit()
{
        physSys.finish();
}

Map()
{
        playerID = 0;
        player.resize(1);
        player[0] = Player();

        camera = new Camera();

        ticks = 0;
}
};

#endif //CORIUM_MAP_H
