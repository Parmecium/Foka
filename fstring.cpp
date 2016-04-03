#include "main.h"
#include "functions.h"
#include "fstring.h"

FString::FString(char *str)
{
    this->str = str;
    for(this->strLen = 0; *str != '\0'; this->strLen++, str++);
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
        this->textures.push_back(loadModel("/slova/slova/" + tmp[0] + ".png"));
    }
}

void FString::render(void)
{
}
