#include "stats.h"

Stats *Stats::addStatsChild(Actor *parent, float max_hp, float max_mana, float damage, float mana_regen)
{
    auto stats = new Stats();  
    stats->init();
    stats->setParent(parent);
    stats->setHp(max_hp);
    stats->setMaxHp(max_hp);
    stats->setMana(max_mana);
    stats->setMaxMana(max_mana);
    stats->setDamage(damage);
    stats->setManaRegen(mana_regen);
    parent->addChild(stats);
    return stats;
}

void Stats::update(float dt)
{
    Object::update(dt);
    regenMana(dt);
    if(is_invincible_){
        invincible_timer_ += dt;
        if(invincible_timer_ >= invincible_time_){
            is_invincible_ = false;
            invincible_timer_ = 0.0f;
        }
    }
}

bool Stats::canUseMana(float cost)
{
    return mana_ >= cost;
}

void Stats::useMana(float cost)
{
    mana_ -= cost;
    if (mana_ < 0) mana_ = 0;
}

void Stats::regenMana(float dt)
{
    mana_ += mana_regen_ * dt;
    if (mana_ > max_mana_) mana_ = max_mana_;
}

void Stats::takeDamage(float damage)
{
    if (is_invincible_) return;  
    hp_ -= damage;
    if (hp_ <= 0) {
        hp_ = 0;
        is_alive_ = false;
    }
    is_invincible_ = true;
    invincible_timer_ = 0.0f;
}
