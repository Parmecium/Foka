#include "main.h"
#include "functions.h"
#include "tick.h"
#include "timer.h"

Timer::Timer(void)
{
    this->before = SDL_GetTicks();
    this->now = 0;
}

Timer::~Timer(void)
{
}

void Timer::add(int interval, Ticker ticker)
{
    this->tickers.push_back(ticker);
    this->intervals.push_back(interval);
}

void Timer::tick(void)
{
}
