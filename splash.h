#ifndef SPLASH_H
#define SPLASH_H

#define SPLASH_SPRITES_COUNT            3

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
        unsigned int texture[SPLASH_SPRITES_COUNT];
        void loadTexture(void);
        void event(SDL_Event event);

    public:
        Splash(int wWidth, int wHeight);
        ~Splash(void);
        void show(int *width, int *height);
};

#endif  // SPLASH_H
