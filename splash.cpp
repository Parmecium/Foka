#include "main.h"
#include "functions.h"
#include "splash.h"

Splash::Splash(float wWidth, float wHeight)
{
    this->width = 300;
    this->height = 300;
    this->wWidth = wWidth;
    this->wHeight = wHeight;
    this->x = wWidth / 2 - this->width / 2;
    this->y = wHeight / 2 - this->height / 2;
    this->time = 4000;
    this->music = NULL;
    loadTexture();
}

Splash::~Splash(void)
{
}

void Splash::loadTexture(void)
{
    this->texture = loadModel("data/foka logo.png");
}

void Splash::show(void)
{
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("data/muzika/music.wav");
    Mix_PlayMusic(music, -1);

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glOrtho(0, this->wWidth, 0, this->wHeight, -1, 1);

    // Begin render

    glColor4ub(255, 255, 255, 255); // White color
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(this->wWidth, 0);
        glVertex2f(this->wWidth, this->wHeight);
        glVertex2f(0, wHeight);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(this->x, this->y);
        glTexCoord2d(1, 1); glVertex2f(this->x + this->width, this->y);
        glTexCoord2d(1, 0); glVertex2f(this->x + this->width, this->y + this->height);
        glTexCoord2d(0, 0); glVertex2f(this->x, this->y + this->height);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // End render

    glPopMatrix();
    SDL_GL_SwapBuffers();
    SDL_Delay(time);
    Mix_FreeMusic(music);
}
