#ifndef _Timer_H
#define _Timer_H

class Timer {
public:
    Timer() : m_counter(0), m_enabled(true) { }
    void set(int value) { m_counter = value; }
    void reset() { m_counter = 0; }
    void enable(bool enable) { m_enabled = enable; }
    bool check(int treshold);
    bool expired(int treshold);

private:
    bool m_enabled;
    int m_counter;
};

#endif

