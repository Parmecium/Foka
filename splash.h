#ifndef SPLASH_H
#define SPLASH_H

#define SPLASH_SPRITES_COUNT            6
#define SPLASH_ANIMATION_INTERVAL       100

class Splash
{
    private:
        int x;
        int y;
        int width;
        int height;
        int wWidth;
        int wHeight;
        int time;
        Mix_Music *music;
        int textureState;
        unsigned int texture[SPLASH_SPRITES_COUNT];
        Timer *timer;
        void loadTexture(void);
        void event(SDL_Event event);

    public:
        Splash(int wWidth, int wHeight);
        ~Splash(void);
        void show(int *width, int *height);
        void changeTexture(void);
};

#endif  // SPLASH_H
