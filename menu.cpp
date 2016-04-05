#include "main.h"
#include "functions.h"
#include "timer.h"
#include "fstring.h"
#include "menu.h"

Menu::Menu(void)
{
    int i;

    this->state = 0;
    this->option[MENU_SIGNLEPLAYER] = FString("SINGLE PLAYER");
    this->option[MENU_MULTIPLAYER] = FString("MULTI PLAYER");
    this->option[MENU_EXIT] = FString("EXIT");

    for(i = 0; i < MENU_NUM_OF_CHOICES; i++)
        option[i].loadTexture();
}

Menu::~Menu(void)
{
}

int Menu::events(SDL_Event event)
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            return MENU_EXIT;

        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDL_DOWN:
                        if(++this->state >= MENU_NUM_OF_OPTIONS)
                            this->state = 0;
                        break;
                    case SDL_UP:
                        if(--this->state < 0)
                            this->state = MENU_NUM_OF_OPTIONS - 1;
                        break;
                    case SDL_RETURN:
                        return state;
                        break;
                }
                break;
        }
    }
}

int Menu::mainLoop(void)
{
    while(1)
    {
        /*
         * Events
         */
        this->events(event);

        /*
         * Render
         */
        this->render();
    }
}

void Menu::render(void)
{
    int i;

    for(i = 0; i < this->option.size(); i++)
        this->option[i].render();
}
