//
// Created by Roni A. Koitermaa on 18.12.2015.
//

#include "game.h"
#include <util/currentTime.h>
#include <util/cfgParser.h>

Game::Game()
{
        text_buffer.resize(15);
}

void Game::main()
{
        auto time = getTime();
        auto fps_time = getTime();

        while (running) {
                ++frame_ticks;

                if (getTime() - fps_time >= 1000) {
                        fps_time = getTime();
                        fps = frame_ticks;

                        std::string fpsString = "FPS: " + to_string(fps) + ", rt: "
                                                + to_string((renderTime) / (float) frame_ticks) + " ms, draws: " +
                                                to_string(renderer.drawsPerCycle) + ", batches: " +
                                                to_string(renderer.batchesPerCycle) + ", tt: " +
                                                to_string((tickTime) / (float) game_ticks) +
                                                " ms";
                        print(fpsString + "\n");
                        print("lights: " + to_string(renderer.max_lights) + "\n");

                        print("Player pos: " + to_string(thisPlayer->phys.pos.x) + ", " + to_string(thisPlayer->phys.pos.y) +
                              ", " + to_string(thisPlayer->phys.pos.z) + "\n");

                        renderTime = 0;
                        tickTime = 0;

                        frame_ticks = 0;
                        game_ticks = 0;
                }

                auto renderTimeStart = getTime();

                // GAME RENDERING
                gameRender();

                renderTime += getTime() - renderTimeStart;

                if (getTime() - time >= 15) {
                        time = getTime();

                        auto tickTimeStart = getTime();

                        // GAME LOGIC
                        tick();

                        tickTime += getTime() - tickTimeStart;
                }

                //UPDATE WINDOW
                wndw.update(&running);
        }
        gameQuit();
}

int Game::getTime()
{
        long long int et = std::chrono::duration_cast<std::chrono::milliseconds>
                                   (timer.now().time_since_epoch() - start_time).count();

        int returns = (int)et;

        return returns;
}

void Game::refresh()
{
        renderer.flushBatchFBO();
        wndw.update(&running); // update window to keep it from freezing
}

void Game::init()
{
        printf("CORIUM 1.4 RONIN748 2018\n");

        thisPlayer = map.getPlayer();
        thisCamera = map.getCamera();

        loadGameCfg();

        if (fileoutput) outputfile = freopen("output.log", "w", stdout);

        print("==========================================================\n");
        print("------------- CORIUM ENGINE v1.4 BY RONIN748 -------------\n");
        print("------------------ " + to_string(currentDateTime()) + " -------------------\n");
        print("==========================================================\n\n");

        int glfw_err = glfwInit();
        if (!glfw_err) {
                printf("Failed to init GLFW %i%s", glfw_err, "\n");
        }

        wndw.createWindow();

        glewExperimental = GL_TRUE;
        int glew_err = glewInit();
        if (glew_err != GLEW_OK) {
                printf("Failed to init GLEW %i%s", glew_err, "\n");
        }

        print("max vertices: " + to_string(GL_MAX_ELEMENTS_VERTICES) + "\n");
        print("max indices: " + to_string(GL_MAX_ELEMENTS_INDICES) + "\n");
        print("batch size: " + to_string(BATCH_SIZE) + "\n");
        print("max tex size: " + to_string(GL_MAX_RECTANGLE_TEXTURE_SIZE) + "\n");

        print("OpenGL version: " + to_string(glGetString(GL_VERSION)) + "\n");
        print("GL_RENDERER: " + to_string(glGetString(GL_RENDERER)) + "\n");

        aud.initAudio();

        renderer.init();

        scr.loadScreen();

        aud.loadAudio();

        if (startFullScr)
                fullScr();
}

void Game::start()
{
        start_time = timer.now().time_since_epoch();

        running = true;

        if (wndw.swapInterval == 0) {
                print("Vsync disabled!\n");
        }
        else {
                print("Vsync enabled!\n");
        }

        map.start(&renderer, &aud, &running);

        wndw.update(&running); // correct window dimesions

        // update main renderer so screen renderer can initialize itself
        rendererUpdate();

        GLFWimage icons[1];
        icons[0].pixels = SOIL_load_image("gfx/misc/CRM_logo.png", &icons[0].width, &icons[0].height, 0, SOIL_LOAD_RGBA);
        glfwSetWindowIcon(wndw.window, 1, icons);

        // loading screen
        loadingScreen();

        map.load(&renderer);

        while (getTime() < 2000) {
                wndw.update(NULL);
        }

        if (music) aud.playMusic();

        main();
}

void Game::print(std::string s)
{
        printf(&s[0]);

        for (int i = text_buffer.size() - 1; i > 0; --i)
                text_buffer[i] = text_buffer[i - 1];

        text_buffer[0] = s;
}

void Game::loadGameCfg()
{
        loadSettings("settings.cfg", this);
}

void Game::fullScr()
{
        wndw.fullScr();

        input.window_focus = false;
        input.focused = true;
        glfwSetInputMode(wndw.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetInputMode(wndw.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::gameQuit()
{
        map.quit();

        wndw.destroyWindow();

        glfwTerminate();

        if (fileoutput) fclose(outputfile);
}
