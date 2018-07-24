//
// Created by Roni A. Koitermaa on 20.12.2015.
//

#define STB_IMAGE_IMPLEMENTATION

#include <texture.h>
#include <stb_image.h>

unsigned char* loadGLTex(std::string p, int* w, int* h)
{
        return stbi_load(p.c_str(), w, h, NULL, 4);
}

GLuint Texture::loadTexture(std::string path)
{
        //GLuint texture_id;

        this->path = path;

        glGenTextures(1, &tex);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);

        unsigned char * image;

        image = loadGLTex(path, &w, &h);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

        //glDeleteTextures(1, &tex);
        //tex = texture_id;
        delete image;

        return tex;
}
