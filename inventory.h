#ifndef INVENTORY_H
#define INVENTORY_H

#define ANIMATION_FRAMES        2

class Inventory
{
    private:
        SDL_Rect screen;
        SDL_Rect heart;
        unsigned int texture[ANIMATION_FRAMES];
        int textureState;
        int textureIncrement;

    public:
        Inventory(float width, float height, Timer *timer);
        ~Inventory(void);

        void render(void);
        void loadTexture(void);
        void changeTexture(void);

        void setScreenSize(float width, float height);
};

#endif  // INVENTORY_H
