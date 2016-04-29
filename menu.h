#ifndef MENU_H
#define MENU_H

#define MENU_NUM_OF_CHOICES     3

#define MENU_SINGLEPLAYER       0
#define MENU_MULTIPLAYER        1
#define MENU_EXIT               2

class Menu
{
    private:
        FString *option[NUM_OF_CHOICES];
        int state;

        int events(SDL_Event event);

    public:
        Menu(void);
        ~Menu(void);

        void loadTexture(void);
        void logic(void);
        void mainLoop(void);
        void render(void);
};

#endif  // MENU_H
