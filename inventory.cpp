#include "main.h"
#include "functions.h"
#include "timer.h"
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

Inventory::Inventory(float width, float height, Timer *timer)
{
    this->screen = { 0, 0, width, height };
    this->heart = { 60, 925, 100, 100 };
    this->textureState = 0;
    this->textureIncrement = 1;

    if(timer != NULL)
        timer->add(260, new InventoryAnimator(this));
}

Inventory::~Inventory(void)
{
}

void Inventory::loadTexture(void)
{
    this->texture[0] = loadModel("data/heart/heart_tile1.png");
    this->texture[1] = loadModel("data/heart/heart_tile2.png");
}

void Inventory::changeTexture(void)
{
    this->textureState += this->textureIncrement;
    if(this->textureState <= 0 || this->textureState >= ANIMATION_FRAMES)
        this->textureIncrement *= -1;
}

void Inventory::render(void)
{
    glColor4ub(255, 255, 255, 255); // White color
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texture[this->textureState]);

    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(this->heart.x, this->heart.y);
        glTexCoord2d(1, 1); glVertex2f(this->heart.x + this->heart.w, this->heart.y);
        glTexCoord2d(1, 0); glVertex2f(this->heart.x + this->heart.w, this->heart.y + this->heart.h);
        glTexCoord2d(0, 0); glVertex2f(this->heart.x, this->heart.y + this->heart.h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
