#ifndef MENU_H
#define MENU_H

#define MENU_NUM_OF_CHOICES     3

#define MENU_SINGLEPLAYER       1
#define MENU_OPTIONS            0
#define MENU_EXIT               2

class Menu
{
    private:
        MenuOption *option[MENU_NUM_OF_CHOICES];
        int state;
        int width;
        int height;
        unsigned int background;
        Mix_Music *music;
        Mix_Chunk *selectedSound;

        int events(SDL_Event event);

    public:
        Menu(int width, int height);
        ~Menu(void);

        void logic(void);
        void resize(int width, int height);
        void loadTexture(void);
        int mainLoop(int *width, int *height);
        void render(void);
};

#endif  // MENU_H
