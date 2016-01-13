#include "main.h"
#include "functions.h"
#include "player.h"
#include "tile.h"

Tile::Tile(float x, float y, float width, float height, int type)
{
    this->coords.x = x;
    this->coords.y = y;
    this->coords.w = width;
    this->coords.h = height;
    this->collCoords = this->coords;
    this->type = type;
}

Tile::Tile(float x, float y, int type)
{
    this->coords.x = x;
    this->coords.y = y;
    this->type = type;
    switch(type)
    {
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
    tmpCoords.w -= 8;
    tmpCoords.h -= 8;

    if(playerCoords.x + playerCoords.w > this->collCoords.x &&
            playerCoords.x < this->collCoords.x + this->collCoords.w &&
            playerCoords.y + playerCoords.h > this->collCoords.y &&
            playerCoords.y < this->collCoords.y + this->collCoords.h)
    {
        if(playerCoords.x + playerCoords.w <= tmpCoords.x)
            player->setX(this->collCoords.x - playerCoords.w);
        else if(playerCoords.x >= tmpCoords.x + tmpCoords.w)
            std::cout << "test" << std::endl;
        if(playerCoords.y + playerCoords.h <= tmpCoords.y)
            player->setY(this->collCoords.y - playerCoords.h);
        else if(playerCoords.y >= tmpCoords.y + tmpCoords.h)
            std::cout << "test 2" << std::endl;
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
