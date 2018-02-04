//
// Created by Roni A. Koitermaa on 18.12.2015.
//

#ifndef CORIUM_QUAD_H
#define CORIUM_QUAD_H

#include "mesh.h"
#include <texture.h>
#include "util/quadIsect.h"

class Quad : public Mesh {
public:
Texture tex;
Phys phys;

void update()
{
        objMatrix = phys.getMatrix();
        vertexBufferData = transform(rawVertexBufferData, objMatrix);
        getNormals();
        getBoundingSphere();
}

void draw(Renderer* renderer)
{
        renderer->draw(&tex, &vertexBufferData, &normalBufferData, &texBufferData, &colBufferData, &indexBufferData);
}

void loadSprite(std::string tex_path, glm::vec4 tex_sprite, bool load_tex = true)
{
        if (load_tex) {
                tex.loadTexture(tex_path);
        }
        float s_offs = (tex_sprite.s / (float) tex.w) * (tex.w / tex_sprite.p);
        float t_offs = (tex_sprite.t / (float) tex.h) * (tex.h / tex_sprite.q);

        float p_scale = tex_sprite.p / (float) tex.w;
        float q_scale = tex_sprite.q / (float) tex.h;

        texBufferData = {
                0.0f + s_offs, 0.0f + t_offs,
                p_scale, q_scale,
                1.0f + s_offs, 0.0f + t_offs,
                p_scale, q_scale,
                1.0f + s_offs, 1.0f + t_offs,
                p_scale, q_scale,
                0.0f + s_offs, 1.0f + t_offs,
                p_scale, q_scale
        };
}

Quad() : Mesh() {
        rawVertexBufferData.resize(16);
        texBufferData.resize(16);
        colBufferData.resize(16);
        indexBufferData.resize(6);
        normalBufferData.resize(6);

        rawVertexBufferData = {
                0.0f, 0.0f, 0.0f, 0.0f,//0
                1.0f, 0.0f, 0.0f, 0.0f,//1
                1.0f, 1.0f, 0.0f, 0.0f,//2
                0.0f, 1.0f, 0.0f, 0.0f//5
        };
        vertexBufferData = {
                0.0f, 0.0f, 0.0f, 0.0f,//0
                1.0f, 0.0f, 0.0f, 0.0f,//1
                1.0f, 1.0f, 0.0f, 0.0f,//2
                0.0f, 1.0f, 0.0f, 0.0f//5
        };

        indexBufferData = {
                0, 1, 2,
                0, 2, 3
        };

        texBufferData = {
                0.0f, 0.0f, 1.0f, 1.0f,//0
                1.0f, 0.0f, 1.0f, 1.0f,//1
                1.0f, 1.0f, 1.0f, 1.0f,//2
                0.0f, 1.0f, 1.0f, 1.0f//5
        };
        colBufferData = {
                1.0, 1.0, 1.0, 1.0,
                1.0, 1.0, 1.0, 1.0,
                1.0, 1.0, 1.0, 1.0,
                1.0, 1.0, 1.0, 1.0
        };
        normalBufferData = {
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f
        };
        getNormals();

        phys.update();
}
};


#endif //CORIUM_QUAD_H
