#include "main.h"
#include "functions.h"
#include "timer.h"

Timer::Timer(void)
{
    this->before = SDL_GetTicks();
}

Timer::~Timer(void)
{
}

void Timer::add(int interval, Ticker *ticker)
{
    this->ticker.push_back(ticker);
    this->interval.push_back(interval);
}

void Timer::tick(void)
{
    int ticks;
    int now;
    int i;

    ticks = SDL_GetTicks();
    now = ticks - this->before;
    this->before = ticks;

    for(i = 0; i < ticker.size(); i++)
    {
        this->now[i] += now;
        if(this->now[i] > this->interval[i])
        {
            ticker[i]->tick();
            this->now[i] = 0;
        }
    }
}
