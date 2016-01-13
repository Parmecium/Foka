#ifndef TIMER_H
#define TIMER_H

class Tick
{
    public:
        public virtual void tick(void);
}

class Timer
{
    private:
        std::vector<Ticker> tickers;
        std::vector<int> intervals;
        long before;
        int now;

        void tick(void);

    public:
        Timer(void);
        ~Timer(void);
        void add(int interval, Ticker ticker);
};

#endif  // TIMER_H
