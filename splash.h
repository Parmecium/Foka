#ifndef SPLASH_H
#define SPLASH_H

#define SPLASH_SPRITES_COUNT            9
<<<<<<< HEAD
#define SPLASH_ANIMATION_INTERVAL       111
=======
#define SPLASH_SPRITES_COUNT_FADE       11
#define SPLASH_ANIMATION_INTERVAL       100
#define SPLASH_ANIMATION_INTERVAL_FADE  111
>>>>>>> 6392836ad012fd432233e0203efa4e56455482bb

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
        unsigned int textureFade[SPLASH_SPRITES_COUNT_FADE];
        Timer *timer;
        void loadTexture(void);
        void resize(int width, int height);
        void event(SDL_Event event);

    public:
        Splash(int wWidth, int wHeight);
        ~Splash(void);
        void show(int *width, int *height);
        void changeTexture(void);
        void changeTextureFade(void);
};

#endif  // SPLASH_H
