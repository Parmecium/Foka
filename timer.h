#ifndef TIMER_H
#define TIMER_H

class Ticker
{
    public:
        virtual void tick(void) {}
};

class Timer
{
    private:
        std::vector<Ticker *> ticker;
        std::vector<int> interval;
        std::vector<int> now;
        unsigned int before;

    public:
        Timer(void);
        ~Timer(void);
        void tick(void);
        void add(int interval, Ticker *ticker);
};

#endif  // TIMER_H
