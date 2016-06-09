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

Player::Player(float x, float y, Timer *timer, float w, float h, int interval)
{
    this->coords.x = x;
    this->coords.y = y;
    this->coords.w = w;
    this->coords.h = h;
    this->speedX = 0;
    this->speedY = 0;
    this->health = 3;
    this->angle = PLAYER_ANGLE_DOWN;
    this->textureState = 1;
    this->textureIncrement = 0;

    if(timer != NULL)
        timer->add(interval, new PlayerAnimator(this));  //Speed of sprites replacing each other.
}

Player::~Player(void)
{
}

void Player::move(void)
{
    if(this->speedX > 0)
    {
        this->angle = PLAYER_ANGLE_RIGHT;
        if(this->textureIncrement == 0)
            this->textureIncrement = 1;
    } else if(this->speedX < 0)
    {
        this->angle = PLAYER_ANGLE_LEFT;
        if(this->textureIncrement == 0)
            this->textureIncrement = 1;
    } else if(this->speedY > 0)
    {
        this->angle = PLAYER_ANGLE_UP;
        if(this->textureIncrement == 0)
            this->textureIncrement = 1;
    } else if(this->speedY < 0)
    {
        this->angle = PLAYER_ANGLE_DOWN;
        if(this->textureIncrement == 0)
            this->textureIncrement = 1;
    } else
    {
        this->angle = PLAYER_ANGLE_DOWN;
        this->textureIncrement = 0;
        this->textureState = 1;
    }
    this->coords.x += this->speedX;
    this->coords.y += this->speedY;
}

void Player::changeMoveState(int type, int state)
{
    switch(type)
    {
        case PLAYER_MOVE_ADD:
            switch(state)
            {
                case PLAYER_MOVE_DOWN:
                    this->speedY -= PLAYER_SPEED;
                    break;
                case PLAYER_MOVE_RIGHT:
                    this->speedX += PLAYER_SPEED;
                    break;
                case PLAYER_MOVE_UP:
                    this->speedY += PLAYER_SPEED;
                    break;
                case PLAYER_MOVE_LEFT:
                    this->speedX -= PLAYER_SPEED;
                    break;
            }
            break;
        case PLAYER_MOVE_DELETE:
            switch(state)
            {
                case PLAYER_MOVE_DOWN:
                    this->speedY += PLAYER_SPEED;
                    break;
                case PLAYER_MOVE_RIGHT:
                    this->speedX -= PLAYER_SPEED;
                    break;
                case PLAYER_MOVE_UP:
                    this->speedY -= PLAYER_SPEED;
                    break;
                case PLAYER_MOVE_LEFT:
                    this->speedX += PLAYER_SPEED;
                    break;
            }
            break;
    }
}

void Player::loadTexture(std::string file)
{
    SDL_Rect imgForCrop = { 0, 0, 32, 32 };
    int i;

    for(i = 0; i < 5; i++)
    {
        this->bodyTexture[PLAYER_ANGLE_DOWN].push_back(
                loadModel("data/" + file + "/" + file + "_body/" + file + "_d.png", imgForCrop));
        this->bodyTexture[PLAYER_ANGLE_RIGHT].push_back(
                loadModel("data/" + file + "/" + file + "_body/" + file + "_r.png", imgForCrop));
        this->bodyTexture[PLAYER_ANGLE_UP].push_back(
                loadModel("data/" + file + "/" + file + "_body/" + file + "_u.png", imgForCrop));
        this->bodyTexture[PLAYER_ANGLE_LEFT].push_back(
                loadModel("data/" + file + "/" + file + "_body/" + file + "_r.png", imgForCrop));
        imgForCrop.x += imgForCrop.h;
    }
    // Precica za ucitavanje glava svinje
    // (zahvaljujuci aci, dobro je stavio raspored na spritesheet)
    imgForCrop = { 0, 0, 32, 32 };
    for(i = 0; i < 4; i++)
    {
        this->headTexture[i].push_back(
                loadModel("data/" + file + "/" + file + "_head/" + file + "_h.png", imgForCrop));
        imgForCrop.x += imgForCrop.w;
    }
    this->shadowTexture = loadModel("data/shadow.png");

    std::cout << "Player texture initialized" << std::endl;
}

