//
// Created by Roni A. Koitermaa on 20.12.2015.
//

#ifndef CORIUM_TEXTURE_H
#define CORIUM_TEXTURE_H

#include "crm.h"
#include <SOIL/SOIL.h>

class Texture {
public:
std::string path = "";

int w = 0, h = 0;

GLuint tex = 0;

GLuint loadTexture(std::string path);

Texture()
{
        path = "";
}
/*
    ~Texture()
    {
        //glDeleteTextures(1, &tex);
    }*/
};

#endif //CORIUM_TEXTURE_H
