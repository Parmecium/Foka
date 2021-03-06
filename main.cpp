#include "main.h"
#include "functions.h"
#include "timer.h"
#include "splash.h"
#include "fstring.h"
#include "menuoption.h"
#include "menu.h"
#include "menu_language.h"
#include "player.h"
#include "tile.h"
#include "enemy.h"
#include "inventory.h"
#include "map.h"
#include "game.h"

int main(int argc, char *argv[])
{
    Game *game = new Game();
    game->mainLoop();
    delete game;
    return 0;
}
