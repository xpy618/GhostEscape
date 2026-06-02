#ifndef PLAYER_H
#define PLAYER_H

#include "core/actor.h"
#include "affiliate/sprite_anim.h"
#include "world/effect.h"
#include "weapon_thunder.h"
#include "raw/move_control.h"

class Timer;
class Player : public Actor
{
    WeaponThunder* weapon_thunder_ = nullptr;
    MoveControl* move_control_ = nullptr;
    SpriteAnim* sprite_idle_ = nullptr;
    SpriteAnim* sprite_move_ = nullptr;
    Effect* effect_ = nullptr;  //player要保存成员变量是因为，特效在player死亡后调用，enemy是在创建之前
    Timer* flash_timer_ = nullptr;
    bool is_moving_ = false;
public:
    virtual void init () override;
    virtual bool handleEvents (SDL_Event& event) override;
    virtual void update (float dt) override;
    virtual void render () override;
    virtual void clean () override;

    virtual void takeDamage (float damage) override;

    void moveControl ();
    void setMoveControl(MoveControl* move_control);

    void synCamera();
    void checkState();
    void changeState(bool is_moving);
    void checkIsDead();
};




#endif // PLAYER_H