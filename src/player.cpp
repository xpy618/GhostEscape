#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_anim.h"
#include "affiliate/collider.h"
#include "raw/stats.h"
#include "affiliate/text_label.h"

void Player::init()
{
    Actor::init();
    max_speed_ = 500.0f;
    sprite_idle_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-idle.png", 2.0f);
    sprite_move_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-move.png", 2.0f);
    sprite_move_->setActive(false);

    collider_ = Collider::addColliderChild(this, sprite_idle_->getSize()/2.0f);
    stats_ = Stats::addStatsChild(this);
    effect_ = Effect::addEffectChild(nullptr, "assets/effect/1764.png", glm::vec2(0), 2.0f);
    weapon_thunder_ = WeaponThunder::addWeaponThunderChild(this, 2.0f, 40.0f);
    //TextLabel::addTextLabelChild(this, "老毛", "assets/font/VonwaonBitmap-16px.ttf", 16);
}

void Player::handleEvents(SDL_Event& event)
{
    Actor::handleEvents(event);
}

void Player::update(float dt)
{
   Actor::update(dt);
   keyboardControl(); 
   checkState();
   move(dt);
   synCamera();
   checkIsDead();
}

void Player::render()
{
    Actor::render();
}

void Player::clean()
{
    Actor::clean();
}

void Player::takeDamage(float damage)
{
    if(!stats_ || stats_->getInvincible()) return;
    Actor::takeDamage(damage);
    game.playSound("assets/sound/hit-flesh-02-266309.mp3");
}

void Player::keyboardControl()
{
    auto currentKeyStates = SDL_GetKeyboardState(NULL);

    velocity_ *= 0.9f; //惯性减速

    if (currentKeyStates[SDL_SCANCODE_W])
    {
        velocity_.y = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_S])
    {
        velocity_.y = max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_A])
    {
        velocity_.x = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_D])
    {
        velocity_.x = max_speed_;
    }

}

void Player::synCamera()
{
    game.getCurrentScene()->setCameraPosition(position_ - game.getScreenSize() / 2.0f);
}

void Player::checkState()
{
    if (velocity_.x < 0){
        sprite_move_->setFlip(true);
        sprite_idle_->setFlip(true);
    }else{
        sprite_move_->setFlip(false);
        sprite_idle_->setFlip(false);
    }
    bool new_is_moving = (glm::length(velocity_) > 0.1f);
    if (new_is_moving != is_moving_){
        is_moving_ = new_is_moving;
        changeState(is_moving_);
    }
}

void Player::changeState(bool is_moving)
{
    if (is_moving){
        sprite_idle_->setActive(false);
        sprite_move_->setActive(true);
        sprite_move_->setCurrentFrame(sprite_idle_->getCurrentFrame());
        sprite_move_->setFrameTime(sprite_idle_->getFrameTime());
    }else{
        sprite_idle_->setActive(true);
        sprite_move_->setActive(false);
        sprite_idle_->setCurrentFrame(sprite_move_->getCurrentFrame());
        sprite_idle_->setFrameTime(sprite_move_->getFrameTime());
    }
}

void Player::checkIsDead()
{
    if (!stats_->getIsAlive()){
        game.getCurrentScene()->safeAddChild(effect_);
        effect_->setPosition(position_);
        setActive(false);
        game.playSound("assets/sound/female-scream-02-89290.mp3");
    }
}
