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
    this->textureIncrement = 0;

    switch(this->type)
    {
        case ENEMY_TYPE_VOODOO:
            this->seeRadius = 250;
            this->textureIncrement = 1;
            break;
        case ENEMY_TYPE_BOZA:
            this->seeRadius = 250;
            break;
    }

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
        this->angle = PLAYER_ANGLE_LEFT;
    this->coords.x += this->speedX;
    this->coords.y += this->speedY;
}

void Enemy::loadTexture()
{
    int i;

    switch(type)
    {
        case ENEMY_TYPE_VOODOO:
            Player::loadTexture(PLAYER_ANGLE_DOWN, 0, "data/indi/indi_red1.png");
            Player::loadTexture(PLAYER_ANGLE_DOWN, 1, "data/indi/indi_red2.png");
            Player::loadTexture(PLAYER_ANGLE_DOWN, 2, "data/indi/indi_red3.png");
            for(i = 0; i < 3; i++)
            {
                this->texture.up[i] = texture.down[i];
                this->texture.left[i] = texture.down[i];
                this->texture.right[i] = texture.down[i];
            }
            break;
        case ENEMY_TYPE_BOZA:
            Player::loadTexture("boza/boza");
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

    if(pow(player->getX() - xe, 2) +
            pow(player->getY() - ye, 2) < pow(this->seeRadius, 2) ||
            pow(player->getX() + player->getWidth() - xe, 2) +
            pow(player->getY() + player->getHeight() - ye, 2) < pow(this->seeRadius, 2))
    {
        if(xe > xp + 3)
            this->speedX = -2.0f;
        else if(xe < xp - 3)
            this->speedX = 2.0f;
        else
            this->speedX = 0;
        if(ye > yp + 3)
            this->speedY = -2.0f;
        else if(ye < yp - 3)
            this->speedY = 2.0f;
        else this->speedY = 0;
        if(this->textureIncrement == 0)
            this->textureIncrement = 1;
    } else
    {
        this->speedX = 0;
        this->speedY = 0;
        if(this->type == ENEMY_TYPE_BOZA)
        {
            this->textureIncrement = 0;
            this->textureState = 1;
        }
    }
}
