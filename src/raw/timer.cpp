#include "timer.h"

Timer *Timer::addTimerChild(Object *parent, float interval)
{
    auto timer = new Timer();
    timer->init();
    timer->setInterval(interval);
    if(parent)parent->addChild(timer);
    timer->setActive(false);
    return timer;
}

void Timer::update(float dt)
{
    timer_ += dt;
    if (timer_ >= interval_){
        timer_ = 0;
        timer_out_ = true;
    }  
}

bool Timer::timerOut()  //并不会中断循环，只是在一个循环结束后发出信号
{
    if (timer_out_){
        timer_out_ = false;
        return true;
    }
    return false;
}
