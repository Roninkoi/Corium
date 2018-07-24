//
// Created by Ronin748 on 18.12.2015.
//

#include "renderer.h"

void Renderer::destroyRenderer()
{
        quadShader.destroyShader();
        PS_Shader.destroyShader();
        PS_ShaderDepth.destroyShader();

        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &texBuffer);
        glDeleteBuffers(1, &colBuffer);
        glDeleteBuffers(1, &normalBuffer);
        glDeleteBuffers(1, &indexBuffer);
        glDeleteBuffers(1, &quadBuf);
        glDeleteBuffers(1, &indBuf);

        glDeleteVertexArrays(1, &vertexArrayID);
        glDeleteTextures(1, &screenTex);
        glDeleteTextures(1, &screenDepthTex);
        glDeleteFramebuffers(1, &screenFBO);
}

void Renderer::compileShaders()
{
        PS_Shader.max_lights = MAX_LIGHTS;

        quadShader.init("gfx/shader/fbo.vert", "gfx/shader/fbo.frag", loadShaders);
        PS_Shader.init("gfx/shader/pointShadow.vert", "gfx/shader/pointShadow.frag", loadShaders);

        PS_ShaderDepth.initGS("gfx/shader/pointShadowDepth.vert",
                              "gfx/shader/pointShadowDepth.frag",
                              "gfx/shader/pointShadowDepth.gs", loadShaders);
}

void Renderer::init()
{
        max_lights = MAX_LIGHTS;
        lights.resize(MAX_LIGHTS);

        compileShaders();

        glUseProgram(PS_Shader.program);

        glGenVertexArrays(1, &vertexArrayID);
        glBindVertexArray(vertexArrayID);

        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &texBuffer);
        glGenBuffers(1, &colBuffer);
        glGenBuffers(1, &normalBuffer);
        glGenBuffers(1, &indexBuffer);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glDisable(GL_STENCIL_TEST);
        glEnable(GL_CULL_FACE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glUniform1i(glGetUniformLocation(PS_Shader.program, "diffuseTexture"), 0);
//    glUniform1i(glGetUniformLocation(PS_Shader.program, "depthMap"), 1);

        for (int l = 0; l < MAX_LIGHTS; ++l)
                lights[l].initShadows(SHADOW_WIDTH, SHADOW_HEIGHT);

        printf("SCREEN WIDTH: %s%s%s%s", &to_string(SCREEN_WIDTH)[0], " SCREEN HEIGHT: ", &to_string(SCREEN_HEIGHT)[0],
               "\n");

        // SCREEN FBO
        glGenTextures(1, &screenTex);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, screenTex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

        glGenFramebuffers(1, &screenFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);

        glGenTextures(1, &screenDepthTex);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, screenDepthTex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_DEPTH_COMPONENT,
                     GL_UNSIGNED_BYTE, 0);

        gamePrint("st " + to_string(screenTex) + "\n");
        gamePrint("sd t " + to_string(screenDepthTex) + "\n");

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTex, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, screenDepthTex, 0);

        // glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, screenTex, 0);
        // glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, screenDepthTex, 0);

        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers);

        glGenBuffers(1, &quadBuf);
        glGenBuffers(1, &indBuf);

        auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
                gamePrint("Framebuffer not complete: " + to_string(fboStatus) + "\n");


        gamePrint("FBO id: " + to_string(screenFBO) + "\n");
}

