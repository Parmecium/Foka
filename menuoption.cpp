#include "main.h"
#include "functions.h"
#include "menuoption.h"

MenuOption::MenuOption(int x, int y, int w, int h)
{
    this->coords.x = x;
    this->coords.y = y;
    this->coords.w = w;
    this->coords.h = h;
    this->selected = false;
}

MenuOption::~MenuOption(void)
{
}

void MenuOption::loadTexture(std::string fileName)
{
    this->texture[0] = loadModel("data/menu/" + fileName + ".png");
    this->texture[1] = loadModel("data/menu/" + fileName + "_selected.png");
}

void MenuOption::render(void)
{
    int x = this->coords.x;
    int y = this->coords.y;
    int w = this->coords.w;
    int h = this->coords.h;

    glColor4ub(255, 255, 255, 255);
    glEnable(GL_TEXTURE_2D);
    if(this->selected)
        glBindTexture(GL_TEXTURE_2D, this->texture[1]);
    else
        glBindTexture(GL_TEXTURE_2D, this->texture[0]);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(x, y);
        glTexCoord2d(1, 1); glVertex2f(x + w, y);
        glTexCoord2d(1, 0); glVertex2f(x + w, y + h);
        glTexCoord2d(0, 0); glVertex2f(x, y + h);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
