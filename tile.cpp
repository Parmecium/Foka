#include "main.h"
#include "functions.h"
#include "player.h"
#include "tile.h"

Tile::Tile(void)
{
    this->coords.x = 0;
    this->coords.y = 0;
    this->coords.w = 0;
    this->coords.h = 0;
    this->collCoords = this->coords;
    this->type = TILE_TYPE_UNKNOWN;
}

Tile::Tile(float x, float y, float width, float height, int type)
{
    this->coords.x = x;
    this->coords.y = y;
    this->coords.w = width;
    this->coords.h = height;
    this->collCoords = this->coords;
    this->type = type;
}

Tile::~Tile(void)
{
}

void Tile::loadTexture(void)
{
    switch(this->type)
    {
        case TILE_WALL_DOWN:
            this->texture = loadModel("data/zid_d.png");
            break;
        case TILE_WALL_RIGHT:
            this->texture = loadModel("data/zid_r.png");
            break;
        case TILE_WALL_UP:
            this->texture = loadModel("data/zid_u.png");
            break;
        case TILE_WALL_LEFT:
            this->texture = loadModel("data/zid_l.png");
    }
}

void Tile::collision(Player *player)
{
    SDL_Rect tmpCoords = this->collCoords;
    SDL_Rect playerCoords = player->getCollCoords();
    tmpCoords.x += 8;
    tmpCoords.y += 8;
    tmpCoords.w -= 8;
    tmpCoords.h -= 8;

    if(playerCoords.x + playerCoords.w > this->collCoords.x &&
            playerCoords.x < this->collCoords.x + this->collCoords.w &&
            playerCoords.y + playerCoords.h > this->collCoords.y &&
            playerCoords.y < this->collCoords.y + this->collCoords.h)
    {
        if(playerCoords.x + playerCoords.w <= tmpCoords.x)
            player->setX(this->collCoords.x - playerCoords.w);
        if(playerCoords.x >= this->collCoords.x + tmpCoords.w)
            player->setX(this->collCoords.x + this->collCoords.w
                    - playerCoords.x + player->getX());
        if(playerCoords.y + playerCoords.h <= tmpCoords.y)
            player->setY(this->collCoords.y - playerCoords.h);
        if(playerCoords.y >= this->collCoords.y + tmpCoords.h)
            player->setY(this->collCoords.y + this->collCoords.h);
    }
}

void Tile::render(void)
{
    glColor4ub(255, 255, 255, 255); // White color
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, this->texture);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(this->coords.x, this->coords.y);
        glTexCoord2d(1, 1); glVertex2f(this->coords.x + this->coords.w, this->coords.y);
        glTexCoord2d(1, 0); glVertex2f(this->coords.x + this->coords.w, this->coords.y + this->coords.h);
        glTexCoord2d(0, 0); glVertex2f(this->coords.x, this->coords.y + this->coords.h);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
