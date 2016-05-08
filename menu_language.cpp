#include "main.h"
#include "functions.h"
#include "timer.h"
#include "fstring.h"
#include "menu_language.h"

MenuLanguage::MenuLanguage(int width, int height)
{
    int i;
    int tmpW, tmpH;

    this->width = width;
    this->height = height;

    this->state = 0;
    tmpW = this->width / 2;
    tmpH = this->height / 2;
    this->option[LANGUAGE_ENGLISH] = new FString("ENGLISH", 0, 0, 250, 50);
    this->option[LANGUAGE_RUSSIAN] = new FString("RUSSIAN", 0, 0, 250, 50);
    this->option[LANGUAGE_SERBIAN] = new FString("SRPSKI", 0, 0, 200, 50);
    this->option[LANGUAGE_FRENCH] = new FString("FRENCH", 0, 0, 200, 50);
    this->resize(this->width, this->height);

    //for(i = 0; i < MENU_NUM_OF_CHOICES; i++)
    //    option[i]->loadTexture();
}

MenuLanguage::~MenuLanguage(void)
{
    int i;
    for(i = 0; i < MENU_NUM_OF_LANGUAGES; i++)
        delete option[i];
}

int MenuLanguage::events(SDL_Event event)
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            return LANGUAGE_ENGLISH;

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
                    case SDLK_DOWN:
                        if(++this->state > MENU_NUM_OF_LANGUAGES - 1)
                            this->state = 0;
                        break;
                    case SDLK_UP:
                        if(--this->state < 0)
                            this->state = MENU_NUM_OF_LANGUAGES - 1;
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

void MenuLanguage::resize(int width, int height)
{
    int i;

    this->width = width;
    this->height = height;
    this->option[0]->setX(this->width / 2 - 187.5);
    this->option[0]->setY(this->height / 2 + 100);
    this->option[1]->setX(this->width / 2 - 150);
    this->option[1]->setY(this->height / 2 - 25);

    for(i = 0; i < MENU_NUM_OF_LANGUAGES; i++)
    {
        this->option[i]->setX(this->width - option[i]->getWidth() - 10);
        this->option[MENU_NUM_OF_LANGUAGES - i - 1]->setY(
                this->height / 2 - 150 + i * 75);
    }
}

int MenuLanguage::mainLoop(int *width, int *height)
{
    SDL_Event event;
    int result = -1;
    int i;

    for(i = 0; i < MENU_NUM_OF_LANGUAGES; i++)
        this->option[i]->loadTexture();
    this->background = loadModel("data/cover/menu_cover.png");
    //Mix_OpenAudio(25050, MIX_DEFAULT_FORMAT, 2, 2096);
    //music = Mix_LoadMUS("data/muzika/menu.mp3");
    //Mix_VolumeMusic(MIX_MAX_VOLUME);
    //Mix_PlayMusic(music, -1);

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

void MenuLanguage::render(void)
{
    int i;
    int x = 0;
    int w = this->width;
    int y = 0;
    int h = this->height;

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glOrtho(0, this->width, 0, this->height, -1, 1);
    glColor4ub(255, 255, 255, 255);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->background);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(x, y);
        glTexCoord2d(1, 1); glVertex2f(w, y);
        glTexCoord2d(1, 0); glVertex2f(w, h);
        glTexCoord2d(0, 0); glVertex2f(x, h);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    for(i = 0; i < MENU_NUM_OF_LANGUAGES; i++)
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
