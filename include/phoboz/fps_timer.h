#ifndef _FpsTimer_H
#define _FpsTimer_H

class FpsTimer {
public:
    FpsTimer() : m_time(0) { }
    bool expired(int frame_rate);

private:
    float m_time;
};

#endif

