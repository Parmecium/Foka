#include "main.h"
#include "functions.h"
#include "timer.h"
#include "fstring.h"
#include "menu.h"

Menu::Menu(void)
{
    int i;

    this->state = 1;
    this->option[MENU_SINGLEPLAYER] = new FString("SINGLE PLAYER");
    this->option[MENU_MULTIPLAYER] = new FString("MULTI PLAYER");
    this->option[MENU_EXIT] = new FString("EXIT");

    for(i = 0; i < MENU_NUM_OF_CHOICES; i++)
        option[i]->loadTexture();
}

Menu::~Menu(void)
{
    int i;
    for(i = 0; i < MENU_NUM_OF_CHOICES; i++)
        delete option[i];
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
                    case SDLK_DOWN:
                        if(++this->state > MENU_NUM_OF_CHOICES)
                            this->state = 1;
                        break;
                    case SDLK_UP:
                        if(--this->state <= 0)
                            this->state = MENU_NUM_OF_CHOICES;
                        break;
                    case SDLK_RETURN:
                        return state;
                        break;
                }
                break;
        }
    }

    return 0;
}

int Menu::mainLoop(void)
{
    SDL_Event event;
    int result;

    while(result == 0)
    {
        /*
         * Events
         */
        result = this->events(event);

        /*
         * Render
         */
        this->render();

        SDL_Delay(1000 / 30);
    }

    return result;
}

void Menu::render(void)
{
    int i;

    for(i = 0; i < MENU_NUM_OF_CHOICES; i++)
        this->option[i]->render();
}
