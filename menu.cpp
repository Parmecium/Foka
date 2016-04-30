#include "main.h"
#include "functions.h"
#include "timer.h"
#include "fstring.h"
#include "menu.h"

Menu::Menu(int width, int height)
{
    int i;
    int tmpW, tmpH;

    this->width = width;
    this->height = height;

    this->state = 0;
    tmpW = this->width / 2;
    tmpH = this->height / 2;
    this->option[MENU_SINGLEPLAYER] = new FString("START", tmpW - 250, tmpH + 25, 500, 100);
    this->option[MENU_EXIT] = new FString("EXIT", tmpW - 200, tmpH - 125, 400, 100);

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
                this->width = event.resize.w;
                this->height = event.resize.h;
                /* samo privremeno, treba promeniti */
                this->option[0]->setX(this->width / 2 - 250);
                this->option[0]->setY(this->height / 2 + 25);
                this->option[1]->setX(this->width / 2 - 200);
                this->option[1]->setY(this->height / 2 - 125);
                break;
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

    return -1;
}

int Menu::mainLoop(void)
{
    SDL_Event event;
    int result = -1;
    int i;

    for(i = 0; i < MENU_NUM_OF_CHOICES; i++)
        this->option[i]->loadTexture();
    //this->background = loadModel("data/cover/cover_blur_plus_plus.png");

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

    return result;
}

void Menu::render(void)
{
    int i;
    int x = this->width / 2 - 284;      // 768
    int w = this->width / 2 + 284;
    int y = this->height / 2 - 312;     // 1024
    int h = this->height / 2 + 312;

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glOrtho(0, this->width, 0, this->height, -1, 1);
    /*
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
    */
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
