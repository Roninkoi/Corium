//
// Created by Roni A. Koitermaa on 21.12.2015.
//

#include "game.h"

// update renderer values per cycle
void Game::rendererUpdate()
{
        renderer.w = wndw.w;
        renderer.h = wndw.h;

        renderer.camPos = thisCamera->pos;
        renderer.camRot = thisCamera->rot;
        renderer.camZ = thisCamera->z;
        renderer.fov = thisCamera->fov;

        renderer.batchesPerCycle = 0;
        renderer.drawsPerCycle = 0;
}

void Game::gameRender() {
        if (startScreen) {
                thisCamera->pos = thisCamera->camStart;
                thisCamera->rot.y = renderer.ticks / 100.0f;
                thisCamera->rot.x = 0.3f*sin(renderer.ticks / 100.0f);
        }

        rendererUpdate();

        renderer.update();

        map.draw(&renderer);

        // flush before screen draws to buffer
        renderer.flushBatch();

        //renderer.flushUpdate();

        // copy text buffer to screen
        scr.text_buffer.resize(text_buffer.size());
        for (int i = 0; i < text_buffer.size(); ++i) {
                scr.text_buffer[i] = text_buffer[i];
        }

        if (startScreen) {
                scr.drawStartScreen(&renderer);
        }
        else if (win) {
                scr.drawWinScreen(&renderer);
        }
        else {
                scr.drawScreen(&renderer);
        }

        // flush batch and render FBO if in use
        renderer.flushBatchFBO();

        renderer.batchesPerCycle += scr.scrRndr.batchnum;
        renderer.drawsPerCycle += scr.scrRndr.drawnum;

        // count the number of lights that are ON, adjust renderer value
        int lOn = 0;
        for (int l = 0; l < renderer.MAX_LIGHTS; ++l) {
                if (glm::length(renderer.lights[l].col) > 0.0f)
                        ++lOn;
        }
        renderer.max_lights = lOn;
}
