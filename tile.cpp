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
        case TILE_PLANT1:
            this->coords.w = 200;
            this->coords.h = 200;
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
            this->texture = loadModel("data/zid/zid2_d.png");
            break;
        case TILE_WALL_RIGHT:
            this->texture = loadModel("data/zid/zid2_r.png");
            break;
        case TILE_WALL_UP:
            this->texture = loadModel("data/zid/zid2_u.png");
            break;
        case TILE_WALL_LEFT:
            this->texture = loadModel("data/zid/zid2_l.png");
            break;
        case TILE_WALL_DL:
            this->texture = loadModel("data/zid/zid2_dl.png");
            break;
        case TILE_WALL_DR:
            this->texture = loadModel("data/zid/zid2_dr.png");
            break;
        case TILE_WALL_UR:
            this->texture = loadModel("data/zid/zid2_ur.png");
            break;
        case TILE_WALL_UL:
            this->texture = loadModel("data/zid/zid2_ul.png");
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
        case TILE_PLANT1:
            this->texture = loadModel("data/heal_plant/plant1.png.png");
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

    switch(this->type)
    {
        case TILE_PLANT1:
            {
                int p = this->collCoords.x + this->collCoords.w / 2;
                int q = this->collCoords.y + this->collCoords.h / 2;
                int r = this->collCoords.w / 2;
                int k;
                int n;
                int a, b, c;
                float x1, x2, y1, y2;

                if(pow(playerCoords.x - p, 2) + pow(playerCoords.y - q, 2)
                        < pow(r, 2))
                {
                    // (x1/2 = -b +- sqrt(b^2 - 4ac)) / 2a
                    k = (playerCoords.y - q) / (playerCoords.x - p);
                    n = k * (-p) + q;
                    a = 1 + pow(k, 2);
                    b = 2 * p - 2 * k * n + 2 * k * q;
                    c = pow(r, 2) + pow(n, 2) - 2 * n * q - pow(q, 2) - pow(p, 2);
                    x1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;
                    x2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;
                    y1 = k * x1 + n;
                    y2 = k * x2 + n;

                    if(x1 == x2)
                    {
                        player->setX(x1);
                        player->setY(x1);
                    } else
                    {
                        float d1 = pow(x1 + playerCoords.x, 2) +
                            pow(y1 + playerCoords.y, 2);
                        float d2 = pow(x2 + playerCoords.x, 2) +
                            pow(y2 + playerCoords.y, 2);
                        if(d1 > d2)
                        {
                            player->setX(x1);
                            player->setY(y1);
                        } else
                        {
                            player->setX(x2);
                            player->setY(y2);
                        }
                    }
                }
                break;
            }
        default:
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
            break;
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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBegin(GL_QUADS);
            glTexCoord2d(0, 1); glVertex2f(this->coords.x - camera.x, this->coords.y - camera.y);
            glTexCoord2d(1, 1); glVertex2f(this->coords.x + this->coords.w - camera.x, this->coords.y - camera.y);
            glTexCoord2d(1, 0); glVertex2f(this->coords.x + this->coords.w - camera.x, this->coords.y + this->coords.h - camera.y);
            glTexCoord2d(0, 0); glVertex2f(this->coords.x - camera.x, this->coords.y + this->coords.h - camera.y);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
}
