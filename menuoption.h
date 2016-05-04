#ifndef MENU_OPTION_H
#define MENU_OPTION_H

class MenuOption
{
    private:
        SDL_Rect coords;
        unsigned int texture[2];
        bool selected;

    public:
        MenuOption(int x, int y, int w = 100, int h = 100);
        ~MenuOption(void);

        void loadTexture(std::string fileName);
        void render(void);

        void setSelected(bool value) { this->selected = value; }
        void setX(int value) { this->coords.x = value; }
        void setY(int value) { this->coords.y = value; }
};

#endif  // MENU_OPTION_H
