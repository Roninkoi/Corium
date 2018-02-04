#version 330
#extension GL_ARB_geometry_shader4:enable

layout (location = 0) in vec4 position;

uniform mat4 model;

void main()
{
    gl_Position = model * vec4(position.xyz, 1.0f);
}
