#ifndef PLAYER_H
#define PLAYER_H

// Player move type definition
#define PLAYER_MOVE_ADD     0
#define PLAYER_MOVE_DELETE  1

// Player move state definition
#define PLAYER_MOVE_DOWN    2
#define PLAYER_MOVE_RIGHT   3
#define PLAYER_MOVE_UP      4
#define PLAYER_MOVE_LEFT    5

// Player angle
#define PLAYER_ANGLE_DOWN   6
#define PLAYER_ANGLE_RIGHT  7
#define PLAYER_ANGLE_UP     8
#define PLAYER_ANGLE_LEFT   9

#define PLAYER_SPEED        3

typedef struct sPlayerTexture
{
    unsigned int down[3];
    unsigned int right[3];
    unsigned int up[3];
    unsigned int left[3];
} PlayerTexture;

class Player
{
    protected:
        SDL_Rect coords;
        //SDL_Rect collCoords;
        int speedX;
        int speedY;
        int health;
        int angle;
        PlayerTexture texture;
        unsigned int shadowTexture;
        int textureState;
        int textureIncrement;

    public:
        Player(float x, float y, Timer *timer,
                float w = 90.0f, float h = 107.0f, int interval = 90);
        ~Player(void);
        void move(void);
        void changeMoveState(int type, int size);
        void loadTexture(std::string file);
        void loadTexture(int side, int num, std::string file);
        void render(SDL_Rect camera);
        void renderShadow(SDL_Rect camera);
        void changeTexture(void);
        void collision(float width, float height);
        void collision(Player *player);

        float getX(void) { return this->coords.x; };
        float getY(void) { return this->coords.y; };
        float getWidth(void) { return this->coords.w; };
        float getHeight(void) { return this->coords.h; };
        float getHealth(void) { return this->health; };
        void setX(float value) { this->coords.x = value; };
        void setY(float value) { this->coords.y = value; };
        SDL_Rect getCollCoords(void);
        int getTextureIncrement(void) { return this->textureIncrement; };
        void setTextureIncrement(int value) { this->textureIncrement = value; };

        bool isAlive(void) { return (this->health > 0 ? true : false); }
};

#endif  // PLAYER_H
