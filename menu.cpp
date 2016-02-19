#include "main.h"
#include "functions.h"
#include "timer.h"
#include "menu.h"

Menu::Menu(void)
{
    this->state = 0;
    this->option[0] = "Signle Player";
    this->option[1] = "Multi Player";
    this->option[2] = "Options";
    this->option[3] = "Exit";
}

Menu::~Menu(void)
{
}

void render(void)
{
}
