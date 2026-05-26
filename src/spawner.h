#ifndef SPAWNER_H
#define SPAWNER_H

#include "core/object.h"

class Player;
class Spawner : public Object
{
protected:
    int num_ = 20;
    float timer_ = 0;
    float interval_ = 3.0f; 
    Player* target_ = nullptr;

public:
    virtual void update(float dt) override;
    //getters and setters
    int getNum() const { return num_; }
    void setNum(int num) { num_ = num; }
    float getTimer() const { return timer_; }
    void setTimer(float timer) { timer_ = timer; }
    float getInterval() const { return interval_; }
    void setInterval(float interval) { interval_ = interval; }
    void setTarget(Player* target) { target_ = target; }

};



#endif // SPAWNER_H