#include "main.h"
#include "functions.h"
#include "splash.h"

Splash::Splash(int wWidth, int wHeight)
{
    this->width = 450;
    this->height = 600;
    this->wWidth = wWidth;
    this->wHeight = wHeight;
    this->x = wWidth / 2 - this->width / 2;
    this->y = wHeight / 2 - this->height / 2;
    this->time = 8000;
    this->music = NULL;
    loadTexture();
}

Splash::~Splash(void)
{
}

void Splash::loadTexture(void)
{
    this->texture[0] = loadModel("data/cover/Mersu_the_Pig.png");
    this->texture[1] = loadModel("data/cover/Mersu_the_Pig.png");
    this->texture[2] = loadModel("data/cover/Mersu_the_Pig.png");
}

void Splash::event(SDL_Event event)
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_VIDEORESIZE)
        {
            this->wWidth = event.resize.w;
            this->wHeight = event.resize.h;
            SDL_SetVideoMode(this->wWidth, this->wHeight, 32, SDL_OPENGL | SDL_RESIZABLE);
            glViewport(0, 0, this->wWidth, this->wHeight);
        }
    }
}

void Splash::show(int *width, int *height)
{
    int i;
    float j;
    int w1 = this->width / 2;
    int h1 = this->height / 2;
    int x1 = this->wWidth / 2 - w1 / 2;
    int y1 = this->wHeight / 2 - h1 / 2;
    SDL_Event event;

    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("data/muzika/opening_splash.mp3");
    Mix_PlayMusic(music, -1);

    //glClear(GL_COLOR_BUFFER_BIT);
    //glPushMatrix();
    //glOrtho(0, this->wWidth, 0, this->wHeight, -1, 1);

    // Begin render

    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 3000 / 8; j += 10)
        {
            this->event(event);

            glClear(GL_COLOR_BUFFER_BIT);
            glPushMatrix();
            glOrtho(0, this->wWidth, 0, this->wHeight, -1, 1);

            /*
            glColor4ub(0, 0, 0, 255);
            glBegin(GL_QUADS);
                glVertex2f(0, 0);
                glVertex2f(this->wWidth, 0);
                glVertex2f(this->wWidth, this->wHeight);
                glVertex2f(0, wHeight);
            glEnd();
            */

            glColor4ub(255, 255, 255, 255);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, this->texture[i % 2]);
            glBegin(GL_QUADS);
                glTexCoord2d(0, 1); glVertex2f(x1, y1);
                glTexCoord2d(1, 1); glVertex2f(x1 + w1, y1);
                glTexCoord2d(1, 0); glVertex2f(x1 + w1, y1 + h1);
                glTexCoord2d(0, 0); glVertex2f(x1, y1 + h1);
            glEnd();
            glDisable(GL_TEXTURE_2D);

            glPopMatrix();
            SDL_GL_SwapBuffers();
            //SDL_Delay(3000 / 8);
            //SDL_Delay(30 / 1000);
            SDL_Delay(5);
        }
    }

    j = 0;
    while(1)
    {
        this->event(event);

        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glOrtho(0, this->wWidth, 0, this->wHeight, -1, 1);

        /*
        glColor4ub(0, 0, 0, 255);
        glBegin(GL_QUADS);
            glVertex2f(0, 0);
            glVertex2f(this->wWidth, 0);
            glVertex2f(this->wWidth, wHeight);
            glVertex2f(0, wHeight);
        glEnd();
        */

        glColor4ub(255, 255, 255, 255);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->texture[2]);
        glBegin(GL_QUADS);
            glTexCoord2d(0, 1); glVertex2f(this->x, this->y);
            glTexCoord2d(1, 1); glVertex2f(this->x + this->width, this->y);
            glTexCoord2d(1, 0); glVertex2f(this->x + this->width, this->y + this->height);
            glTexCoord2d(0, 0); glVertex2f(this->x, this->y + this->height);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        glPopMatrix();
        SDL_GL_SwapBuffers();

        //SDL_Delay(time - 3000);
        //SDL_Delay(30 / 1000);
        //j += 30.0f / 1000.0f;
        SDL_Delay(10);
        j += 10;
        if(j > time - 4500)
            break;
    }

    // End render

    *width = this->wWidth;
    *height = this->wHeight;

    Mix_FreeMusic(music);
}
