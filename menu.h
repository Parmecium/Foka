#ifndef MENU_H
#define MENU_H

#define MENU_COUNT_OPTIONS          4

class Menu
{
    private:
        char *option[4];
        int state;

    public:
        Menu(void);
        ~Menu(void);

        void loadTexture(void);
        void logic(void);
        void render(void);
};

#endif  // MENU_H