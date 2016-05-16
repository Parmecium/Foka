#include "main.h"
#include "functions.h"
#include "fstring.h"
#include "options.h"

Options::Options(int width, int height)
{
    this->width = width;
    this->height = height;

    musicString = new FString("MUSIC", 0, 0, 250, 50);
    bgCoords.w = 600;
    bgCoords.h = 600;
    musicCoords.w = 10;
    musicCoords.h = 50;
    this->resize(this->width, this->height);
}

Options::~Options(void)
{
    delete musicString;
    //delete effectString;
}

void Options::resize(int width, int height)
{
    int t, l;

    this->width = width;
    this->height = height;

    bgCoords.x = this->width / 2 - 300;
    bgCoords.y = this->height / 2 - 300;
    musicString->setX(this->width / 2 - musicString->getWidth());
    musicString->setY(this->height / 2 - musicString->getHeight() - 10);
    musicCoords.x = musicString->getX() + musicString->getWidth() + 10;
    musicCoords.y = musicString->getY();
}

int Options::events(SDL_Event event)
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            return OPTIONS_EXIT;

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
                    case SDLK_ESCAPE:
                        return OPTIONS_EXIT;
                        break;
                    case SDLK_RIGHT:
                        return OPTIONS_MUSIC_UP;
                        break;
                    case SDLK_LEFT:
                        return OPTIONS_MUSIC_DOWN;
                        break;
                }
                break;
        }
    }

    return -1;
}

void Options::mainLoop(int *width, int *height, int *musicVolume, int *effectVolume)
{
    SDL_Event event;
    int result;
    int i;

    this->bgImage = loadModel("data/menu/options_box/options_box.png");
    musicString->loadTexture();

    do
    {
        /*
         * Events
         */
        result = this->events(event);

        /*
         * Logic
         */
        switch(result)
        {
            case OPTIONS_MUSIC_UP:
                if(*musicVolume < 8)
                    (*musicVolume)++;
                result = -1;
                break;
            case OPTIONS_MUSIC_DOWN:
                if(*musicVolume > 0)
                    (*musicVolume)--;
                result = -1;
                break;
        }

        /*
         * Render
         */
        this->render(*musicVolume, *effectVolume);

        SDL_Delay(1000 / 30);
    } while(result < 0);

    *width = this->width;
    *height = this->height;
}

void Options::render(int musicVolume, int effectVolume)
{
    int i;
    int x = this->bgCoords.x;
    int y = this->bgCoords.y;
    int w = this->bgCoords.w;
    int h = this->bgCoords.h;

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glOrtho(0, this->width, 0, this->height, -1, 1);
    glColor4ub(255, 255, 255, 255);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->bgImage);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(x, y);
        glTexCoord2d(1, 1); glVertex2f(x + w, y);
        glTexCoord2d(1, 0); glVertex2f(x + w, y + h);
        glTexCoord2d(0, 0); glVertex2f(x, y + h);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glColor4ub(128, 0, 15, 255);
    musicString->render();
    x = this->musicCoords.x;
    y = this->musicCoords.y;
    w = this->musicCoords.w;
    h = this->musicCoords.h;
    for(i = 0; i < musicVolume; i++)
    {
        if(i < musicVolume)
        {
            if(i < 4)
                glColor4ub(0, 255, 0, 255);
            else if(i < 7)
                glColor4ub(255, 255, 0, 255);
            else
                glColor4ub(255, 0, 0, 255);
        }
        glBegin(GL_QUADS);
            glTexCoord2d(0, 1); glVertex2f(x, y);
            glTexCoord2d(1, 1); glVertex2f(x + w, y);
            glTexCoord2d(1, 0); glVertex2f(x + w, y + h);
            glTexCoord2d(0, 0); glVertex2f(x, y + h);
        glEnd();
        x += 2 * w;
    }
    glPopMatrix();
    SDL_GL_SwapBuffers();
}
