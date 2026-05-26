#ifndef WEAPON_H
#define WEAPON_H

#include "../core/object.h"
#include "../world/spell.h"

class Spell;
class Actor;
class Weapon : public Object
{
protected:
    Actor* parent_ = nullptr;
    float cool_down_ = 1.0f;
    float mana_cost_ = 0.0f;
    float cool_down_timer_ = 0.0f;

public:
    virtual void update(float dt) override;

    void attack(glm::vec2 position, Spell* spell);  //保证调用时一定执行
    bool canAttack() ;
    //getters and setters
    float getCoolDown() const { return cool_down_; };
    void setCoolDown(float cool_down) { cool_down_ = cool_down; };
    float getManaCost() const { return mana_cost_; };
    void setManaCost(float mana_cost) { mana_cost_ = mana_cost; };
    Actor* getParent() const { return parent_; };
    void setParent(Actor* parent) { parent_ = parent; };



};



#endif // WEAPON_H