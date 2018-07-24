//
// Created by Roni A. Koitermaa on 22.8.2016.
//

#ifndef CORIUM_SCREENRENDERER_H
#define CORIUM_SCREENRENDERER_H

#include <render/renderer.h>
#include <render/shader/shader.h>

class ScreenRenderer {
public:
Shader screenShader;

GLuint *screenFBO;

int batchnum = 0;
int drawnum = 0;

bool loadShaders = true;
int rfbo = 0;

GLuint vertexArrayID;
GLuint vertexBuffer;
GLuint texBuffer;
GLuint colBuffer;
GLuint indexBuffer;

Texture tex;

float vertexBufferArray[BATCH_SIZE];
float texBufferArray[BATCH_SIZE];
float colBufferArray[BATCH_SIZE];
int indexBufferArray[BATCH_SIZE];

int buffer_vertices = 0;
int buffer_indices = 0;

glm::mat4 pMatrix = glm::mat4(1.0f);
glm::mat4 cMatrix = glm::mat4(1.0f);
glm::mat4 uMatrix = glm::mat4(1.0f);

GLuint u_pMatrix;
GLuint u_cMatrix;
GLuint u_uMatrix;

int w, h = 0;
GLuint SCREEN_WIDTH = 512, SCREEN_HEIGHT = 300;

float fov = 1.6f;

// sync screen renderer with main renderer
void update(Renderer *renderer) {
        drawnum = 0;
        batchnum = 0;

        w = renderer->w;
        h = renderer->h;

        SCREEN_WIDTH = renderer->SCREEN_WIDTH;
        SCREEN_HEIGHT = renderer->SCREEN_HEIGHT;

        screenFBO = &renderer->screenFBO;
        rfbo = renderer->rfbo;
        //fov = renderer->fov;

        uMatrix = glm::mat4(1.0f);
        cMatrix = glm::mat4(1.0f);
        pMatrix = glm::perspective(fov, (float) w / (float) h, 1.0f,
                                   1000000000.0f); // lol, stretch the frustum [0.0, 1.0]
}

void render(Texture tex, glm::mat4 objMatrix, std::vector<float> *vertexData, std::vector<float> *texData,
            std::vector<float> *colData, std::vector<int> *indexData) {
        uMatrix = objMatrix;
        this->tex = tex;

        buffer_indices = indexData->size();
        buffer_vertices = vertexData->size();

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertexData->size() * sizeof(float), &(*vertexData)[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertexData->size() * sizeof(float), &(*texData)[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, colBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertexData->size() * sizeof(float), &(*colData)[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData->size() * sizeof(int), &(*indexData)[0], GL_DYNAMIC_DRAW);

        flush();
}

void flushBatch() {
        if (buffer_indices > 2) {
                glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
                glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), vertexBufferArray, GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
                glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), texBufferArray, GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, colBuffer);
                glBufferData(GL_ARRAY_BUFFER, buffer_vertices * sizeof(float), colBufferArray, GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_indices * sizeof(int), indexBufferArray, GL_DYNAMIC_DRAW);

                flush();
        }
}

void draw(Texture tex, glm::mat4 objMatrix, std::vector<float> *vertexData, std::vector<float> *texData,
          std::vector<float> *colData, std::vector<int> *indexData) {
        if (vertexData->size() < BATCH_SIZE && indexData->size() < BATCH_SIZE) {
                batchAdd(tex, objMatrix, vertexData, texData, colData, indexData);
        }
        else {
                flushBatch();
                render(tex, objMatrix, vertexData, texData, colData, indexData);
        }
}

void batchAdd(Texture tex, glm::mat4 objMatrix, std::vector<float> *vertexData, std::vector<float> *texData,
              std::vector<float> *colData, std::vector<int> *indexData) {
        ++drawnum;
        uMatrix = objMatrix;

        if (buffer_vertices + vertexData->size() >= BATCH_SIZE ||
            buffer_indices + indexData->size() >= BATCH_SIZE || (tex.path != this->tex.path)) {
                flushBatch();
        }

        int vertices = buffer_vertices / 4;

        for (unsigned int i = 0; i < vertexData->size(); ++i) {
                vertexBufferArray[buffer_vertices] = vertexData->at(i);
                texBufferArray[buffer_vertices] = texData->at(i);
                colBufferArray[buffer_vertices] = colData->at(i);
                ++buffer_vertices;
        }

        for (unsigned int i = 0; i < indexData->size(); ++i) {
                indexBufferArray[buffer_indices] = indexData->at(i) + vertices;
                ++buffer_indices;
        }
        this->tex = tex;
}

// alpha test
bool at = true;

void flush() {
        ++batchnum;
        glUseProgram(screenShader.program);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->tex.tex);

        glDisable(GL_CULL_FACE);
        if (at) {
                glDisable(GL_DEPTH_TEST);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else {
                glEnable(GL_DEPTH_TEST);
                glDisable(GL_BLEND);
        }

        if (!rfbo) {
                glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                glBindFramebuffer(GL_FRAMEBUFFER, *screenFBO);
        }
        else {
                glViewport(0, 0, w, h);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        glUniformMatrix4fv(u_pMatrix, 1, GL_FALSE, glm::value_ptr(pMatrix));
        glUniformMatrix4fv(u_cMatrix, 1, GL_FALSE, glm::value_ptr(cMatrix));
        glUniformMatrix4fv(u_uMatrix, 1, GL_FALSE, glm::value_ptr(uMatrix));

        glBindVertexArray(vertexArrayID);

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
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, colBuffer);
        glVertexAttribPointer(
                2,
                4,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) 0
                );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

        glDrawRangeElements(GL_TRIANGLES, 0, buffer_vertices - 1, buffer_indices, GL_UNSIGNED_INT,
                            (void *) 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

        buffer_vertices = 0;
        buffer_indices = 0;
}

void init() {
        screenShader.init("gfx/shader/screenShader.vert", "gfx/shader/screenShader.frag", loadShaders);

        glUseProgram(screenShader.program);

        glGenVertexArrays(1, &vertexArrayID);
        glBindVertexArray(vertexArrayID);

        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &texBuffer);
        glGenBuffers(1, &colBuffer);
        glGenBuffers(1, &indexBuffer);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glDisable(GL_STENCIL_TEST);
        glDisable(GL_CULL_FACE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        u_pMatrix = glGetUniformLocation(screenShader.program, "projection");
        u_cMatrix = glGetUniformLocation(screenShader.program, "view");
        u_uMatrix = glGetUniformLocation(screenShader.program, "model");

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void destroyRenderer()
{
        screenShader.destroyShader();

        glDeleteVertexArrays(1, &vertexArrayID);

        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &texBuffer);
        glDeleteBuffers(1, &colBuffer);
        glDeleteBuffers(1, &indexBuffer);
}
};

#endif //CORIUM_SCREENRENDERER_H