void Renderer::clear()
{
        glClearColor(clr_col.r, clr_col.g, clr_col.b, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::update()
{
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        clear();

        glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);

        clear();

        cMatrix = glm::mat4(1.0f);
        pMatrix = glm::mat4(1.0f);

        pMatrix = glm::perspective(fov, (float) w / (float) h, 0.05f, far_plane);

        //glViewport(0, 0, w, h);

        cMatrix = glm::translate(cMatrix, glm::vec3(0.0f, 0.0f, -camZ)); // for 3rd person

        cMatrix = glm::rotate(cMatrix, camRot.y, glm::vec3(0.0f, 1.0f, 0.0f));
        cMatrix = glm::rotate(cMatrix, camRot.x, glm::vec3(cos(camRot.y), 0.0, sin(camRot.y)));

        cMatrix = glm::translate(cMatrix, camPos);
}

void Renderer::batchAdd(Texture *tex, std::vector<float> *vertexData, std::vector<float> *normalData,
                        std::vector<float> *texData,
                        std::vector<float> *colData, std::vector<int> *indexData)
{
        if (buffer_vertices + vertexData->size() >= BATCH_SIZE ||
            buffer_indices + indexData->size() >= BATCH_SIZE || (tex->path != this->tex.path)) {
                flushBatch();
        }

        vertices = buffer_vertices / 4;

        for (unsigned int i = 0; i < vertexData->size(); ++i) {
                vertexBufferArray[buffer_vertices] = (vertexData->at(i));
                texBufferArray[buffer_vertices] = (texData->at(i));
                colBufferArray[buffer_vertices] = (colData->at(i));
                normalBufferArray[buffer_vertices] = (normalData->at(i));
                ++buffer_vertices;
        }

        for (unsigned int i = 0; i < indexData->size(); ++i) {
                indexBufferArray[buffer_indices] = indexData->at(i) + vertices;
                ++buffer_indices;
        }

        this->tex = *tex;
}

void Renderer::draw(Texture *tex, std::vector<float> *vertexData, std::vector<float> *normalData,
                    std::vector<float> *texData,
                    std::vector<float> *colData, std::vector<int> *indexData)
{
        ++drawsPerCycle;

        if (vertexData->size() < BATCH_SIZE && indexData->size() < BATCH_SIZE) {
                batchAdd(tex, vertexData, normalData, texData, colData, indexData);
        }
        else {
                //flushBatch();
                render(tex, &uMatrix, vertexData, normalData, texData, colData, indexData);
        }
}

// flush batch and render FBO
void Renderer::flushBatchFBO()
{
        flushBatch();
        if (!rfbo) renderFBO();
}

void Renderer::flushUpdate()
{
        if (rfbo) {
                glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
                SCREEN_WIDTH = w;
                SCREEN_HEIGHT = h;
        }
        else {
                glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);
                SCREEN_WIDTH = 256 * 2 * SCREEN_SCALE;
                SCREEN_HEIGHT = 150 * 2 * SCREEN_SCALE;
        }

        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glUseProgram(PS_Shader.program);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glDisable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
        //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);

        //glDepthFunc(GL_LEQUAL); // changed from GL_LESS
        glDepthFunc(GL_LESS);
        glCullFace(GL_BACK);

        glUniform2fv(glGetUniformLocation(PS_Shader.program, "ws"), 1,
                     &(glm::vec2((float) SCREEN_WIDTH, (float) SCREEN_HEIGHT))[0]);

        glUniform1f(glGetUniformLocation(PS_Shader.program, "far_plane"), far_plane);

        glUniform1f(glGetUniformLocation(PS_Shader.program, "dither"), (float) dithering);

        GLuint sampleTex = glGetUniformLocation(PS_Shader.program, "diffuseTexture");
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex.tex);
        glUniform1i(sampleTex, 0);

        glUniform3fv(glGetUniformLocation(PS_Shader.program, "fogCol"), 1, &(clr_col)[0]);
        glUniform2fv(glGetUniformLocation(PS_Shader.program, "al"), 1, &(glm::vec2(this->amb, this->lght))[0]);


        for (int l = 0; l < max_lights; ++l) {
                glUniform3fv(glGetUniformLocation(PS_Shader.program, ("lights[" + to_string(l) + "].pos").c_str()), 1,
                             (const float *) glm::value_ptr(lights[l].pos));
                glUniform3fv(glGetUniformLocation(PS_Shader.program, ("lights[" + to_string(l) + "].col").c_str()), 1,
                             &(lights[l].col*((float)shadows))[0]);

                GLuint depthTex = glGetUniformLocation(PS_Shader.program, ("depthMap[" + to_string(l) + "]").c_str());

                glActiveTexture((GLenum) (GL_TEXTURE1 + l));
                glBindTexture(GL_TEXTURE_CUBE_MAP, lights[l].depthCubemap);
                glUniform1i(depthTex, 1 + l);
        }

        glUniform1i(glGetUniformLocation(PS_Shader.program, "max_lights"), max_lights);

        glUniformMatrix4fv(glGetUniformLocation(PS_Shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(pMatrix));
        glUniformMatrix4fv(glGetUniformLocation(PS_Shader.program, "view"), 1, GL_FALSE, glm::value_ptr(cMatrix));
        glUniformMatrix4fv(glGetUniformLocation(PS_Shader.program, "model"), 1, GL_FALSE, glm::value_ptr(uMatrix));

}

