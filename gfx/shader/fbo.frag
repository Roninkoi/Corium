#version 330

in vec4 v_pos;
in vec2 v_tex;

//layout(location = 0) out vec4 gl_FragColor;

uniform sampler2D tex;

void main()
{
/*float x = 410.0f*0.5f;
  gl_FragColor = vec4(texture(tex, vec2(floor(v_tex.x*x)/x, v_tex.y)).rgb, 1.0f) + vec4(texture(tex, vec2(floor(v_tex.x*x)/x+0.5f/x, v_tex.y)).rgb, 1.0f);
  gl_FragColor *= 0.5f;*/

  vec4 texCol = texture(tex, vec2(v_tex.x, v_tex.y));
  //texCol.rgb *= texCol.a;
  gl_FragColor = vec4(texCol.rgb, 1.0f);

}

