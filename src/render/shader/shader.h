//
// Created by Ronin748 on 18.12.2015.
//

#ifndef CORIUM_SHADER_H
#define CORIUM_SHADER_H

#include <crm.h>
//#include "shadersrc.h" // this causes errors

class Shader {
public:
GLuint program;

GLuint VertexShaderID;
GLuint GeometryShaderID;
GLuint FragmentShaderID;

int max_lights = 8;

GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path, bool src);

GLuint loadGS(const char *vertex_file_path, const char *fragment_file_path, const char *gs_file_path, bool src);

void init(const char *vertPath, const char *fragPath, bool ls)
{
        program = loadShaders(vertPath, fragPath, !ls);
}

void initGS(const char *vertPath, const char *fragPath, const char *gsPath, bool ls)
{
        program = loadGS(vertPath, fragPath, gsPath, !ls);
}

void destroyShader()
{
        glDeleteProgram(program);
}

Shader()
{
}
};

#endif //CORIUM_SHADER_H
