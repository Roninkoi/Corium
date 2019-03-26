#version 140

//layout(location = 0) out vec4 gl_FragColor;

in vec2 vTex;
in vec4 v_col;

uniform sampler2D tex;

void main() {
    gl_FragColor = texture(tex, vTex) * v_col;
}