void Renderer::flush()
{
        ++batchesPerCycle;

        glBindVertexArray(vertexArrayID);

        glBindAttribLocation(PS_Shader.program, 0, "position");
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
                0,
                4,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) 0
                );

        glBindAttribLocation(PS_Shader.program, 1, "normal");
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glVertexAttribPointer(
                1,
                4,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) 0
                );

        glBindAttribLocation(PS_Shader.program, 2, "texCoords");
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
        glVertexAttribPointer(
                2,
                4,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) 0
                );

        glBindAttribLocation(PS_Shader.program, 3, "col");
        glEnableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, colBuffer);
        glVertexAttribPointer(
                3,
                4,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) 0
                );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);


        glDrawElements(GL_TRIANGLES,
                       buffer_indices, GL_UNSIGNED_INT,
                       (void *) 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);

        buffer_indices = 0;
        buffer_vertices = 0;

        uMatrix = glm::mat4(1.0f);
}
bool rezzing = false;
void Renderer::render(Texture *tex, glm::mat4 *objMatrix, std::vector<float> *vertexData,
                      std::vector<float> *normalData,
                      std::vector<float> *texData,
                      std::vector<float> *colData, std::vector<int> *indexData)
{
        flushBatch();

        buffer_vertices = vertexData->size();
        buffer_indices = indexData->size();
        uMatrix = *objMatrix;
        this->tex = *tex;

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), &(*vertexData)[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
        glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), &(*texData)[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), &(*normalData)[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, colBuffer);
        glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), &(*colData)[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_indices * sizeof(int), &(*indexData)[0], GL_DYNAMIC_DRAW);

        /*glActiveTexture(GL_TEXTURE0);
           glBindTexture(GL_TEXTURE_2D, this->tex.tex);*/

        flushUpdate();

        flush();
}

