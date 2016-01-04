#include "main.h"
#include "functions.h"
#include "tile.h"

Tile::Tile(void)
{
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->type = TILE_TYPE_UNKNOWN;
}

Tile::Tile(float x, float y, float width, float height, int type)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
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
        glTexCoord2d(0, 1); glVertex2f(this->x, this->y);
        glTexCoord2d(1, 1); glVertex2f(this->x + this->width, this->y);
        glTexCoord2d(1, 0); glVertex2f(this->x + this->width, this->y + this->height);
        glTexCoord2d(0, 0); glVertex2f(this->x, this->y + this->height);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
