#version 140

/*layout(location = 0) */in vec4 aPos;
/*layout(location = 1) */in vec4 aTex;

out vec4 vPos;
out vec2 vTex;

void main()
{
  gl_Position = vec4(aPos.xyz, 1.0f);

  vTex = vec2(aTex.s*aTex.p, aTex.t*aTex.q);
  vPos = aPos;
}
