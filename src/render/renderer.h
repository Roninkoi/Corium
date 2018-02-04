//
// Created by Roni A. Koitermaa on 18.12.2015.
//

#ifndef CORIUM_RENDERER_H
#define CORIUM_RENDERER_H

#include <crm.h>
#include <render/shader/shader.h>
#include <texture.h>

const int BATCH_SIZE = GL_MAX_ELEMENTS_VERTICES;

struct Light {
        glm::vec3 pos;
        glm::vec3 col = glm::vec3(0.0f, 0.0f, 0.0f); // if col == (0, 0, 0) light is off

        GLuint depthMapFBO;
        GLuint depthCubemap;

        GLuint w = 512;
        GLuint h = 512;

        void initShadows(GLuint new_w, GLuint new_h)
        {
                w = new_w;
                h = new_h;

                glGenFramebuffers(1, &depthMapFBO);

                // Create depth cubemap texture
                glGenTextures(1, &depthCubemap);
                glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);

                for (GLuint i = 0; i < 6; ++i)
                        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                // Attach cubemap as depth map FBO's color buffer
                glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

                glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);

                glDrawBuffer(GL_NONE);
                glReadBuffer(GL_NONE);
                if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                        std::cout << "Framebuffer not complete!" << std::endl;
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        Light()
        {

        }
};

class Renderer {
public:
GLuint vertexArrayID;
GLuint vertexBuffer;
GLuint texBuffer;
GLuint indexBuffer;
GLuint normalBuffer;
GLuint colBuffer;

int vertices = 0;

bool save = false;

Texture tex;

GLuint SCREEN_WIDTH = 512, SCREEN_HEIGHT = 300;
float SCREEN_SCALE = 1.0f;

float far_plane = 200.0f;
glm::vec3 clr_col = glm::vec3(0.0f, 0.0f, 0.0f);

bool rts = false;     // render to screen

bool disableShadows = false;     // disable shadows for a draw

float amb = 0.5f;
float lght = 0.5f;
float render_dist = 0.5f;

bool dithering_enabled = true;

bool drawLines = false;

glm::vec3 camStart = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec3 down = glm::vec3(0.0f, -1.0f, 0.0f);

Shader PS_Shader;
Shader PS_ShaderDepth;
Shader quadShader;

GLuint screenTex;
GLuint screenFBO;

GLuint screenDepthTex;

GLuint quadBuf;
GLuint indBuf;

int MAX_LIGHTS = 8;
int max_lights = 8;

GLuint SHADOW_WIDTH = 512, SHADOW_HEIGHT = 512;

glm::mat4 cMatrix = glm::mat4(1.0f);
glm::mat4 pMatrix = glm::mat4(1.0f);
glm::mat4 uMatrix = glm::mat4(1.0f);

glm::vec3 camPos = glm::vec3(0.0f);
glm::vec3 camRot = glm::vec3(0.0f);
float camZ = 7.0f;

float vertexBufferArray[BATCH_SIZE];
float texBufferArray[BATCH_SIZE];
float colBufferArray[BATCH_SIZE];
float normalBufferArray[BATCH_SIZE];
int indexBufferArray[BATCH_SIZE];

int batchesPerCycle = 0;
int drawsPerCycle = 0;

int buffer_vertices = 0;
int buffer_indices = 0;

float xSpacing = 0.0f;

int w = 512;     // viewport dimensions
int h = 300;

float fov = 1.5f;

float ticks = 0.0f;

bool loadShaders = true;

int light_i = 0;

std::vector<Light> lights;

void flushBatch();

void flushBatchFBO();

void clear();

void update();

void renderFBO();

void batchAdd(Texture* tex, std::vector<float> *vertexData, std::vector<float> *normalData,
              std::vector<float> *texData,
              std::vector<float> *colData, std::vector<int> *indexData);

void draw(Texture* tex, std::vector<float> *vertexData, std::vector<float> *normalData, std::vector<float> *texData,
          std::vector<float> *colData, std::vector<int> *indexData);

void render(Texture* tex, glm::mat4 *objMatrix, std::vector<float> *vertexData, std::vector<float> *normalData,
            std::vector<float> *texData,
            std::vector<float> *colData, std::vector<int> *indexData);

void flush();     // FLUSH IT!

void flushUpdate();

void drawShadows(std::vector<float> *vertexData, std::vector<int> *indexData);
void renderShadows(glm::mat4 *objMatrix, std::vector<float> *vertexData, std::vector<int> *indexData);
void flushShadows();
void drawShadowMap();
void addShadows(std::vector<float> *vertexData, std::vector<int> *indexData);
void clearShadows();

void init();

void compileShaders();

void destroyRenderer();

Renderer()
{
}
};


#endif //CORIUM_RENDERER_H
