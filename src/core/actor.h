#ifndef ACTOR_H
#define ACTOR_H

#include "object_world.h"
#include <glm/glm.hpp>

class Stats;
class AffiliateBar;
class Actor : public ObjectWorld 
{
protected:
    Stats* stats_ = nullptr;
    AffiliateBar* health_bar_ = nullptr;
    glm::vec2 velocity_ = glm::vec2(0, 0);
    float max_speed_ = 100.0f;

public:
    virtual void update(float dt) override;
    void move(float dt);
    virtual void takeDamage(float damage) override;
    
    //getters and setters
    glm::vec2 getVelocity() const { return velocity_; }
    void setVelocity(const glm::vec2& velocity) { velocity_ = velocity; }
    float getMaxSpeed() const { return max_speed_; }
    void setMaxSpeed(float max_speed) { max_speed_ = max_speed; }
    Stats* getStats() const { return stats_; }
    void setStats(Stats* stats) { stats_ = stats; }
    AffiliateBar* getHealthBar() const { return health_bar_; }
    void setHealthBar(AffiliateBar* health_bar) { health_bar_ = health_bar; }

    bool getIsAlive();

private:
    void updateHealthBar();

    
};



#endif // ACTOR_H