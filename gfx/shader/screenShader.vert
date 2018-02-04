#version 330

/*layout(location = 0)*/ in vec4 a_pos;
/*layout(location = 1)*/ in vec4 a_tex;
/*layout(location = 2)*/ in vec4 a_col;

out vec2 v_tex;
out vec4 v_col;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection*view*model*vec4(a_pos.xyz, 1.0f);
    v_tex = vec2(a_tex.s*a_tex.p, a_tex.t*a_tex.q);
    v_col = a_col;
}
