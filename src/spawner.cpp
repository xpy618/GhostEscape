#include "spawner.h"
#include "enemy.h"
#include "world/effect.h"
#include "core/scene.h"

void Spawner::update(float dt)
{
    if (!target_ || !target_->getActive()) return;
    timer_ += dt;
    if (timer_ > interval_)
    {
        timer_ = 0;
        for (int i = 0; i < num_; ++i)
        {
            auto pos = game.randomVec2(game.getCurrentScene()->getCameraPosition(), game.getCurrentScene()->getCameraPosition() + game.getScreenSize());
            Enemy* enemy = Enemy::addEnemyChild(nullptr, pos, target_);  //不在这里创enemy，在下面创
            Effect::addEffectChild(game.getCurrentScene(), "assets/effect/184_3.png", pos, 1.0f, enemy);
        }
    }
}
