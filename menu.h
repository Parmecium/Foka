#ifndef MENU_H
#define MENU_H

class Menu
{
    private:
        std::vector<FString> option;
        int state;

    public:
        Menu(void);
        ~Menu(void);

        void loadTexture(void);
        void logic(void);
        void render(void);
};

#endif  // MENU_H
