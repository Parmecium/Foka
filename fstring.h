#ifndef FSTRING_H
#define FSTRING_H

#define FSTRING_CHAR_WIDTH      10
#define FSTRING_CHAR_HEIGHT     10

class FString
{
    private:
        SDL_Rect coords;
        int strLen;
        char *str;
        std::vector<unsigned int> textures;

    public:
        FString(char *str);
        ~FString(void);

        void render(void);
        void loadTexture(void);
};

#endif  // FSTRING_H
