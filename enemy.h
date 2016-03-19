#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_TYPE_VOODOO           0
#define ENEMY_TYPE_BOZA             1

class Enemy : public Player
{
    protected:
        int type;
        float minX;
        float maxX;
        float speedX;
        float speedY;
        float seeRadius;

    public:
        Enemy(float x, float y, Timer *timer, int type,
                float w = 90.0f, float h = 107.0f, int interval = 90);
        ~Enemy(void);
        void move(void);
        void loadTexture();
        void seeLogic(Player *player);
};

#endif  // ENEMY_H
