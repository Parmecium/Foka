#include "main.h"
#include "functions.h"
#include "timer.h"
#include "fstring.h"
#include "menu_language.h"

class BloodAnimator : public Ticker
{
    private:
        MenuLanguage *menuLanguage;

    public:
        BloodAnimator(MenuLanguage *menuLanguage)
        {
            this->menuLanguage = menuLanguage;
        }

        virtual void tick(void)
        {
            this->menuLanguage->changeBloodState();
        }
};

MenuLanguage::MenuLanguage(int width, int height)
{
    int i;
    int tmpW, tmpH;

    this->width = width;
    this->height = height;

    this->state = 0;
    this->option[LANGUAGE_ENGLISH] = new FString("ENGLISH", 0, 0, 250, 50);
    this->option[LANGUAGE_RUSSIAN] = new FString("RUSSKI", 0, 0, 250, 50);
    this->option[LANGUAGE_SERBIAN] = new FString("SRPSKI", 0, 0, 250, 50);
    this->option[LANGUAGE_FRENCH] = new FString("FRANCAIS", 0, 0, 250, 50);
    this->resize(this->width, this->height);

    this->bloodCoords.x = LANGUAGE_LOGO_X + LANGUAGE_LOGO_WIDTH - 325;
    this->bloodCoords.y = 0;
    this->bloodCoords.w = 50;
    this->bloodCoords.h = this->height;
    this->bloodState = 0;

    timer = new Timer();
    timer->add(100, new BloodAnimator(this));

    //for(i = 0; i < MENU_NUM_OF_CHOICES; i++)
    //    option[i]->loadTexture();
}

MenuLanguage::~MenuLanguage(void)
{
    int i;
    for(i = 0; i < MENU_NUM_OF_LANGUAGES; i++)
        delete option[i];
    delete timer;
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

    for(i = 0; i < MENU_NUM_OF_LANGUAGES; i++)
    {
        this->option[i]->setX(this->width / 2 + 532 / 2);
        this->option[MENU_NUM_OF_LANGUAGES - i - 1]->setY(
                this->height / 2 - 150 + i * 75);
    }
}

void MenuLanguage::changeBloodState(void)
{
    this->bloodState++;
    if(this->bloodState >= 3)
        this->bloodState = 0;
}

int MenuLanguage::mainLoop(int *width, int *height)
{
    SDL_Event event;
    int result = -1;
    int i;

    for(i = 0; i < MENU_NUM_OF_LANGUAGES; i++)
        this->option[i]->loadTexture();
    this->background = loadModel("data/cover/menu_cover.png");
    this->logo = loadModel("data/cover/Mersu_the_Pig.png");
    this->hand = loadModel("data/pointer/pointer_menu.png");
    for(i = 0; i < 3; i++)
    {
        SDL_Rect imageRect = { i * 127, 0, 126, 1024 };
        this->blood[i] = loadModel("data/cover/blood sve3.png", imageRect);
    }
    Mix_OpenAudio(25050, MIX_DEFAULT_FORMAT, 2, 2096);
    music = Mix_LoadMUS("data/muzika/beat_menu.mp3");
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
        timer->tick();
    }

    *width = this->width;
    *height = this->height;

    return result;
}

void MenuLanguage::render(void)
{
    int i;
    int x = this->width / 2 - 700 / 2;
    int w = this->width / 2 + 700 / 2;
    int y = this->height / 2 - 1000 / 2;
    int h = this->height / 2 + 1000 / 2;
    int x1, y1;
    int w1 = 175;
    int h1 = 175;

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
    glBindTexture(GL_TEXTURE_2D, this->blood[this->bloodState]);
    x = this->bloodCoords.x;
    y = this->bloodCoords.y;
    w = this->bloodCoords.w;
    h = this->bloodCoords.h;
    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(x, y);
        glTexCoord2d(1, 1); glVertex2f(x + w, y);
        glTexCoord2d(1, 0); glVertex2f(x + w, y + h);
        glTexCoord2d(0, 0); glVertex2f(x, y + h);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, this->logo);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(LANGUAGE_LOGO_X,
                                       LANGUAGE_LOGO_Y);
        glTexCoord2d(1, 1); glVertex2f(LANGUAGE_LOGO_X + LANGUAGE_LOGO_WIDTH,
                                       LANGUAGE_LOGO_Y);
        glTexCoord2d(1, 0); glVertex2f(LANGUAGE_LOGO_X + LANGUAGE_LOGO_WIDTH,
                                       LANGUAGE_LOGO_X + LANGUAGE_LOGO_HEIGHT);
        glTexCoord2d(0, 0); glVertex2f(LANGUAGE_LOGO_X,
                                       LANGUAGE_LOGO_Y + LANGUAGE_LOGO_HEIGHT);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    for(i = 0; i < MENU_NUM_OF_LANGUAGES; i++)
    {
        if(i == this->state)
        {
            x1 = option[i]->getX() - w1;
            y1 = option[i]->getY() + option[i]->getHeight() - h1;
            glColor4ub(255, 255, 255, 255);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, this->hand);
            glBegin(GL_QUADS);
                glTexCoord2d(0, 1), glVertex2f(x1, y1);
                glTexCoord2d(1, 1); glVertex2f(x1 + w1, y1);
                glTexCoord2d(1, 0); glVertex2f(x1 + w1, y1 + h1);
                glTexCoord2d(0, 0); glVertex2f(x1, y1 + h1);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            glColor4ub(185, 0, 0, 155);
        } else
            glColor4ub(255, 255, 255, 255);
        this->option[i]->render();
    }
    glPopMatrix();
    SDL_GL_SwapBuffers();
}
