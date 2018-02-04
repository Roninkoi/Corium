//
// Created by Roni A. Koitermaa on 18.12.2015.
//
#include <util/objParser.h>
#include "obj.h"

void Obj::update()
{
        phys.m = pow(fabs(physMesh.boundingSphereRadius), 2)*0.75f*M_PI + 1.0f;

        phys.update();

        updateMesh();
}

void Obj::updateMesh()
{
        // Transform mesh according to phys
        mesh.objMatrix = phys.getRMatrix();
        if (!ro) {
                mesh.update();
        }
        physMesh.objMatrix = phys.getMatrix();
        physMesh.update();
}

void Obj::draw(Renderer *renderer)
{
        if (!ro)
                mesh.draw(renderer, &tex);
        else
                render(renderer);
}

void Obj::render(Renderer *renderer)
{
        mesh.render(renderer, &tex);
}

void Obj::drawShadows(Renderer *renderer)
{
        if (!ro)
                mesh.drawShadows(renderer);
        else
                renderShadows(renderer);
}

void Obj::renderShadows(Renderer *renderer)
{
        mesh.renderShadows(renderer);
}

void Obj::loadMesh(std::string sp, std::string pp)
{
        if (pp == "")
                pp = sp;

        mesh = loadObj(sp);
        physMesh = loadObj(pp);
}

void Obj::loadObject(std::string tp, std::string sp, std::string pp)
{
        loadMesh(sp, pp);
        tex.loadTexture(tp);
}
