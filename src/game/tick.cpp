//
// Created by Roninkoi on 19.12.2015.
//

#include "game.h"

void Game::tick()
{
        ++ticks;
        ++game_ticks;
        renderer.ticks += 1.0f;
        map.ticks += 1.0f;
        scr.ticks += 1.0f;

        gameInput();

        if (reset) {
                reset = false;
                win = false;
                lose = false;
        }

        map.update();

        scr.tick();
}
