#include "main.h"
#include "functions.h"
#include "timer.h"

Timer::Timer(void)
{
    this->before = 0;
}

Timer::~Timer(void)
{
    int i;

    for(i = 0; i < ticker.size(); i++)
        delete ticker[i];
}

void Timer::add(int interval, Ticker *ticker)
{
    this->ticker.push_back(ticker);
    this->interval.push_back(interval);
    this->now.push_back(0);
}

void Timer::tick(void)
{
    unsigned int ticks;
    int now;
    int i;

    ticks = SDL_GetTicks();
    now = ticks - this->before;
    this->before = ticks;

    for(i = 0; i < ticker.size(); i++)
    {
        this->now[i] += now;
        if(this->now[i] >= this->interval[i])
        {
            ticker[i]->tick();
            this->now[i] = 0;
        }
    }
}
