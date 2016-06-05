#include "main.h"
#include "functions.h"
#include "timer.h"
#include "splash.h"

class SplashAnimator : public Ticker
{
    private:
        Splash *splash;

    public:
        SplashAnimator(Splash *splash)
        {
            this->splash = splash;
        }

        virtual void tick(void)
        {
            this->splash->changeTexture();
        }
};

class SplashFadeAnimator : public Ticker
{
    private:
        Splash *splash;

    public:
        SplashFadeAnimator(Splash *splash)
        {
            this->splash = splash;
        }

        virtual void tick(void)
        {
            this->splash->changeTextureFade();
        }
};

class SplashStartAnimator : public Ticker
{
    private:
        Splash *splash;

    public:
        SplashStartAnimator(Splash *splash)
        {
            this->splash = splash;
        }

        virtual void tick(void)
        {
            this->splash->changeTextureStart();
        }
};

Splash::Splash(int wWidth, int wHeight)
{
    this->width = 1480;
    this->height = 740;
    this->wWidth = wWidth;
    this->wHeight = wHeight;
    this->x = wWidth / 2 - this->width / 2;
    this->y = wHeight / 2 - this->height / 2;
    this->time = 6200;
    this->music = NULL;
    this->timer = new Timer();
    this->textureState = 0;
    this->textureStateFade = 0;
    this->textureStateStart = 0;
    this->startCoords.x = 0;
    this->startCoords.y = 0;
    this->startCoords.w = 200;
    this->startCoords.h = 50;
    this->isRunning = true;
    loadTexture();
}

Splash::~Splash(void)
{
    delete this->timer;
}

void Splash::loadTexture(void)
{
    int i;
    SDL_Rect imgForCrop;

    imgForCrop = { 0, 0, 102, 86 };
    for(i = 0; i < SPLASH_SPRITES_COUNT_FADE; i++)
    {
        this->textureFade[i] = loadModel("data/cover/splash1.png", imgForCrop);
        imgForCrop.x += imgForCrop.w;
    }

    imgForCrop = { 0, 0, 142, 64 };
    for(i = 0; i < SPLASH_SPRITES_COUNT; i++)
    {
        this->texture[i] = loadModel("data/cover/splash2.png", imgForCrop);
        imgForCrop.x += imgForCrop.w;
    }

    imgForCrop = { 0, 0, 32, 32 };
    for(i = 0; i < SPLASH_SPRITES_COUNT_START; i++)
    {
        this->textureStart[i] = loadModel("data/cover/start.png", imgForCrop);
        imgForCrop.x += imgForCrop.w;
    }
}

void Splash::event(SDL_Event event)
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_VIDEORESIZE)
        {
            this->resize(event.resize.w, event.resize.h);
            SDL_SetVideoMode(this->wWidth, this->wHeight, 32, SDL_OPENGL | SDL_RESIZABLE);
            glViewport(0, 0, this->wWidth, this->wHeight);
        } else if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_RETURN:
                    this->isRunning = false;
                    break;
            }
        }
    }
}

void Splash::changeTexture(void)
{
    textureState++;
    if(textureState >= SPLASH_SPRITES_COUNT)
        textureState = 0;
}

void Splash::changeTextureFade(void)
{
    if(textureStateFade >= SPLASH_SPRITES_COUNT_FADE)
        return;

    textureStateFade++;
    if(textureStateFade >= SPLASH_SPRITES_COUNT_FADE)
    {
        this->timer->add(SPLASH_ANIMATION_INTERVAL,
                new SplashAnimator(this));
        this->timer->add(SPLASH_ANIMATION_INTERVAL_START,
                new SplashStartAnimator(this));
    }
}

void Splash::changeTextureStart(void)
{
    textureStateStart++;
    if(textureStateStart >= SPLASH_SPRITES_COUNT_START)
        textureStateStart = 0;
}

void Splash::resize(int width, int height)
{
    this->wWidth = width;
    this->wHeight = height;
    this->x = this->wWidth / 2 - this->width / 2;
    this->y = this->wHeight / 2 - this->height / 2;
}

void Splash::show(int *width, int *height)
{
    int i;
    float j;
    SDL_Event event;

    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("data/muzika/secret_door.mp3");
    Mix_PlayMusic(music, -1);

    this->timer->add(SPLASH_ANIMATION_INTERVAL_FADE,
            new SplashFadeAnimator(this));

    //glClear(GL_COLOR_BUFFER_BIT);
    //glPushMatrix();
    //glOrtho(0, this->wWidth, 0, this->wHeight, -1, 1);

    SDL_Delay(1500);

    // Begin render

    j = 0;
    while(this->isRunning)
    {
        this->event(event);

        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glOrtho(0, this->wWidth, 0, this->wHeight, -1, 1);

        glColor4ub(255, 255, 255, 255);
        glEnable(GL_TEXTURE_2D);
        if(this->textureStateFade < SPLASH_SPRITES_COUNT_FADE)
            glBindTexture(GL_TEXTURE_2D,
                    this->textureFade[this->textureStateFade]);
        else
            glBindTexture(GL_TEXTURE_2D, this->texture[this->textureState]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBegin(GL_QUADS);
            glTexCoord2d(0, 1); glVertex2f(this->x, this->y);
            glTexCoord2d(1, 1); glVertex2f(this->x + this->width, this->y);
            glTexCoord2d(1, 0); glVertex2f(this->x + this->width, this->y + this->height);
            glTexCoord2d(0, 0); glVertex2f(this->x, this->y + this->height);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->textureStart[this->textureStateStart]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        int x = this->startCoords.x;
        int y = this->startCoords.y;
        int w = this->startCoords.w;
        int h = this->startCoords.h;
        glBegin(GL_QUADS);
            glTexCoord2d(0, 1); glVertex2f(x, y);
            glTexCoord2d(1, 1); glVertex2f(x + w, y);
            glTexCoord2d(1, 0); glVertex2f(x + w, y + h);
            glTexCoord2d(0, 0); glVertex2f(x, y + h);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        glPopMatrix();
        SDL_GL_SwapBuffers();

        //SDL_Delay(time - 3000);
        //SDL_Delay(30 / 1000);
        //j += 30.0f / 1000.0f;
        SDL_Delay(10);
        j += 10;
        this->timer->tick();
        //if(j > time)
        //    break;
    }

    // End render

    *width = this->wWidth;
    *height = this->wHeight;

    Mix_FreeMusic(music);
}
