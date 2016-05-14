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
    this->option[MENU_SINGLEPLAYER] = new MenuOption(tmpW - 100, 250, 220, 220);
    this->option[MENU_OPTIONS] = new MenuOption(tmpW - 300, 50, 180, 180);
    this->option[MENU_EXIT] = new MenuOption(tmpW + 150, 50, 180, 180);

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
    int w = width / 2;

    this->width = width;
    this->height = height;
    this->option[MENU_SINGLEPLAYER]->setX(w - 100);
    this->option[MENU_SINGLEPLAYER]->setY(250);
    this->option[MENU_OPTIONS]->setX(w - 300);
    this->option[MENU_OPTIONS]->setY(50);
    this->option[MENU_EXIT]->setX(w + 150);
    this->option[MENU_EXIT]->setY(50);
}

int Menu::mainLoop(int *width, int *height)
{
    SDL_Event event;
    int result = -1;

    this->option[MENU_SINGLEPLAYER]->loadTexture("start");
    this->option[MENU_OPTIONS]->loadTexture("options");
    this->option[MENU_EXIT]->loadTexture("exit");
    this->background = loadModel("data/menu/poz_menu_providna.png");
    Mix_OpenAudio(25050, MIX_DEFAULT_FORMAT, 2, 2096);
    music = Mix_LoadMUS("data/muzika/menu_music.mp3");
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
    int w = 600;
    int h = 700;
    int x = this->width / 2 - w / 2;
    int y = this->height / 2 - h / 2;

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glOrtho(0, this->width, 0, this->height, -1, 1);
    glEnable(GL_TEXTURE_2D);
    glColor4ub(255, 255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, this->background);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(x, y);
        glTexCoord2d(1, 1); glVertex2f(x + w, y);
        glTexCoord2d(1, 0); glVertex2f(x + w, y + h);
        glTexCoord2d(0, 0); glVertex2f(x, y + h);
    glEnd();
    glDisable(GL_TEXTURE_2D);
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
