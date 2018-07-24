#version 330
//#extension GL_EXT_geometry_shader4 : enable
//#extension GL_ARB_explicit_attrib_location : enable

in vec4 FragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main()
{
    float lightDistance = length(FragPos.xyz - lightPos);

    lightDistance = lightDistance / far_plane;

    gl_FragDepth = lightDistance;
}