SDL_Rect Player::getCollCoords(void)
{
    SDL_Rect collCoords = this->coords;
    collCoords.h -= 45;
    return collCoords;
}

void Player::changeTexture(void)
{
    this->textureState += this->textureIncrement;
    if(this->textureState <= 0 || this->textureState >= bodyTexture[0].size() - 1)
        this->textureIncrement = -this->textureIncrement;
}

void Player::collision(float width, float height)
{
    if(this->coords.x < 0)
        this->coords.x = 0;
    else if(this->coords.x + this->coords.w > width)
        this->coords.x = width - this->coords.x + this->coords.w;
    if(this->coords.y < 0)
        this->coords.y = 0;
    else if(this->coords.y + this->coords.h > height)
        this->coords.y = height - this->coords.y + this->coords.h;
}

void Player::collision(Player *player)
{
    SDL_Rect tmpCoords = this->coords;
    tmpCoords.x += 8;
    tmpCoords.y += 8;
    tmpCoords.w -= 8 * 2;
    tmpCoords.h -= 8 * 2;

    if(player->getX() + player->getWidth() > this->coords.x &&
       player->getX() < this->coords.x + this->coords.w &&
       player->getY() + player->getHeight() > this->coords.y &&
       player->getY() < this->coords.y + this->coords.h)
    {
        if(player->getX() + player->getWidth() <= tmpCoords.x)
            this->coords.x = player->getX() + player->getWidth();
        else if(player->getX() >= tmpCoords.x + tmpCoords.w)
            this->coords.x = player->getX() - this->coords.w;
        if(player->getY() + player->getHeight() <= tmpCoords.y)
            this->coords.y = player->getY() + player->getHeight();
        else if(player->getY() >= tmpCoords.y + tmpCoords.h)
            this->coords.y = player->getY() - this->coords.h;
        this->health--;
    }
}

// Render player
void Player::render(SDL_Rect camera)
{
    glColor4ub(255, 255, 255, 255); // White color
    glEnable(GL_TEXTURE_2D);

    float x = this->coords.x - camera.x;
    float y = this->coords.y - camera.y;
    float w = this->coords.w;
    float h = this->coords.h;

    glBindTexture(GL_TEXTURE_2D, this->bodyTexture[this->angle][this->textureState]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(x, y);
        glTexCoord2d(1, 1); glVertex2f(x + w, y);
        glTexCoord2d(1, 0); glVertex2f(x + w, y + h);
        glTexCoord2d(0, 0); glVertex2f(x, y + h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);

    w = this->coords.w + 10;
    h = this->coords.h + 10;
    x = this->coords.x - camera.x + this->coords.w / 2 - w / 2;
    y = this->coords.y - camera.y + this->coords.h / 2 - h / 2;

    glBindTexture(GL_TEXTURE_2D, this->headTexture[this->angle][0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(x, y);
        glTexCoord2d(1, 1); glVertex2f(x + w, y);
        glTexCoord2d(1, 0); glVertex2f(x + w, y + h);
        glTexCoord2d(0, 0); glVertex2f(x, y + h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Player::renderShadow(SDL_Rect camera)
{
    glColor4ub(255, 255, 255, 255); // White color
    glEnable(GL_TEXTURE_2D);

    float x = this->coords.x - camera.x;
    float y = this->coords.y - camera.y;
    float w = this->coords.w;
    float h = this->coords.h;

    y -= 35;
    h -= 60;

    glBindTexture(GL_TEXTURE_2D, this->shadowTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(x, y);
        glTexCoord2d(1, 1); glVertex2f(x + w, y);
        glTexCoord2d(1, 0); glVertex2f(x + w, y + h);
        glTexCoord2d(0, 0); glVertex2f(x, y + h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
