#version 150

precision lowp int;
precision lowp float;

/*layout (location = 0) */in vec4 position;
/*layout (location = 1) */in vec4 normal;
/*layout (location = 2) */in vec4 texCoords;
/*layout (location = 3) */in vec4 col;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexPos;
out vec4 fragCol;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(position.xyz, 1.0f);
    FragPos = vec3(model * position);
    Normal = transpose(inverse(mat3(model))) * (normal.xyz);
    //Normal = mat3(model) * (normal.xyz);
    TexPos = vec2((texCoords.s)*texCoords.p, (texCoords.t)*texCoords.q);
    fragCol = col;
}
