#include "main.h"
#include "functions.h"
#include "timer.h"
#include "fstring.h"
#include "menu.h"

Menu::Menu(int width, int height)
{
    int i;

    this->width = width;
    this->height = height;

    this->state = 0;
    this->option[MENU_SINGLEPLAYER] = new FString("SINGLE PLAYER", 10, this->height - 100, 500, 100);
    this->option[MENU_MULTIPLAYER] = new FString("MULTI PLAYER", 10, this->height - 250, 500, 100);
    this->option[MENU_EXIT] = new FString("EXIT", 10, this->height - 400, 500, 100);

    //for(i = 0; i < MENU_NUM_OF_CHOICES; i++)
    //    option[i]->loadTexture();
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
                        if(++this->state > MENU_NUM_OF_CHOICES - 1)
                            this->state = 0;
                        break;
                    case SDLK_UP:
                        if(--this->state < 0)
                            this->state = MENU_NUM_OF_CHOICES - 1;
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
    int result = 0;
    int i;

    for(i = 0; i < MENU_NUM_OF_CHOICES; i++)
        this->option[i]->loadTexture();

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

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glOrtho(0, this->width, 0, this->height, -1, 1);
    for(i = 0; i < MENU_NUM_OF_CHOICES; i++)
    {
        if(i == this->state)
            glColor4ub(255, 0, 0, 255);
        else
            glColor4ub(255, 255, 255, 255);
        this->option[i]->render();
    }
    glPopMatrix();
    SDL_GL_SwapBuffers();
}
