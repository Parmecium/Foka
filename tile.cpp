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
    texture = loadModel("data/zid1.png");
}

void Tile::collision(Player *player)
{
    SDL_Rect tmpCoords = this->collCoords;
    tmpCoords.x += 8;
    tmpCoords.y += 8;
    tmpCoords.w -= 8;
    tmpCoords.h -= 8;

    if(player->getX() + player->getWidth() > this->collCoords.x &&
            player->getX() < this->collCoords.x + this->collCoords.w &&
            player->getY() + player->getHeight() > this->collCoords.y &&
            player->getY() < this->collCoords.y + this->collCoords.h)
    {
        if(player->getX() + player->getWidth() <= tmpCoords.x)
            player->setX(this->collCoords.x - player->getWidth());
        if(player->getX() >= this->collCoords.x + tmpCoords.w)
            player->setX(this->collCoords.x + this->collCoords.w);
        if(player->getY() + player->getHeight() <= tmpCoords.y)
            player->setY(this->collCoords.y - player->getHeight());
        if(player->getY() >= this->collCoords.y + tmpCoords.h)
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
