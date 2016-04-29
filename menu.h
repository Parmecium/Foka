#ifndef MENU_H
#define MENU_H

#define MENU_NUM_OF_CHOICES     3

#define MENU_SINGLEPLAYER       1
#define MENU_MULTIPLAYER        2
#define MENU_EXIT               3

class Menu
{
    private:
        FString *option[MENU_NUM_OF_CHOICES];
        int state;

        int events(SDL_Event event);

    public:
        Menu(void);
        ~Menu(void);

        void loadTexture(void);
        void logic(void);
        int mainLoop(void);
        void render(void);
};

#endif  // MENU_H
