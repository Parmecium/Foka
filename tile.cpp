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
        case TILE_WALL_LEFT: case TILE_WALL_RIGHT:  /*130 najbolje*/
            this->coords.w = 150;
            this->coords.h = 150;
            break;
        case TILE_WALL_UP: case TILE_WALL_DOWN:
            this->coords.w = 150;
            this->coords.h = 150;
            break;
        case TILE_WALL_DL: case TILE_WALL_DR:
        case TILE_WALL_UR: case TILE_WALL_UL:
            this->coords.w = 150;
            this->coords.h = 150;
            break;
        case TILE_DESK:
            this->coords.w = 50;
            this->coords.h = 50;
            break;
        case TILE_TREE_FALL:
            this->coords.w = 90;
            this->coords.h = 100;
            break;
        /*case TILE_LEAF:
            this->coords.w = 140;
            this->coords.h = 80;
            break;*/
        case TILE_NOTHING:
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
            this->texture = loadModel("data/zid/zid1_d.png");
            break;
        case TILE_WALL_RIGHT:
            this->texture = loadModel("data/zid/zid1_r.png");
            break;
        case TILE_WALL_UP:
            this->texture = loadModel("data/zid/zid1_u.png");
            break;
        case TILE_WALL_LEFT:
            this->texture = loadModel("data/zid/zid1_l.png");
            break;
        case TILE_WALL_DL:
            this->texture = loadModel("data/zid/zid1_dl.png");
            break;
        case TILE_WALL_DR:
            this->texture = loadModel("data/zid/zid1_dr.png");
            break;
        case TILE_WALL_UR:
            this->texture = loadModel("data/zid/zid1_ur.png");
            break;
        case TILE_WALL_UL:
            this->texture = loadModel("data/zid/zid1_ul.png");
            break;
        case TILE_DESK:
            this->texture = loadModel("data/stocic_bloody.png");
            break;
        case TILE_TREE_FALL:
            this->texture = loadModel("data/stvari/stocic_bloody.png");
            break;
        /*case TILE_LEAF:
            this->texture = loadModel("data/list.png");
            break; */
        case TILE_NOTHING:
            this->texture = 0;
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
        if(this->type == TILE_NOTHING)  // OVO OBAVEZNO PROMENITI !!!
            glColor4ub(0, 0, 0, 255);
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
