#include "main.h"
#include "functions.h"
#include "timer.h"
#include "player.h"
#include "inventory.h"

class InventoryAnimator : public Ticker
{
    private:
        Inventory *inventory;

    public:
        InventoryAnimator(Inventory *inventory)
        {
            this->inventory = inventory;
        }

        virtual void tick(void)
        {
            this->inventory->changeTexture();
        }
};

Inventory::Inventory(float width, float height, Timer *timer, Player *player)
{
    this->screen = { 0, 0, width, height };
    this->heart = { 35, 0, 115, 135 };   // ne pomera se sa desne strane kao da je zalepljeno , javi Zi-u
    this->healthCoords = { 170, 0, 50, 50 };
    this->healthBgCoords = { healthCoords.x - 25,
                             0,
                             healthCoords.w * player->getHealth() + 100,
                             healthCoords.h + 100 };
    this->textureState = 0;
    this->textureIncrement = 1;

    this->player = player;

    if(timer != NULL)
        timer->add(130, new InventoryAnimator(this)); //bilo je 260
}

Inventory::~Inventory(void)
{
}

void Inventory::loadTexture(void)
{
    this->texture[0] = loadModel("data/heart/heart_full3.png");
    this->texture[1] = loadModel("data/heart/heart_full4.png");
    this->texHealth = loadModel("data/life/life1.png");
    this->texHealthBg = loadModel("data/life/life_box.png");
}

void Inventory::changeTexture(void)
{
    this->textureState += this->textureIncrement;
    if(this->textureState <= 1 || this->textureState >= ANIMATION_FRAMES)
        this->textureIncrement *= -1;
}

void Inventory::setScreenSize(float width, float height)
{
    this->screen.w = width;
    this->screen.h = height;
    this->heart.y = height - this->heart.h - 35;
    this->healthCoords.y = height - this->healthCoords.h - 50;
    this->healthBgCoords.y = this->healthCoords.y - 65;
}

void Inventory::render(void)
{
    int x, y, w, h;
    int i;

    glColor4ub(255, 255, 255, 255); // White color
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texture[this->textureState]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(this->heart.x, this->heart.y);
        glTexCoord2d(1, 1); glVertex2f(this->heart.x + this->heart.w, this->heart.y);
        glTexCoord2d(1, 0); glVertex2f(this->heart.x + this->heart.w, this->heart.y + this->heart.h);
        glTexCoord2d(0, 0); glVertex2f(this->heart.x, this->heart.y + this->heart.h);
    glEnd();

    x = this->healthBgCoords.x;
    y = this->healthBgCoords.y;
    w = this->healthBgCoords.w;
    h = this->healthBgCoords.h;
    glColor4ub(255, 255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, this->texHealthBg);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(x, y);
        glTexCoord2d(1, 1); glVertex2f(x + w, y);
        glTexCoord2d(1, 0); glVertex2f(x + w, y + h);
        glTexCoord2d(0, 0); glVertex2f(x, y + h);
    glEnd();

    glColor4ub(255, 255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, this->texHealth);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    x = this->healthCoords.x;
    y = this->healthCoords.y;
    w = this->healthCoords.w;
    h = this->healthCoords.h;
    for(i = 0; i < this->player->getHealth(); i++)
    {
        glBegin(GL_QUADS);
            glTexCoord2d(0, 1); glVertex2f(x, y);
            glTexCoord2d(1, 1); glVertex2f(x + w, y);
            glTexCoord2d(1, 0); glVertex2f(x + w, y + h);
            glTexCoord2d(0, 0); glVertex2f(x, y + h);
        glEnd();
        x += w + HEALTH_HART_DISTANCE;
    }

    glDisable(GL_TEXTURE_2D);
}