void Renderer::drawLine(glm::vec3 l0, glm::vec3 l1)
{
        flushBatch();

        uMatrix = glm::mat4(1.0f);

        std::vector<float> vertexData = {l0.x, l0.y, l0.z, 1.0f, l1.x, l1.y, l1.z, 1.0f};
        std::vector<float> normalData = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
        std::vector<float> texData = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
        std::vector<float> colData = {20.0f, 0.0f, 0.0f, 1.0f, 20.0f, 0.0f, 20.0f, 1.0f};
        std::vector<int> indexData = {0, 1, 0, 1, 0, 1};
        //render(&tex, &uMatrix, &vertexData, &normalData,&texData,&colData,&indexData);
        buffer_vertices = vertexData.size();
        buffer_indices = indexData.size();

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), &(vertexData)[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
        glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), &(texData)[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), &(normalData)[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, colBuffer);
        glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), &(colData)[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_indices * sizeof(int), &(indexData)[0], GL_DYNAMIC_DRAW);

        /*glActiveTexture(GL_TEXTURE0);
           glBindTexture(GL_TEXTURE_2D, this->tex.tex);*/


        /*glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

           glEnable(GL_POLYGON_OFFSET_LINE);

           glPolygonOffset(0.0f, -500.0f);*/

        flushUpdate();

        glBindVertexArray(vertexArrayID);

        glBindAttribLocation(PS_Shader.program, 0, "position");
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
                0,
                4,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) 0
                );

        glBindAttribLocation(PS_Shader.program, 1, "normal");
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glVertexAttribPointer(
                1,
                4,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) 0
                );

        glBindAttribLocation(PS_Shader.program, 2, "texCoords");
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
        glVertexAttribPointer(
                2,
                4,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) 0
                );

        glBindAttribLocation(PS_Shader.program, 3, "col");
        glEnableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, colBuffer);
        glVertexAttribPointer(
                3,
                4,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) 0
                );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

        glLineWidth(8.0f);

        glDrawElements(GL_LINES,
                       buffer_indices, GL_UNSIGNED_INT,
                       (void *) 0);

        glLineWidth(1.0f);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);

        buffer_indices = 0;
        buffer_vertices = 0;

        uMatrix = glm::mat4(1.0f);

        if (!rfbo) renderFBO();

        //flush();

        /*glPolygonOffset(0.0f, 0.0f);

           glEnable(GL_POLYGON_OFFSET_LINE);

           glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);*/
}

void Renderer::flushBatch()
{
        if (buffer_indices > 2) {
                uMatrix = glm::mat4(1.0f);

                glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
                glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), vertexBufferArray, GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
                glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), texBufferArray, GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
                glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), normalBufferArray, GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, colBuffer);
                glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), colBufferArray, GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_indices * sizeof(int), indexBufferArray, GL_DYNAMIC_DRAW);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, this->tex.tex);

                //   if (rezzing)
                //        flushUpdate(); //dont

                glm::mat4 oldum = uMatrix;
                int bv = buffer_vertices;
                int bi = buffer_indices;

                flush();

                if (drawLines) {
                        uMatrix = oldum;
                        buffer_vertices = bv;
                        buffer_indices = bi;

                        glBindBuffer(GL_ARRAY_BUFFER, colBuffer);
                        for (int i = 0; i < buffer_vertices; i += 1) {
                                colBufferArray[i] = 0.0f;
                        }
                        glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), colBufferArray, GL_DYNAMIC_DRAW);

                        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

                        glEnable(GL_POLYGON_OFFSET_LINE);

                        glPolygonOffset(0.0f, -500.0f);

                        flush();

                        glPolygonOffset(0.0f, 0.0f);

                        glEnable(GL_POLYGON_OFFSET_LINE);

                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                }
        }
}

void Renderer::drawShadows(std::vector<float> *vertexData, std::vector<int> *indexData)
{
        if (vertexData->size() < BATCH_SIZE && indexData->size() < BATCH_SIZE) {
                addShadows(vertexData, indexData);
        }
        else {
                renderShadows(&uMatrix, vertexData, indexData);
        }
}

void Renderer::addShadows(std::vector<float> *vertexData, std::vector<int> *indexData)
{
        if ((buffer_vertices + vertexData->size() >= BATCH_SIZE ||
             buffer_indices + indexData->size() >= BATCH_SIZE)) {
                flushShadows();
        }

        int vertices = buffer_vertices / 4;

        for (unsigned int i = 0; i < vertexData->size(); ++i) {
                vertexBufferArray[buffer_vertices] = (vertexData->at(i));
                ++buffer_vertices;
        }

        for (unsigned int i = 0; i < indexData->size(); ++i) {
                indexBufferArray[buffer_indices] = indexData->at(i) + vertices;
                ++buffer_indices;
        }
}

void Renderer::flushShadows()
{
        uMatrix = glm::mat4(1.0f);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), vertexBufferArray, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_indices * sizeof(int), indexBufferArray, GL_DYNAMIC_DRAW);

        drawShadowMap();
}

