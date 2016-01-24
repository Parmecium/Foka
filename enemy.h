#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Player
{
    protected:
        float minX;
        float maxX;

    public:
        Enemy(int x, int y, Timer *timer);
        ~Enemy(void);
        void move(void);
};

#endif  // ENEMY_H
