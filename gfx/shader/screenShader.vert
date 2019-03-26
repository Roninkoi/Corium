#version 140

/*layout(location = 0)*/ in vec4 aPos;
/*layout(location = 1)*/ in vec4 aTex;
/*layout(location = 2)*/ in vec4 a_col;

out vec2 vTex;
out vec4 v_col;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection*view*model*vec4(aPos.xyz, 1.0f);
    vTex = vec2(aTex.s*aTex.p, aTex.t*aTex.q);
    v_col = a_col;
}
