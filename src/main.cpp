#include <game/game.h>
#include <util/crmlang.h>

Game game;

void gamePrint(std::string s)
{
        game.print(s);
}

void gameRefresh()
{
        game.refresh();
}

void gameScript(std::string s)
{
        runScript(s, &game);
}

int main(int argc, char* argv[])
{
        game.init();
        game.start();

        return 0;
}
