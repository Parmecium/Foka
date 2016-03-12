#include "main.h"
#include "functions.h"
#include "timer.h"
#include "player.h"
#include "enemy.h"

class EnemyAnimator : public Ticker
{
    private:
        Enemy *enemy;

    public:
        EnemyAnimator(Enemy *enemy)
        {
            this->enemy = enemy;
        }

        virtual void tick(void)
        {
            this->enemy->changeTexture();
        }
};

Enemy::Enemy(float x, float y, Timer *timer, float w, float h, int interval)
    : Player(x, y, NULL, w, h, interval)
{
    this->moveState.right = true;
    this->minX = x;
    this->maxX = x + 500;
    this->speed = 3.0;

    this->textureIncrement = 1;

    timer->add(interval, new EnemyAnimator(this));
}

Enemy::~Enemy(void)
{
}

void Enemy::move(void)
{
    if(this->moveState.right == true)
    {
        this->coords.x += this->speed;
        this->angle = PLAYER_ANGLE_RIGHT;
    } else if(this->moveState.left == true)
    {
        this->coords.x -= this->speed;
        this->angle = PLAYER_ANGLE_LEFT;
    }
    if(this->coords.x <= this->minX)
    {
        this->moveState.left = false;
        this->moveState.right = true;
    } else if(this->coords.x >= this->maxX)
    {
        this->moveState.right = false;
        this->moveState.left = true;
    }
}
