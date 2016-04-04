#include "main.h"
#include "functions.h"
#include "timer.h"
#include "fstring.h"
#include "menu.h"

Menu::Menu(void)
{
    int i;

    this->state = 0;
    this->option.push_back(FString("Signle Player"));
    this->option.push_back(FString("Multi Player"));
    this->option.push_back(FString("Options"));
    this->option.push_back(FString("Exit"));

    for(i = 0; i < option.size(); i++)
        option[i].loadTexture();
}

Menu::~Menu(void)
{
}

void Menu::render(void)
{
    int i;

    for(i = 0; i < this->option.size(); i++)
        this->option[i].render();
}