void Renderer::renderShadows(glm::mat4 *objMatrix, std::vector<float> *vertexData, std::vector<int> *indexData)
{
        flushShadows();

        buffer_vertices = vertexData->size();
        buffer_indices = indexData->size();
        uMatrix = *objMatrix;

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), &(*vertexData)[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_indices * sizeof(int), &(*indexData)[0], GL_DYNAMIC_DRAW);

        drawShadowMap();
}

void Renderer::clearShadows()
{
        for (int l = 0; l < max_lights; ++l) {
                glBindFramebuffer(GL_FRAMEBUFFER, lights[l].depthMapFBO);
                clear();
        }
}

void Renderer::drawShadowMap()
{
        //++batchesPerCycle; // count shadows too?

        GLfloat aspect = ((GLfloat) SHADOW_WIDTH) / ((GLfloat) SHADOW_HEIGHT);
        GLfloat near = 0.3f;
        GLfloat far = far_plane;
        glm::mat4 shadowProj = glm::perspective((float) (M_PI / 2.0f), aspect, near, far);

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

        glUseProgram(PS_ShaderDepth.program);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glDepthFunc(GL_LESS);

        glUniform1f(glGetUniformLocation(PS_ShaderDepth.program, "far_plane"), far);

        glUniformMatrix4fv(glGetUniformLocation(PS_ShaderDepth.program, "model"), 1, GL_FALSE,
                           (const float *) glm::value_ptr(uMatrix));
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void *) 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

        for (light_i = 0; light_i < max_lights; ++light_i) {
                std::vector<glm::mat4> shadowTransforms;
                shadowTransforms.push_back(
                        shadowProj * glm::lookAt(lights[light_i].pos, lights[light_i].pos + glm::vec3(1.0, 0.0, 0.0),
                                                 glm::vec3(0.0, -1.0, 0.0)));
                shadowTransforms.push_back(
                        shadowProj * glm::lookAt(lights[light_i].pos, lights[light_i].pos + glm::vec3(-1.0, 0.0, 0.0),
                                                 glm::vec3(0.0, -1.0, 0.0)));
                shadowTransforms.push_back(
                        shadowProj * glm::lookAt(lights[light_i].pos, lights[light_i].pos + glm::vec3(0.0, 1.0, 0.0),
                                                 glm::vec3(0.0, 0.0, 1.0)));
                shadowTransforms.push_back(
                        shadowProj * glm::lookAt(lights[light_i].pos, lights[light_i].pos + glm::vec3(0.0, -1.0, 0.0),
                                                 glm::vec3(0.0, 0.0, -1.0)));
                shadowTransforms.push_back(
                        shadowProj * glm::lookAt(lights[light_i].pos, lights[light_i].pos + glm::vec3(0.0, 0.0, 1.0),
                                                 glm::vec3(0.0, -1.0, 0.0)));
                shadowTransforms.push_back(
                        shadowProj * glm::lookAt(lights[light_i].pos, lights[light_i].pos + glm::vec3(0.0, 0.0, -1.0),
                                                 glm::vec3(0.0, -1.0, 0.0)));

                glBindFramebuffer(GL_FRAMEBUFFER, lights[light_i].depthMapFBO);

                for (GLuint i = 0; i < 6; ++i)
                        glUniformMatrix4fv(
                                glGetUniformLocation(PS_ShaderDepth.program,
                                                     ("shadowTransforms[" + to_string(i) + "]").c_str()), 1,
                                GL_FALSE, glm::value_ptr(shadowTransforms[i]));

                glUniform3fv(glGetUniformLocation(PS_ShaderDepth.program, "lightPos"), 1,
                             (const float *) glm::value_ptr(lights[light_i].pos));
/*
        glDrawRangeElements(GL_TRIANGLES, 0, buffer_vertices - 1, buffer_indices, GL_UNSIGNED_INT,
                            (void *) 0);*/

                glDrawElements(GL_TRIANGLES,
                               buffer_indices, GL_UNSIGNED_INT,
                               (void *) 0);
        }

        glDisableVertexAttribArray(0);

        buffer_indices = 0;
        buffer_vertices = 0;
}
int screenshots = 0;
void Renderer::renderFBO()
{

        float verts[32] = {
                0.0f, -1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f, -1.0f,
                1.0f, 1.0f, -1.0f, -1.0f,
                0.0f, 1.0f, -1.0f, -1.0f,

                -1.0f, -1.0f, -1.0f, -1.0f,
                0.0f, -1.0f, -1.0f, -1.0f,
                0.0f, 1.0f, -1.0f, -1.0f,
                -1.0f, 1.0f, -1.0f, -1.0f
        };

        float x0 = -this->xSpacing;
        float x1 = this->xSpacing;

        float w0 = 0.0f;
        float w1 = 0.0f;

        float texcoords[32] = {
                (0.0f + 1.0f) / 2.0f + x0, (-1.0f + 1.0f) / 2.0f, 1.0f + w0, 1.0f,
                (1.0f + 1.0f) / 2.0f + x0, (-1.0f + 1.0f) / 2.0f, 1.0f + w0, 1.0f,
                (1.0f + 1.0f) / 2.0f + x0, (1.0f + 1.0f) / 2.0f, 1.0f + w0, 1.0f,
                (0.0f + 1.0f) / 2.0f + x0, (1.0f + 1.0f) / 2.0f, 1.0f + w0, 1.0f,

                (-1.0f + 1.0f) / 2.0f + x1, (-1.0f + 1.0f) / 2.0f, 1.0f + w1, 1.0f,
                (0.0f + 1.0f) / 2.0f + x1, (-1.0f + 1.0f) / 2.0f, 1.0f + w1, 1.0f,
                (0.0f + 1.0f) / 2.0f + x1, (1.0f + 1.0f) / 2.0f, 1.0f + w1, 1.0f,
                (-1.0f + 1.0f) / 2.0f + x1, (1.0f + 1.0f) / 2.0f, 1.0f + w1, 1.0f
        };
        int indices[12] = {
                0, 1, 2,
                0, 2, 3,
                4, 5, 6,
                4, 6, 7
        };

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        clear();

        glViewport(0, 0, w, h);

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        /*glDisable(GL_BLEND);

           glDisable(GL_DEPTH_TEST);*/
        glDisable(GL_CULL_FACE);

        glUseProgram(quadShader.program);
/*
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, screenTex);*/

        GLuint sampleTex = glGetUniformLocation(quadShader.program, "tex");

        glUniform1i(sampleTex, 0);
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, screenTex);

        glBindBuffer(GL_ARRAY_BUFFER, quadBuf);
        glBufferData(GL_ARRAY_BUFFER, 4 * 4 * 2 * sizeof(float), verts, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
        glBufferData(GL_ARRAY_BUFFER, 4 * 4 * 2 * sizeof(float), texcoords, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuf);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * 2 * sizeof(int), indices, GL_DYNAMIC_DRAW);

        glBindAttribLocation(quadShader.program, 0, "a_pos");
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, quadBuf);
        glVertexAttribPointer(
                0,
                4,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) 0
                );
        glBindAttribLocation(quadShader.program, 1, "a_tex");
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
        glVertexAttribPointer(
                1,
                4,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) 0
                );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuf);
/*
    glDrawRangeElements(GL_TRIANGLES, 0, 12, 12, GL_UNSIGNED_INT,
                        (void *) 0);*/

        glDrawElements(GL_TRIANGLES,
                       12, GL_UNSIGNED_INT,
                       (void *) 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        buffer_indices = 0;
        buffer_vertices = 0;

        uMatrix = glm::mat4(1.0f);
}
