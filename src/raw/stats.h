#ifndef STATS_H
#define STATS_H

#include "../core/actor.h"

class Stats : public Object
{
protected:
    Actor* parent_ = nullptr;
    float hp_ = 100.0f;
    float max_hp_ =100.0f;
    float mana_ = 100.0f;
    float max_mana_ = 100.0f;
    float damage_ = 40.0f;
    float mana_regen_ = 10.0f; 

    float invincible_time_ = 1.5f;
    float invincible_timer_ = 0.0f;
    bool is_alive_ = true;  
    bool is_invincible_ = false; 

public:
    static Stats* addStatsChild(Actor* parent, float max_hp = 100.0f, float max_mana = 100.0f, float damage = 40.0f, float mana_regen = 10.0f);
    virtual void update(float dt) override;
    bool canUseMana(float cost);
    void useMana(float cost);
    void regenMana(float dt);
    void takeDamage(float damage);

    // getters and setters
    Actor* getParent() const { return parent_; }
    float getHp() const { return hp_; }
    float getMaxHp() const { return max_hp_; }
    float getMana() const { return mana_; }
    float getMaxMana() const { return max_mana_; }
    float getDamage() const { return damage_; }
    float getManaRegen() const { return mana_regen_; }
    bool getInvincible() const { return is_invincible_; }
    bool getIsAlive() const { return is_alive_; }
    void setParent(Actor* parent) { parent_ = parent; }
    void setHp(float hp) { hp_ = hp; }
    void setMaxHp(float max_hp) { max_hp_ = max_hp; }
    void setMana(float mana) { mana_ = mana; }
    void setMaxMana(float max_mana) { max_mana_ = max_mana; }
    void setDamage(float damage) { damage_ = damage; }
    void setManaRegen(float mana_regen) { mana_regen_ = mana_regen; }
    void setAlive(bool is_alive) { is_alive_ = is_alive; }
    void setInvincible(bool is_invincible) { is_invincible_ = is_invincible; }
};



#endif // STATS_H