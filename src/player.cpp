#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_anim.h"
#include "affiliate/collider.h"
#include "raw/stats.h"
#include "raw/timer.h"
#include "affiliate/text_label.h"
#include "world/spell.h"
#include "raw/spell_thunder.h"
#include "raw/spell_fire.h"

void Player::init()
{
    Actor::init();
    flash_timer_ = Timer::addTimerChild(this, 0.2f);
    flash_timer_->start();
    max_speed_ = 500.0f;
    sprite_idle_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-idle.png", 2.0f);
    sprite_move_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-move.png", 2.0f);
    sprite_move_->setActive(false);

    collider_ = Collider::addColliderChild(this, sprite_idle_->getSize()/2.0f);
    stats_ = Stats::addStatsChild(this);
    effect_ = Effect::addEffectChild(Game::getInstance().getCurrentScene(), "assets/effect/1764.png", glm::vec2(0), 2.0f);
    effect_->setActive(false);

    weapon_= Weapon::addWeaponChild(this, 2.0f, 40.0f);
    auto thunder_creator = new SpellThunder();
    thunder_creator->init();
    weapon_->setSpellCreator(thunder_creator);
    weapon_->addChild(thunder_creator);  

    weapon2_= Weapon::addWeaponChild(this, 0.5f, 5.0f);
    auto fire_creator = new SpellFire();
    fire_creator->init();
    weapon2_->setSpellCreator(fire_creator);
    weapon2_->addChild(fire_creator);
    weapon2_->setSoundPath("assets/sound/fire-magic-6947.mp3");
    weapon2_->setTriggerButton(SDL_BUTTON_RIGHT);

    //TextLabel::addTextLabelChild(this, "老毛", "assets/font/VonwaonBitmap-16px.ttf", 16);

    setMoveControl(new MoveControl());
}

bool Player::handleEvents(SDL_Event& event)
{
    if(Actor::handleEvents(event)) return true;
    return false;
}

void Player::update(float dt)
{
   Actor::update(dt);
   if (!move_control_) autoEscape();
   checkState();
   move(dt);
   synCamera();
   checkIsDead();
}

void Player::render()
{
    if (stats_->getInvincible() && flash_timer_->getProgress() < 0.5f) return;
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
    Game::getInstance().playSound("assets/sound/hit-flesh-02-266309.mp3");
}

void Player::autoEscape()
{
    velocity_ = glm::vec2(0);
    //todo
}

void Player::synCamera()
{
    Game::getInstance().getCurrentScene()->setCameraPosition(position_ - Game::getInstance().getScreenSize() / 2.0f);
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
        effect_->setActive(true);
        effect_->setPosition(position_);
        setActive(false);
        Game::getInstance().playSound("assets/sound/female-scream-02-89290.mp3");
    }
}
