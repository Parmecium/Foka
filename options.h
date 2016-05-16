#ifndef OPTIONS_H
#define OPTIONS_H

#define OPTIONS_MUSIC_NUMBERS   8
#define OPTIONS_EFFECT_NUMBERS  8

#define OPTIONS_EXIT            0
#define OPTIONS_MUSIC_UP        1
#define OPTIONS_MUSIC_DOWN      2

class Options
{
    private:
        int width;
        int height;
        SDL_Rect bgCoords;
        unsigned int bgImage;
        SDL_Rect musicCoords;
        FString *musicString;
        SDL_Rect effectCoords;
        FString *effectString;

        int events(SDL_Event event);

    public:
        Options(int width, int height);
        ~Options(void);

        void logic(void);
        void resize(int width, int height);
        void mainLoop(int *width, int *height, int *musicVolume, int *effectVolume);
        void render(int musicVolume, int effectVolume);
};

#endif  // OPTIONS_H
