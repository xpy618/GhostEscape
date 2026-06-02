#include "actor.h"
#include "scene.h"
#include "../raw/stats.h"
#include "../affiliate/affiliate_bar.h"

void Actor::update(float dt)
{
    ObjectWorld::update(dt);
    updateHealthBar();
}

void Actor::move(float dt)
{
    setPosition(getPosition() + velocity_ * dt);
    position_ = glm::clamp(position_, glm::vec2(0.0f), Game::getInstance().getCurrentScene()->getWorldSize() );//限制移动范围
}

void Actor::takeDamage(float damage)
{
    if (stats_) {
        stats_->takeDamage(damage);
    }
}

void Actor::removeMoveControl()
{
    if( !move_control_ ) return;
    move_control_->setNeedRemove(true);
    move_control_ = nullptr;
}

void Actor::setMoveControl(MoveControl *move_control)
{
    if (move_control_){
        move_control_->setNeedRemove(true);
    }
    move_control_ = move_control;
    move_control_->setParent(this);  //有疑问
    safeAddChild(move_control_);
}

bool Actor::getIsAlive()
{
    if (!stats_) return true;
    return stats_->getIsAlive();
}

void Actor::updateHealthBar()
{
    if( !stats_ || !health_bar_ ) return;
    health_bar_->setPercentage(stats_->getHp() / stats_->getMaxHp());
}
