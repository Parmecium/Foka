#ifndef MAP_H
#define MAP_H

class Map
{
    private:
        int width;
        int height;
        int sWidth;
        int sHeight;

        Player *player;
        Player *player2;
        Inventory *inventory;
        std::vector<Tile *> tile;
        std::vector<Enemy *> enemy;
        Timer *timer;
        SDL_Rect camera;
        SDL_Rect bgCoords;
        unsigned int bgImg;
        Mix_Music *music;

    public:
        Map(float width, float height, float sWidth, float sHeight);
        Map(std::string path);
        ~Map(void);

        void setCamera(void);
        void loadTexture(void);
        void loadMusic(void);
        void renderBackground(void);
        void resized(void);
        bool logic(void);
        void render(void);

        float getWidth(void) { return this->width; }
        float getHeight(void) { return this->height; }
        Player *getPlayer(void) { return this->player; }
        Player *getPlayer2(void) { return this->player2; }
        void setSWidth(float value) { this->sWidth = value; this->camera.w = this->sWidth; }
        void setSHeight(float value) { this->sHeight = value; this->camera.h = this->sHeight; }
};

#endif  // MAP_H
