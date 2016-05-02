#include "main.h"
#include "functions.h"
#include "timer.h"
#include "fstring.h"
#include "menuoption.h"
#include "menu.h"

Menu::Menu(int width, int height)
{
    int i;
    int tmpW, tmpH;

    this->width = width;
    this->height = height;

    this->state = 1;
    tmpW = this->width / 2;
    tmpH = this->height / 2;
    this->option[MENU_SINGLEPLAYER] = new MenuOption(tmpW - 50, 200, 100, 100);
    this->option[MENU_OPTIONS] = new MenuOption(tmpW - 250, 150, 100, 100);
    this->option[MENU_EXIT] = new MenuOption(tmpW + 200, 150, 100, 100);

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
            case SDL_VIDEORESIZE:
                this->resize(event.resize.w, event.resize.h);
                SDL_SetVideoMode(this->width, this->height, 32, SDL_OPENGL | SDL_RESIZABLE);
                glViewport(0, 0, this->width, this->height);
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        if(++this->state > MENU_NUM_OF_CHOICES - 1)
                            this->state = 0;
                        break;
                    case SDLK_LEFT:
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

    return -1;
}

void Menu::resize(int width, int height)
{
    this->width = width;
    this->height = height;
    //this->option[0]->setX(this->width / 2 - 187.5);
    //this->option[0]->setY(this->height / 2 + 100);
    //this->option[1]->setX(this->width / 2 - 150);
    //this->option[1]->setY(this->height / 2 - 25);
}

int Menu::mainLoop(int *width, int *height)
{
    SDL_Event event;
    int result = -1;

    this->option[MENU_SINGLEPLAYER]->loadTexture("start");
    this->option[MENU_OPTIONS]->loadTexture("options");
    this->option[MENU_EXIT]->loadTexture("exit");
    //this->background = loadModel("data/cover/cover_blur_plus_plus.png");
    Mix_OpenAudio(25050, MIX_DEFAULT_FORMAT, 2, 2096);
    music = Mix_LoadMUS("data/muzika/menu_theme.mp3");
    Mix_VolumeMusic(MIX_MAX_VOLUME);
    Mix_PlayMusic(music, -1);

    while(result < 0)
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

    *width = this->width;
    *height = this->height;

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
            this->option[i]->setSelected(true);
        else
            this->option[i]->setSelected(false);
        this->option[i]->render();
    }
    glPopMatrix();
    SDL_GL_SwapBuffers();
}
