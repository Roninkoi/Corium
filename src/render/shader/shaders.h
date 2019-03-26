
std::string fbovert ="\n"
                      "\n";
std::string fbofrag = "\n"
                      "\n";

std::string pointShadowfrag = "\n"
                              "\n";

std::string pointShadowvert = "\n"
                              "\n";

std::string pointShadowDepthfrag = "#version 330 core\n"
                                   "in vec4 fragPos;\n"
                                   "\n"
                                   "uniform vec3 lightPos;\n"
                                   "uniform float farPlane;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    float lightDistance = length(fragPos.xyz - lightPos);\n"
                                   "\n"
                                   "    lightDistance = lightDistance / farPlane;\n"
                                   "\n"
                                   "    gl_FragDepth = lightDistance;\n"
                                   "}";
std::string pointShadowDepthvert = "#version 330 core\n"
                                   "layout (location = 0) in vec4 position;\n"
                                   "\n"
                                   "uniform mat4 model;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    gl_Position = model * vec4(position.xyz, 1.0f);\n"
                                   "}";
std::string pointShadowDepthgs = "#version 330 core\n"
                                 "layout (triangles) in;\n"
                                 "layout (triangle_strip, max_vertices=18) out;\n"
                                 "\n"
                                 "uniform mat4 shadowTransforms[6];\n"
                                 "\n"
                                 "out vec4 fragPos;\n"
                                 "\n"
                                 "void main()\n"
                                 "{\n"
                                 "    for(int face = 0; face < 6; ++face)\n"
                                 "    {\n"
                                 "        gl_Layer = face;\n"
                                 "        for(int i = 0; i < 3; ++i)\n"
                                 "        {\n"
                                 "            fragPos = gl_in[i].gl_Position;\n"
                                 "            gl_Position = shadowTransforms[face] * fragPos;\n"
                                 "            EmitVertex();\n"
                                 "        }\n"
                                 "        EndPrimitive();\n"
                                 "    }\n"
                                 "}";


std::string screenShaderfrag = "\n"
                               "\n";
std::string screenShadervert = "\n"
                               "\n";
