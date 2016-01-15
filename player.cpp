#include "main.h"
#include "functions.h"
#include "timer.h"
#include "player.h"

class PlayerAnimator : public Ticker
{
    private:
        Player *player;

    public:
        PlayerAnimator(Player *player)
        {
            this->player = player;
        }

        virtual void tick(void)
        {
            this->player->changeTexture();
        }
};

Player::Player(float x, float y, Timer *timer)
{
    this->coords.x = x;
    this->coords.y = y;
    this->coords.w = 54.0;
    this->coords.h = 70.0;
    this->speed = 5.0;
    this->helth = 3.0;
    this->moveState.down = false;
    this->moveState.right = false;
    this->moveState.up = false;
    this->moveState.left = false;
    this->angle = PLAYER_ANGLE_DOWN;
    this->textureState = 1;
    this->textureIncrement = 0;

    timer->add(90, new PlayerAnimator(this));
}

Player::~Player(void)
{
}

void Player::move(void)
{
    if(!this->moveState.down &&
            !this->moveState.up &&
            !this->moveState.left &&
            !this->moveState.right)
    {
        this->textureState = 1;
        this->textureIncrement = 0;
    } else
    {
        if(this->textureIncrement == 0)
            this->textureIncrement = 1;
        if(this->moveState.down)
        {
            this->coords.y -= this->speed;
            this->angle = PLAYER_ANGLE_DOWN;
        }
        if(this->moveState.up)
        {
            this->coords.y += this->speed;
            this->angle = PLAYER_ANGLE_UP;
        }
        if(this->moveState.left)
        {
            this->coords.x -= this->speed;
            this->angle = PLAYER_ANGLE_LEFT;
        }
        if(this->moveState.right)
        {
            this->coords.x += this->speed;
            this->angle = PLAYER_ANGLE_RIGHT;
        }
    }
}

void Player::changeMoveState(int type, int state)
{
    switch(type)
    {
        case PLAYER_MOVE_ADD:
            switch(state)
            {
                case PLAYER_MOVE_DOWN:
                    this->moveState.down = true;
                    break;
                case PLAYER_MOVE_RIGHT:
                    this->moveState.right = true;
                    break;
                case PLAYER_MOVE_UP:
                    this->moveState.up = true;
                    break;
                case PLAYER_MOVE_LEFT:
                    this->moveState.left = true;
                    break;
            }
            break;
        case PLAYER_MOVE_DELETE:
            switch(state)
            {
                case PLAYER_MOVE_DOWN:
                    this->moveState.down = false;
                    break;
                case PLAYER_MOVE_RIGHT:
                    this->moveState.right = false;
                    break;
                case PLAYER_MOVE_UP:
                    this->moveState.up = false;
                    break;
                case PLAYER_MOVE_LEFT:
                    this->moveState.left = false;
                    break;
            }
            break;
    }
}

void Player::loadTexture(std::string file)
{
    this->texture.down[0] = loadModel("data/" + file + "_d2.png");
    this->texture.right[0] = loadModel("data/" + file + "_r2.png");
    this->texture.left[0] = loadModel("data/" + file + "_l2.png");
    this->texture.up[0] = loadModel("data/" + file + "_u2.png");
    this->texture.down[1] = loadModel("data/" + file + "_d.png");
    this->texture.right[1] = loadModel("data/" + file + "_r.png");
    this->texture.left[1] = loadModel("data/" + file + "_l.png");
    this->texture.up[1] = loadModel("data/" + file + "_u.png");
    this->texture.down[2] = loadModel("data/" + file + "_d3.png");
    this->texture.right[2] = loadModel("data/" + file + "_r3.png");
    this->texture.left[2] = loadModel("data/" + file + "_l3.png");
    this->texture.up[2] = loadModel("data/" + file + "_u3.png");
}

void Player::changeTexture(void)
{
    this->textureState += this->textureIncrement;
    if(this->textureState != 1)
        this->textureIncrement = -this->textureIncrement;
}

// Render player
void Player::render(void)
{
    glColor4ub(255, 255, 255, 255); // White color
    glEnable(GL_TEXTURE_2D);

    switch(this->angle)
    {
        case PLAYER_ANGLE_DOWN:
            glBindTexture(GL_TEXTURE_2D, this->texture.down[this->textureState]);
            break;
        case PLAYER_ANGLE_RIGHT:
            glBindTexture(GL_TEXTURE_2D, this->texture.right[this->textureState]);
            break;
        case PLAYER_ANGLE_UP:
            glBindTexture(GL_TEXTURE_2D, this->texture.up[this->textureState]);
            break;
        case PLAYER_ANGLE_LEFT:
            glBindTexture(GL_TEXTURE_2D, this->texture.left[this->textureState]);
            break;
    }

    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(this->coords.x, this->coords.y);
        glTexCoord2d(1, 1); glVertex2f(this->coords.x + this->coords.w, this->coords.y);
        glTexCoord2d(1, 0); glVertex2f(this->coords.x + this->coords.w, this->coords.y + this->coords.h);
        glTexCoord2d(0, 0); glVertex2f(this->coords.x, this->coords.y + this->coords.h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Player::collision(float width, float height)
{
    if(this->coords.x < 0)
        this->coords.x = 0;
    else if(this->coords.x + this->coords.w > width)
        this->coords.x = width - this->coords.w;
    if(this->coords.y < 0)
        this->coords.y = 0;
    else if(this->coords.y + this->coords.h > height)
        this->coords.y = height - this->coords.h;
}

/*
void Player::collision(Tile *tile)
{
    if(this->coords.x + this->coords.w > tile->getX() &&
            this->coords.x < tile->getX() + tile->getWidth())
        if(this->coords.y + this->coords.h > tile->getY() &&
                this->coords.y < tile->getY() + tile->getHeight())
        {
            / *
            if(this->moveState.down)
                this->y = tile->getY() + tile->getHeight();
            else if(this->moveState.right)
                this->x = tile->getX() - this->width;
            else if(this->moveState.up)
                this->y = tile->getY() - this->height;
            else if(this->moveState.left)
                this->x = tile->getX() + tile->getWidth();
            * /
            switch(this->angle)
            {
                case PLAYER_ANGLE_DOWN:
                    this->coords.y = tile->getY() + tile->getHeight();
                    break;
                case PLAYER_ANGLE_RIGHT:
                    this->coords.x = tile->getX() - this->coords.w;
                    break;
                case PLAYER_ANGLE_UP:
                    this->coords.y = tile->getY() - this->coords.h;
                    break;
                case PLAYER_ANGLE_LEFT:
                    this->coords.x = tile->getX() + tile->getWidth();
                    break;
            }
        }
}
*/
