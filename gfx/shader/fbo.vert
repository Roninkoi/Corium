#version 330

/*layout(location = 0) */in vec4 a_pos;
/*layout(location = 1) */in vec4 a_tex;

out vec4 v_pos;
out vec2 v_tex;

void main()
{
  gl_Position = vec4(a_pos.xyz, 1.0f);

  v_tex = vec2(a_tex.s*a_tex.p, a_tex.t*a_tex.q);
  v_pos = a_pos;
}
