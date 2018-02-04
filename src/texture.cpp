//
// Created by Roni A. Koitermaa on 20.12.2015.
//

#include "texture.h"

#include <texture.h>
#include <SOIL/SOIL.h>

GLuint Texture::loadTexture(std::string path)
{
    GLuint texture_id;

    this->path = path;

    glGenTextures(1, &texture_id);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    unsigned char * image;

    image = SOIL_load_image(path.c_str(), &w, &h, 0, SOIL_LOAD_RGBA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    SOIL_free_image_data(image);

    glDeleteTextures(1, &tex);
    tex = texture_id;

    return texture_id;
}
