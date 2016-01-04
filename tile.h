#ifndef TILE_H
#define TILE_H

#define TILE_TYPE_UNKNOWN       0
#define TILE_TYPE_BLOCK         1

class Tile
{
    private:
        SDL_Rect coords;
        SDL_Rect collCoords;
        int type;
        unsigned int texture;

    public:
        Tile(void);
        Tile(float x, float y, float width, float height, int type);
        ~Tile(void);
        void loadTexture(void);
        void render(void);

        float getX(void) { return this->coords.x; };
        float getY(void) { return this->coords.y; };
        float getWidth(void) { return this->coords.w; };
        float getHeight(void) { return this->coords.h; };
};

#endif  // TILE_H
