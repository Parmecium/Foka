#include "main.h"
#include "functions.h"
#include "timer.h"
#include "player.h"
#include "tile.h"
#include "enemy.h"
#include "inventory.h"
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
    player = new Player(100, 95, timer);
    player2 = new Player(130, 95, timer);
    inventory = new Inventory(this->sWidth, this->sHeight, timer);

    this->bgCoords = {0, 0, 98, 98};

    // Test
    //this->tile.push_back(new Tile(600, 300, TILE_LEAF));
    for(i = 50; i < width - 100; i += 150)
    {
        this->tile.push_back(new Tile(i, 50, TILE_WALL_UP));
        this->tile.push_back(new Tile(i, this->width - 100, TILE_WALL_DOWN));
    }
    for(i = 50; i < height - 100; i += 150)
    {
        this->tile.push_back(new Tile(50, i, TILE_WALL_RIGHT));
        this->tile.push_back(new Tile(this->height - 100, i, TILE_WALL_LEFT));
    }
    for(i = 0; i <= width - 50; i += 50)
    {
        this->tile.push_back(new Tile(i, 0, TILE_NOTHING));
        this->tile.push_back(new Tile(i, this->width - 50, TILE_NOTHING));
    }
    for(i = 0; i <= height - 50; i += 50)
    {
        this->tile.push_back(new Tile(0, i, TILE_NOTHING));
        this->tile.push_back(new Tile(this->height - 50, i, TILE_NOTHING));
    }

    //this->tile.push_back(new Tile(730, 240, TILE_WALL_LEFT));
    //this->tile.push_back(new Tile(745, 240, TILE_WALL_RIGHT));
    for(i = 0; i < 6; i++)
    {
        int n = randnum(800);
        int m = randnum(800);
        this->tile.push_back(new Tile(n, m, TILE_WALL_LEFT));
        this->tile.push_back(new Tile(n + 15, m, TILE_WALL_RIGHT));
    }

    this->enemy.push_back(new Enemy(300, 410, timer));
}

Map::~Map(void)
{
    int i;

    delete this->player;
    delete this->player2;
    delete this->inventory;
    for(i = 0; i < this->tile.size(); i++)
        delete this->tile[i];
    for(i = 0; i < this->enemy.size(); i++)
        delete this->enemy[i];
    delete timer;
}

void Map::loadTexture(void)
{
    int i;
    player->loadTexture("pig/pig");
    //player2->loadTexture("grim/grim");
    player2->loadTexture("duh/duh");
    inventory->loadTexture();
    for(i = 0; i < this->tile.size(); i++)
        this->tile[i]->loadTexture();
    for(i = 0; i < this->enemy.size(); i++)
        this->enemy[i]->loadTexture("duh/duh");
    //this->bgImg = loadModel("data/testBg3.png");
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
    player->collision(width, height);
    player2->collision(width, height);
    for(i = 0; i < tile.size(); i++)
    {
        this->tile[i]->collision(player);
        this->tile[i]->collision(player2);
    }
    for(i = 0; i < enemy.size(); i++)
        this->enemy[i]->move();
    this->setCamera();
    this->timer->tick();
}

void Map::resized(void)
{
    this->inventory->setScreenSize(this->sWidth, this->sHeight);
}

void Map::render(void)
{
    int i, j;

    /*
    for(i = 0; i < this->width - this->bgCoords.w; i += this->bgCoords.w)
        for(j = 0; j < this->height - this->bgCoords.h; j += this->bgCoords.h)
        {
            this->bgCoords.x = i;
            this->bgCoords.y = j;

            if(this->bgCoords.x + this->bgCoords.w > this->camera.x &&
                    this->bgCoords.y + this->bgCoords.h > this->camera.y &&
                    this->bgCoords.x < this->camera.x + camera.w &&
                    this->bgCoords.y < this->camera.y + camera.h)
            {
                glColor4ub(255, 255, 255, 255);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, this->bgImg);
                glBegin(GL_QUADS);
                    glTexCoord2d(0, 1); glVertex2f(this->bgCoords.x - this->camera.x, this->bgCoords.y - this->camera.y);
                    glTexCoord2d(1, 1); glVertex2f(this->bgCoords.x - this->camera.x + this->bgCoords.w, this->bgCoords.y - this->camera.y);
                    glTexCoord2d(1, 0); glVertex2f(this->bgCoords.x - this->camera.x + this->bgCoords.w, this->bgCoords.y - this->camera.y + this->bgCoords.h);
                    glTexCoord2d(0, 0); glVertex2f(this->bgCoords.x - this->camera.x, this->bgCoords.y - this->camera.y + this->bgCoords.h);
                glEnd();
                glDisable(GL_TEXTURE_2D);
            }
        }
    */

    for(i = 0; i < tile.size(); i++)
        this->tile[i]->render(camera);
    for(i = 0; i < enemy.size(); i++)
        this->enemy[i]->render(camera);
    this->player->render(camera);
    this->player2->render(camera);
    this->inventory->render();
}
