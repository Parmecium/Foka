#include "main.h"
#include "functions.h"
#include "tile.h"

Tile::Tile(void)
{
    this->coords.x = 0;
    this->coords.y = 0;
    this->coords.w = 0;
    this->coords.h = 0;
    this->type = TILE_TYPE_UNKNOWN;
}

Tile::Tile(float x, float y, float width, float height, int type)
{
    this->coords.x = x;
    this->coords.y = y;
    this->coords.w = width;
    this->coords.h = height;
    this->type = type;
}

Tile::~Tile(void)
{
}

void Tile::loadTexture(void)
{
    texture = loadModel("data/zid1.png");
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
