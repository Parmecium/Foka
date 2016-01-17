#include "main.h"
#include "functions.h"
#include "timer.h"
#include "player.h"
#include "tile.h"

Tile::Tile(float x, float y, int type)
{
    this->coords.x = x;
    this->coords.y = y;
    this->type = type;
    switch(type)
    {
        case TILE_WALL_LEFT: case TILE_WALL_RIGHT:
            this->coords.w = 50;
            this->coords.h = 100;
            break;
        case TILE_WALL_UP: case TILE_WALL_DOWN:
            this->coords.w = 100;
            this->coords.h = 50;
            break;
        case TILE_DESK:
            this->coords.w = 50;
            this->coords.h = 50;
            break;
    }
    this->collCoords = this->coords;
}

Tile::~Tile(void)
{
}

void Tile::loadTexture(void)
{
    switch(this->type)
    {
        case TILE_WALL_DOWN:
            this->texture = loadModel("data/zid/zid_d.png");
            break;
        case TILE_WALL_RIGHT:
            this->texture = loadModel("data/zid/zid_r.png");
            break;
        case TILE_WALL_UP:
            this->texture = loadModel("data/zid/zid_u.png");
            break;
        case TILE_WALL_LEFT:
            this->texture = loadModel("data/zid/zid_l.png");
            break;
        case TILE_DESK:
            this->texture = loadModel("data/stocic.png");
            break;
    }
}

void Tile::collision(Player *player)
{
    SDL_Rect tmpCoords = this->collCoords;
    SDL_Rect playerCoords = player->getCollCoords();
    tmpCoords.x += 8;
    tmpCoords.y += 8;
    tmpCoords.w -= 15;
    tmpCoords.h -= 15;

    if(playerCoords.x + playerCoords.w > this->collCoords.x &&
            playerCoords.x < this->collCoords.x + this->collCoords.w &&
            playerCoords.y + playerCoords.h > this->collCoords.y &&
            playerCoords.y < this->collCoords.y + this->collCoords.h)
    {
        if(playerCoords.x + playerCoords.w <= tmpCoords.x)
            player->setX(this->collCoords.x - playerCoords.w);
        if(playerCoords.x >= tmpCoords.x + tmpCoords.w)
            player->setX(this->collCoords.x + this->collCoords.w);
        if(playerCoords.y + playerCoords.h <= tmpCoords.y)
            player->setY(this->collCoords.y - playerCoords.h);
        if(playerCoords.y >= tmpCoords.y + tmpCoords.h)
            player->setY(this->collCoords.y + this->collCoords.h);
    }
}

void Tile::render(SDL_Rect camera)
{
    if(this->coords.x + this->coords.w > camera.x &&
            this->coords.y + this->coords.h > camera.y &&
            this->coords.x < camera.x + camera.w &&
            this->coords.y < camera.y + camera.h)
    {
        glColor4ub(255, 255, 255, 255); // White color
        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, this->texture);
        glBegin(GL_QUADS);
            glTexCoord2d(0, 1); glVertex2f(this->coords.x - camera.x, this->coords.y - camera.y);
            glTexCoord2d(1, 1); glVertex2f(this->coords.x + this->coords.w - camera.x, this->coords.y - camera.y);
            glTexCoord2d(1, 0); glVertex2f(this->coords.x + this->coords.w - camera.x, this->coords.y + this->coords.h - camera.y);
            glTexCoord2d(0, 0); glVertex2f(this->coords.x - camera.x, this->coords.y + this->coords.h - camera.y);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
}
