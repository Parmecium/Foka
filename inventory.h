#ifndef INVENTORY_H
#define INVENTORY_H

#define ANIMATION_FRAMES        2

#define HEALTH_HART_DISTANCE    10

class Inventory
{
    private:
        SDL_Rect screen;
        SDL_Rect heart;
        SDL_Rect healthCoords;
        unsigned int texture[ANIMATION_FRAMES];
        unsigned int texHealth;
        int textureState;
        int textureIncrement;
        Player *player;

    public:
        Inventory(float width, float height, Timer *timer, Player *player);
        ~Inventory(void);

        void render(void);
        void loadTexture(void);
        void changeTexture(void);

        void setScreenSize(float width, float height);
};

#endif  // INVENTORY_H
