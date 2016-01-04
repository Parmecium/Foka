#include "main.h"
#include "splash.h"
#include "tile.h"
#include "player.h"
#include "game.h"

int main(int argc, char *argv[])
{
    Game *game = new Game();
    game->mainLoop();
    delete game;
    return 0;
}
