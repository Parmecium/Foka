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

Enemy::Enemy(float x, float y, Timer *timer, int type,
        float w, float h, int interval)
    : Player(x, y, NULL, w, h, interval)
{
    this->moveState.right = true;
    this->minX = x;
    this->maxX = x + 500;
    this->speedX = 0;
    this->speedY = 0;
    this->type = type;

    this->seeArea.x = this->coords.x - 150;
    this->seeArea.y = this->coords.y - 150;
    this->seeArea.w = this->coords.w + 2 * 150;
    this->seeArea.h = this->coords.h + 2 * 150;

    this->textureIncrement = 1;

    timer->add(interval, new EnemyAnimator(this));
}

Enemy::~Enemy(void)
{
}

void Enemy::move(void)
{
    if(this->speedY > 0)
        this->angle = PLAYER_ANGLE_UP;
    else if(this->speedY < 0)
        this->angle = PLAYER_ANGLE_DOWN;
    if(this->speedX > 0)
        this->angle = PLAYER_ANGLE_RIGHT;
    else if(this->speedX < 0)
        this->angle = PLAYER_ANGLE_RIGHT;
    this->coords.x += this->speedX;
    this->coords.y += this->speedY;
    this->seeArea.x += this->speedX;
    this->seeArea.y += this->speedY;
}

void Enemy::loadTexture()
{
    int i;

    switch(type)
    {
        case ENEMY_TYPE_VOODOO:
            this->texture.down[0] = loadModel("data/voodoo/voodoo_purple1.png");
            this->texture.down[1] = loadModel("data/voodoo/voodoo_purple2.png");
            this->texture.down[2] = loadModel("data/voodoo/voodoo_purple3.png");
            for(i = 0; i < 3; i++)
            {
                this->texture.up[i] = texture.down[i];
                this->texture.left[i] = texture.down[i];
                this->texture.right[i] = texture.down[i];
            }
            break;
    }

    this->shadowTexture = loadModel("data/shadow2.png");
}

void Enemy::seeLogic(Player *player)
{
    float xe = this->coords.x + this->coords.w / 2;
    float ye = this->coords.y + this->coords.h / 2;
    float xp = player->getX() + player->getWidth() / 2;
    float yp = player->getY() + player->getHeight() / 2;

    if(player->getX() + player->getWidth() > this->seeArea.x &&
       player->getX() < this->seeArea.x + this->seeArea.w &&
       player->getY() + player->getHeight() > this->seeArea.y &&
       player->getY() < this->seeArea.y + this->seeArea.h)
    {
        if(xe > xp + 3)
            this->speedX = -3.0f;
        else if(xe < xp - 3)
            this->speedX = 3.0f;
        else
            this->speedX = 0;
        if(ye > yp + 3)
            this->speedY = -3.0f;
        else if(ye < yp - 3)
            this->speedY = 3.0f;
        else
            this->speedY = 0;
    } else
    {
        this->speedX = 0;
        this->speedY = 0;
    }
}
