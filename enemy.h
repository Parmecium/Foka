#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Player
{
    protected:
        float minX;
        float maxX;

    public:
        Enemy(float x, float y, Timer *timer,
                float w = 90.0f, float h = 107.0f, int interval = 90);
        ~Enemy(void);
        void move(void);
};

#endif  // ENEMY_H
