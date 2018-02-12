//
// Created by Roni A. Koitermaa on 20.12.2015.
//

#include "game.h"

int grabbed = 0;
bool jumped = true;
bool thrown = false;
bool rightPress = false;
float dist = 2.0f;

bool restartpressed = false;

bool flyingPressed = false;

bool console = true;

int meshNo = 0;

bool screenshotpressed = false;

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        dist += yoffset / 10.0f;
}

void Game::gameInput() {
        glfwSetScrollCallback(wndw.window, scroll_callback);

        input.getKeys(wndw.window);
        input.getMouse(wndw.window);

        if (!startScreen && !win && !lose) {
                thisPlayer->getInput(&input);
        }
        else {
                thisPlayer->phys.v = glm::vec3(0.0f);
                thisPlayer->phys.rot_v = glm::vec3(0.0f);
                thisPlayer->moving = false;
        }

        thisCamera->z = thisCamera->z*0.8f + dist*3.0f*0.2f;

        if (glfwGetWindowAttrib(wndw.window, GLFW_FOCUSED) && glfwGetMouseButton(wndw.window, GLFW_MOUSE_BUTTON_LEFT) &&
            !input.focused) {
                if (input.window_focus) {
                        input.window_focus = false;
                        input.focused = true;
                        glfwSetInputMode(wndw.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
                        glfwSetInputMode(wndw.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }
        }
        else {
                input.window_focus = true;
        }
        if (input.keyDown[GLFW_KEY_M]) {
                if (input.keyPressed[GLFW_KEY_M]) {
                        if (aud.playingMusic()) {
                                aud.haltMusic();
                        }
                        else {
                                aud.playMusic();
                        }
                        input.keyPressed[GLFW_KEY_M] = false;
                }
        }
        else {
                input.keyPressed[GLFW_KEY_M] = true;
        }
        if (input.keyDown[GLFW_KEY_Y]) {
                if (flyingPressed) {
                        thisPlayer->flying = !thisPlayer->flying;
                        flyingPressed = false;
                }
        }
        else {
                flyingPressed = true;
        }

        if (glfwGetKey(wndw.window, GLFW_KEY_F11)) {
                if (input.fullscreen) {
                        fullScr();

                        input.fullscreen = false;
                }
        }
        else {
                input.fullscreen = true;
        }
        if (glfwGetKey(wndw.window, GLFW_KEY_F2)) {
                if (console) {
                        console = false;
                        scr.console = !scr.console;
                }
        }
        else if (glfwGetKey(wndw.window, GLFW_KEY_F3)) {
                if (console) {
                        console = false;
                        scr.big = !scr.big;
                }
        }
        else {
                console = true;
        }

        if (glfwGetKey(wndw.window, GLFW_KEY_ESCAPE) && !wndw.fullscreen) {
                //running = false;
                input.focused = false;
                glfwSetInputMode(wndw.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        if (input.keyDown[GLFW_KEY_V] && !thrown) {
                map.physSys.finish();
                map.objs[grabbed].phys.pos = glm::vec3(thisPlayer->renderPos.x + dist * sin(-thisPlayer->phys.rot.y + M_PI),
                                                       thisPlayer->renderPos.y + dist * sin(thisPlayer->phys.rot.x + M_PI),
                                                       thisPlayer->renderPos.z + dist * cos(-thisPlayer->phys.rot.y + M_PI));
                map.objs[grabbed].phys.rot.y = -thisPlayer->phys.rot.y;
                map.objs[grabbed].phys.v = thisPlayer->phys.v - thisPlayer->phys.rot_v;

                //map.objs[grabbed].mesh.phys.update();
                //map.objs[grabbed].mesh.update();
        }

        int count;
        const unsigned char* jb = glfwGetJoystickButtons(input.jsnum, &count);
        bool jb1 = false;
        bool jb2 = false;
        bool jb3 = false;
        if (count >= 2) {
                jb1 = jb[1];
                jb2 = jb[0];
                jb3 = jb[2];
        }
        if (glfwGetKey(wndw.window, GLFW_KEY_LEFT_SHIFT) || jb2) {
                thisPlayer->spd = 4.5f * 0.5f * 0.5f * 2.2f;
                if (thisPlayer->moving) thisPlayer->sprinting = true;
        }
        else {
                thisPlayer->spd = 4.5f * 0.5f * 0.5f;
                thisPlayer->sprinting = false;
        }
        if (jb3 || glfwGetKey(wndw.window, GLFW_KEY_LEFT_ALT)) {
                thisPlayer->flaming = true;
        }
        else {
                thisPlayer->flaming = false;
        }

        if (glfwGetMouseButton(wndw.window, GLFW_MOUSE_BUTTON_LEFT)) {
                if (input.keyDown[GLFW_KEY_V] && !thrown) {
                        thrown = true;
                        map.objs[grabbed].phys.pos = glm::vec3(thisPlayer->renderPos.x + dist * sin(-thisPlayer->phys.rot.y + M_PI),
                                                               thisPlayer->renderPos.y + dist * sin(thisPlayer->phys.rot.x + M_PI),
                                                               thisPlayer->renderPos.z + dist * cos(-thisPlayer->phys.rot.y + M_PI));
                        map.objs[grabbed].phys.rot.y = -thisPlayer->phys.rot.y;
                        map.objs[grabbed].phys.v = glm::vec3(dist * sin(-thisPlayer->phys.rot.y + M_PI),
                                                             dist * sin(thisPlayer->phys.rot.x + M_PI),
                                                             dist * cos(-thisPlayer->phys.rot.y + M_PI))*0.1f;

                        map.objs[grabbed].phys.v = map.gravity;
                        map.objs[grabbed].update();
                }
        }
        else if (!input.keyDown[GLFW_KEY_V]) {thrown = false;}
        if (glfwGetMouseButton(wndw.window, GLFW_MOUSE_BUTTON_RIGHT)) {
        }

        if ((input.getKey(GLFW_KEY_SPACE) || jb1) && thisPlayer->health > 0.0f) {
                if (!jumped) {
                        if (startScreen)
                                startScreen = false;
                        if (glm::length(map.gravity) > 0.0f) {
                                thisPlayer->phys.v += -0.008f * glm::normalize(map.gravity) * 40.0f;
                                //aud.playAudio(6, aud.jump, 0);
                        }
                }
                jumped = true;
        }
        else if (thisPlayer->onGround) {
                jumped = false;
        }

        if (input.keyDown[GLFW_KEY_C] && ticks % 6 == 0) {
                if (input.keyPressed[GLFW_KEY_C] || true) {

                        map.physSys.finish();
                        std::string path;
                        switch (meshNo) {
                        case 0:
                                path = "gfx/models/tetra.obj";
                                break;
                        case 1:
                                path = "gfx/models/cube.obj";
                                break;
                        case 2:
                                path = "gfx/models/octa.obj";
                                break;
                        case 3:
                                path = "gfx/models/ico.obj";
                                break;
                        default:
                                path = "gfx/models/tetra.obj";
                                break;
                        }
                        path = "gfx/models/ico.obj";
                        ++meshNo;
                        if (meshNo > 3) meshNo = 0;

                        map.addObj(path,"", "gfx/white.png",
                                   glm::vec3(thisPlayer->phys.pos.x + 3.0f * sin(-thisPlayer->phys.rot.y + M_PI),
                                             thisPlayer->phys.pos.y + 3.0f * sin(thisPlayer->phys.rot.x + M_PI),
                                             thisPlayer->phys.pos.z + 3.0f * cos(-thisPlayer->phys.rot.y + M_PI)),
                                   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), false, true);
                        map.objs[map.objs.size() - 1].phys.isStatic = false;
                        if (meshNo == 2) {
                                map.objs[map.objs.size() - 1].phys.s = glm::vec3(0.7f);
                                map.objs[map.objs.size() - 1].phys.m = 0.3f;
                        }
                        if (meshNo == 1) map.objs[map.objs.size() - 1].phys.s = glm::vec3(1.3f);

                        map.objs[map.objs.size() - 1].phys.s *= glm::vec3(1.2f);

                        float r = random_range(0, 1000) / 1000.0f;
                        float g = random_range(0, 1000) / 1000.0f;
                        float b = random_range(0, 1000) / 1000.0f;

                        for (int i = 0; i < map.objs[map.objs.size() - 1].mesh.colBufferData.size(); i += 4) {
                                map.objs[map.objs.size() - 1].mesh.colBufferData[i] = r + random_range(0, 5) / 20.0f;
                                map.objs[map.objs.size() - 1].mesh.colBufferData[i + 1] = g + random_range(0, 5) / 20.0f;
                                map.objs[map.objs.size() - 1].mesh.colBufferData[i + 2] = b + random_range(0, 5) / 20.0f;
                                map.objs[map.objs.size() - 1].mesh.colBufferData[i + 3] = 1.0f;
                        }
                        input.keyPressed[GLFW_KEY_C] = false;
                        //map.addPhysObjects();
                        map.physadded = false;
                }
        }
        else {
                input.keyPressed[GLFW_KEY_C] = true;
                if (!map.physadded) {
                        map.addPhysObjects();
                        map.physadded = true;
                }
        }

        if (glfwGetKey(wndw.window, GLFW_KEY_RIGHT_CONTROL)) {
                if (!rightPress && grabbed < map.objs.size() - 1) {
                        rightPress = true;
                        grabbed += 1;
                        print("grabbed " + to_string(grabbed) + "\n");
                }
        }
        else if (glfwGetKey(wndw.window, GLFW_KEY_LEFT_CONTROL)) {
                if (!rightPress && grabbed > 0) {
                        rightPress = true;
                        grabbed -= 1;
                        print("grabbed " + to_string(grabbed) + "\n");
                }
        }
        else {
                rightPress = false;
        }

        if (input.keyDown[GLFW_KEY_I]) {
                loadGameCfg();
                loadingScreen();
                map.reload(&renderer);
        }

        if (input.keyDown[GLFW_KEY_U]) { // MASSIVE MEMORY LEAK!
                if (restartpressed) {
                        restartpressed = false;
                        rendererReset();
                }
        }
        if (input.keyDown[GLFW_KEY_O]) {
                loadGameCfg();
        }
        if (input.keyDown[GLFW_KEY_T]) {
                if (restartpressed) {
                        restartpressed = false;
                        map.restart();
                        //map.gen.generate();
                }
        }
        else {
                restartpressed = true;
        }
        if (input.keyDown[GLFW_KEY_B]) {
                if (screenshotpressed) {
                        screenshotpressed = false;
                        renderer.save = true;
                        //map.gen.generate();
                }
        }
        else {
                screenshotpressed = true;
        }
        if (input.keyDown[GLFW_KEY_J]) {
                renderer.xSpacing += 0.001f;
        }
        if (input.keyDown[GLFW_KEY_K]) {
                renderer.xSpacing -= 0.001f;
        }
        if (input.keyDown[GLFW_KEY_L]) {
                renderer.xSpacing = 0.0f;
        }

}
