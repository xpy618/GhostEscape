#ifndef MOVE_CONTROL_H
#define MOVE_CONTROL_H

#include "../core/object.h"

class Actor;
class MoveControl : public Object 
{
protected:
    bool is_up_ = false;
    bool is_down_ = false;
    bool is_left_ = false;
    bool is_right_ = false;
    Actor* parent_ = nullptr;
    float max_speed_ = 500.0f;

public:
    virtual void update(float dt) override;
    // void checkInput();
    virtual bool handleEvents(SDL_Event& event) override ;
    //gettses and setters
    bool getUp() const { return is_up_; }
    bool getDown() const { return is_down_; }
    bool getLeft() const { return is_left_; }
    bool getRight() const { return is_right_; }

    void setParent(Actor* parent) { parent_ = parent; }
    Actor* getParent() const { return parent_; }
    void setMaxSpeed(float speed) { max_speed_ = speed; }
    float getMaxSpeed() const { return max_speed_; }

};






#endif // MOVE_CONTROL_H