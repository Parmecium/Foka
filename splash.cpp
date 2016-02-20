#include "main.h"
#include "functions.h"
#include "splash.h"

Splash::Splash(float wWidth, float wHeight)
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
    this->texture[0] = loadModel("data/splash/splash1.png");
    this->texture[1] = loadModel("data/splash/splash2.png");
    this->texture[2] = loadModel("data/splash/splash3.png");
}

void Splash::show(void)
{
    int i;
    float x1 = this->x + (this->width - this->x) / 4;
    float y1 = this->y + (this->height - this->y) / 4;
    float w1 = this->width - this->width / 4;
    float h1 = this->height - this->height / 4;

    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("data/muzika/opening_splash.mp3");
    Mix_PlayMusic(music, -1);

    //glClear(GL_COLOR_BUFFER_BIT);
    //glPushMatrix();
    //glOrtho(0, this->wWidth, 0, this->wHeight, -1, 1);

    // Begin render

    for(i = 0; i < 4; i++)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glOrtho(0, this->wWidth, 0, this->wHeight, -1, 1);

        glColor4ub(0, 0, 0, 255);
        glBegin(GL_QUADS);
            glVertex2f(0, 0);
            glVertex2f(this->wWidth, 0);
            glVertex2f(this->wWidth, this->wHeight);
            glVertex2f(0, wHeight);
        glEnd();

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
        SDL_Delay(3000 / 4);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glOrtho(0, this->wWidth, 0, this->wHeight, -1, 1);

    glColor4ub(0, 0, 0, 255);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(this->wWidth, 0);
        glVertex2f(this->wWidth, wHeight);
        glVertex2f(0, wHeight);
    glEnd();

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

    SDL_Delay(time - 3000);

    // End render

    Mix_FreeMusic(music);
}
