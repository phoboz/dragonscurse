#ifndef _Timer_H
#define _Timer_H

class Timer {
public:
    Timer() : m_time(0) { }
    bool lock_fps(int frame_rate);

private:
    float m_time;
};

#endif

