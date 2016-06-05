#ifndef SPLASH_H
#define SPLASH_H

#define SPLASH_SPRITES_COUNT            9
#define SPLASH_SPRITES_COUNT_FADE       11
#define SPLASH_SPRITES_COUNT_START      5
#define SPLASH_ANIMATION_INTERVAL       100
#define SPLASH_ANIMATION_INTERVAL_FADE  351
#define SPLASH_ANIMATION_INTERVAL_FADE  111
#define SPLASH_ANIMATION_INTERVAL_START 500


class Splash
{
    private:
        int x;
        int y;
        int width;
        int height;
        int wWidth;
        int wHeight;
        SDL_Rect startCoords;
        int time;
        bool isRunning;
        Mix_Music *music;
        int textureState;
        int textureStateFade;
        int textureStateStart;
        unsigned int texture[SPLASH_SPRITES_COUNT];
        unsigned int textureFade[SPLASH_SPRITES_COUNT_FADE];
        unsigned int textureStart[SPLASH_SPRITES_COUNT_START];
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
        void changeTextureStart(void);
};

#endif  // SPLASH_H
