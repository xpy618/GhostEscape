#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "affiliate/sprite_anim.h"

class Enemy : public Actor
{
    enum class State{
        NORMAL,
        HURT,
        DIE
    };

    State current_state_ = State::NORMAL;
    Player* target_ = nullptr;
    SpriteAnim* anim_normal_ = nullptr;
    SpriteAnim* anim_hurt_ = nullptr;
    SpriteAnim* anim_die_ = nullptr;

    SpriteAnim* current_anim_ = nullptr;

    int score_ = 10;


public:
    static Enemy* addEnemyChild(ObjectScreen* parent, glm::vec2 pos, Player* target);
    virtual void init() override;
    virtual void update(float dt) override;
    void aimTarget(Player* target);

    void checkState();
    void changeState(State new_state);
    void attack();
    void remove();

    //getters and setters
    Player* getTarget() const { return target_; }
    void setTarget(Player* target) { target_ = target; } //告诉要追谁
};



#endif // ENEMY_H