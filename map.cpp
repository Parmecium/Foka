#include "main.h"
#include "functions.h"
#include "timer.h"
#include "player.h"
#include "tile.h"
#include "map.h"

Map::Map(float width, float height, float sWidth, float sHeight)
{
    int i;

    this->width = width;
    this->height = height;
    this->sWidth = sWidth;
    this->sHeight = sHeight;

    this->camera = {0, 0, this->sWidth, this->sHeight };

    timer = new Timer();
    player = new Player(55, 55, timer);
    player2 = new Player(55, 75, timer);

    // Test
    this->tile.push_back(new Tile(300, 300, TILE_DESK));
    for(i = 0; i <= width - 100; i += 100)
    {
        this->tile.push_back(new Tile(i, 0, TILE_WALL_UP));
        this->tile.push_back(new Tile(i, this->width - 50, TILE_WALL_DOWN));
    }
    for(i = 0; i <= height - 100; i+= 100)
    {
        this->tile.push_back(new Tile(0, i, TILE_WALL_RIGHT));
        this->tile.push_back(new Tile(this->height - 50, i, TILE_WALL_LEFT));
    }
}

Map::~Map(void)
{
    int i;

    delete this->player;
    delete this->player2;
    for(i = 0; i < this->tile.size(); i++)
        delete this->tile[i];
    delete timer;
}

void Map::loadTexture(void)
{
    int i;
    player->loadTexture("pig/pig");
    player2->loadTexture("creep/creep");
    for(i = 0; i < this->tile.size(); i++)
        this->tile[i]->loadTexture();
}

void Map::setCamera(void)
{
    this->camera.x = (this->player->getX() + this->player->getWidth() / 2) -
        this->sWidth / 2;
    this->camera.y = (this->player->getY() + this->player->getHeight() / 2) -
        this->sHeight / 2;
    if(camera.x < 0)
        this->camera.x = 0;
    else if(this->camera.x + this->camera.w > this->width)
        this->camera.x = this->width - this->camera.w;
    if(this->camera.y < 0)
        this->camera.y = 0;
    else if(this->camera.y + this->camera.h > this->height)
        this->camera.y = this->width - this->camera.h;
}

void Map::logic(void)
{
    int i;
    player->move();
    player2->move();
    for(i = 0; i < tile.size(); i++)
    {
        this->tile[i]->collision(player);
        this->tile[i]->collision(player2);
    }
    this->setCamera();
    this->timer->tick();
}

void Map::render(void)
{
    int i;
    this->player->render(camera.x, camera.y);
    this->player2->render(camera.x, camera.y);
    for(i = 0; i < tile.size(); i++)
        this->tile[i]->render(camera.x, camera.y);
}
