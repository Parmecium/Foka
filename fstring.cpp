#include "main.h"
#include "functions.h"
#include "fstring.h"

FString::FString(char *str, int x, int y, int w, int h)
{
    this->str = str;
    for(this->strLen = 0; *str != '\0'; this->strLen++, str++);

    this->coords.x = x;
    this->coords.y = y;
    this->coords.w = w;
    this->coords.h = h;
}

FString::~FString(void)
{
}

void FString::loadTexture(void)
{
    char *tmp;
    tmp = this->str;

    while(*(tmp++) != '\0')
    {
        //this->textures.push_back(loadModel("/slova/slova/" + (char)tmp + ".png"));
    }
}

FString &FString::operator = (const FString &rhs)
{
    /*
    char *tmp;
    memcpy(tmp, rhs.c_str(), rhs.leanght());
    */
    return *this;
}

void FString::render(void)
{
    int i;
    int x = this->coords.x;
    int y = this->coords.y;
    //int w = FSTRING_CHAR_WIDTH;
    //int h = FSTRING_CHAR_HEIGHT;
    int w = this->strLen / FSTRING_CHAR_WIDTH;
    int h = this->strLen / FSTRING_CHAR_HEIGHT;

    glEnable(GL_TEXTURE_2D);
    for(i = 0; i < textures.size(); i++)
    {
        glBindTexture(GL_TEXTURE_2D, this->textures[i]);
        glBegin(GL_QUADS);
            glTexCoord2d(0, 1); glVertex2f(x, y);
            glTexCoord2d(1, 1); glVertex2f(x + w, y);
            glTexCoord2d(1, 0); glVertex2f(x + w, y + h);
            glTexCoord2d(0, 0); glVertex2f(x, y + h);
        glEnd();
        x += w;
        y += h;
    }

    glDisable(GL_TEXTURE_2D);
}
