#version 150

precision lowp int;
precision lowp float;

/*layout (location = 0) */in vec4 position;
/*layout (location = 1) */in vec4 normal;
/*layout (location = 2) */in vec4 texPos;
/*layout (location = 3) */in vec4 col;

out vec3 fragPos;
out vec3 fnormal;
out vec2 ftexPos;
out vec4 fragCol;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(position.xyz, 1.0f);
    fragPos = vec3(model * position);
    fnormal = transpose(inverse(mat3(model))) * (normal.xyz);
    //normal = mat3(model) * (normal.xyz);
    ftexPos = vec2((texPos.s)*texPos.p, (texPos.t)*texPos.q);
    fragCol = col;
}
