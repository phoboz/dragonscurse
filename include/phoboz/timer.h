#ifndef _Timer_H
#define _Timer_H

class Timer {
public:
    Timer() : m_counter(0) { }
    void reset() { m_counter = 0; }
    bool check(int treshold);
    bool expired(int treshold);

private:
    int m_counter;
};

#endif

