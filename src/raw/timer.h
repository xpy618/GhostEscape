#ifndef TIMER_H
#define TIMER_H

#include "../core/object.h"

class Timer : public Object  //创建时默认非active
{
protected:
    float timer_ = 0.0f;
    float interval_ = 3.0f;
    bool timer_out_ = false;

public:
    static Timer* addTimerChild(Object* parent, float interval = 3.0f);

    virtual void update(float dt) override;

    void start() { is_active_ = true; }
    void stop() { is_active_ = false; }
    bool timerOut ();
    float getProgress() { return timer_ / interval_; }  //返回0-1之间的值
    //getters and setters
    float getTimer() { return timer_; }
    float getInterval() { return interval_; }
    void setTimer(float timer) { timer_ = timer; }
    void setInterval(float interval) { interval_ = interval; }
};






#endif // TIMER_H