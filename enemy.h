#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Player
{
    protected:
        float minX;
        float maxX;

    public:
        Enemy(float x, float y, Timer *timer);
        ~Enemy(void);
        void move(void);
        void changeTexture(void);
};

#endif  // ENEMY_H
