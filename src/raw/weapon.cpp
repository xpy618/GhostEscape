#include "weapon.h"
#include "../core/actor.h"
#include "../world/spell.h"
#include "../core/scene.h"
#include "stats.h"


void Weapon::update(float dt)
{
    Object::update(dt);
    cool_down_timer_ += dt;
}

void Weapon::attack(glm::vec2 position, Spell* spell)
{
    
    parent_->getStats()->useMana(mana_cost_);
    cool_down_timer_ = 0.0f;
    spell->setPosition(position);
    Game::getInstance().getCurrentScene()->safeAddChild(spell); //因为是游戏运行时添加的，所以必须使用safeaddchild
    
}

bool Weapon::canAttack()
{
    if (cool_down_timer_ < cool_down_) return false;
    if (!parent_->getStats()->canUseMana(mana_cost_)) return false;
    return true;
}
