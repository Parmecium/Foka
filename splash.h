#ifndef SPLASH_H
#define SPLASH_H

class Splash
{
    private:
        float x;
        float y;
        float width;
        float height;
        float wWidth;
        float wHeight;
        int time;
        Mix_Music *music;
        unsigned int texture[3];
        void loadTexture(void);

    public:
        Splash(float wWidth, float wHeight);
        ~Splash(void);
        void show(void);
};

#endif  // SPLASH_H
