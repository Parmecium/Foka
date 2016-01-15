#ifndef MAP_H
#define MAP_H

class Map
{
    private:
        float width;
        float height;
        float sWidth;
        float sHeight;

        Player *player;
        Player *player2;
        std::vector<Tile *> tile;
        Timer *timer;
        SDL_Rect camera;

    public:
        Map(float width, float height, float sWidth, float sHeight);
        Map(std::string path);
        ~Map(void);

        void setCamera(void);
        void loadTexture(void);
        void logic(void);
        void render(void);

        float getWidth(void) { return this->width; }
        float getHeight(void) { return this->height; }
        Player *getPlayer(void) { return this->player; }
        Player *getPlayer2(void) { return this->player2; }
};

#endif  // MAP_H