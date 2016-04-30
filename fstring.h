#ifndef FSTRING_H
#define FSTRING_H

#define FSTRING_CHAR_WIDTH      50
#define FSTRING_CHAR_HEIGHT     50

class FString
{
    private:
        SDL_Rect coords;
        int strLen;
        char *str;
        std::vector<unsigned int> textures;

    public:
        FString(char *str, int x = 0, int y = 0, int w = 0, int h = 0);
        ~FString(void);

        void render(void);
        void loadTexture(void);

        FString &operator = (const FString &rhs);

        char *c_str(void) { return this->str; }
        int length(void) { return this->strLen; }
        void setX(int value) { this->coords.x = value; }
        void setY(int value) { this->coords.y = value; }
};

#endif  // FSTRING_H
