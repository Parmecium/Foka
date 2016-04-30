#ifndef MENU_H
#define MENU_H

#define MENU_NUM_OF_CHOICES     2

#define MENU_SINGLEPLAYER       0
//#define MENU_MULTIPLAYER        1
#define MENU_EXIT               1

class Menu
{
    private:
        FString *option[MENU_NUM_OF_CHOICES];
        int state;
        int width;
        int height;
        unsigned int background;

        int events(SDL_Event event);

    public:
        Menu(int width, int height);
        ~Menu(void);

        void loadTexture(void);
        void logic(void);
        int mainLoop(void);
        void render(void);
};

#endif  // MENU_H
