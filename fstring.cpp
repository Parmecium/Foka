#include "main.h"
#include "functions.h"
#include "fstring.h"

FString::FString(char *str, int x, int y, int w, int h)
{
    this->strLen = strlen(str);
    this->str = (char *)malloc(this->strLen + 1);
    strcpy(this->str, str);

    this->coords.x = x;
    this->coords.y = y;
    this->coords.w = w;
    this->coords.h = h;
}

FString::~FString(void)
{
    free(str);
}

void FString::loadTexture(void)
{
    std::string tmp;
    char *str;

    for(str = this->str; *str != '\0'; str++)
    {
        if(((char)(*str)) == ' ')
            continue;
        tmp = std::string("data/font/");
        tmp.append(1, (char)(*str));
        tmp += std::string(".png");
        this->textures.push_back(loadModel(tmp));
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
    //int w = this->coords.w / FSTRING_CHAR_WIDTH;
    int w = this->coords.w / (this->strLen + 1);
    int h = this->coords.h;

    glColor4ub(255, 255, 255, 255);
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
        x += w + 5;
        //y += h;
    }

    glDisable(GL_TEXTURE_2D);
}
