#ifndef MOVE_CONTROL_H
#define MOVE_CONTROL_H

#include "../core/object.h"

class MoveControl : public Object 
{
protected:
    bool is_up_ = false;
    bool is_down_ = false;
    bool is_left_ = false;
    bool is_right_ = false;

public:
    //gettses
    bool getUp() const { return is_up_; }
    bool getDown() const { return is_down_; }
    bool getLeft() const { return is_left_; }
    bool getRight() const { return is_right_; }

};






#endif // MOVE_CONTROL_H