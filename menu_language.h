#ifndef MENU_LANGUAGE_H
#define MENU_LANGUAGE_H

#define MENU_NUM_OF_LANGUAGES   4

#define LANGUAGE_ENGLISH        0
#define LANGUAGE_RUSSIAN        1
#define LANGUAGE_SERBIAN        2
#define LANGUAGE_FRENCH         3

class MenuLanguage
{
    private:
        FString *option[MENU_NUM_OF_LANGUAGES];
        int state;
        int width;
        int height;
        unsigned int background;

        int events(SDL_Event event);

    public:
        MenuLanguage(int width, int height);
        ~MenuLanguage(void);

        void logic(void);
        void resize(int width, int height);
        int mainLoop(int *width, int *height);
        void render(void);
};

#endif  // MENU_LANGUAGE_H
