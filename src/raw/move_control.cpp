#include "move_control.h"
#include "../core/actor.h"

void MoveControl::update(float dt)
{
    if (parent_ == nullptr) return;
    Object::update(dt);
    parent_->setVelocity(parent_->getVelocity() * 0.9f);
    // checkInput();
    auto direction = glm::vec2(is_right_ - is_left_, is_down_ - is_up_);  //C++中bool是整数类型
    if(glm::length(direction) > 0.1f) direction = glm::normalize(direction);  //归一化斜线速度一致
    if(glm::length(direction) > 0.1f) parent_->setVelocity(direction * max_speed_);  //动的时候才设置速度
}

bool MoveControl::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if (event.key.scancode == SDL_SCANCODE_W || event.key.scancode == SDL_SCANCODE_UP) is_up_ = true;
        if (event.key.scancode == SDL_SCANCODE_S || event.key.scancode == SDL_SCANCODE_DOWN) is_down_ = true;
        if (event.key.scancode == SDL_SCANCODE_A || event.key.scancode == SDL_SCANCODE_LEFT) is_left_ = true;
        if (event.key.scancode == SDL_SCANCODE_D || event.key.scancode == SDL_SCANCODE_RIGHT) is_right_ = true;
        return true;
    }
    if (event.type == SDL_EVENT_KEY_UP)
    {
        if (event.key.scancode == SDL_SCANCODE_W || event.key.scancode == SDL_SCANCODE_UP) is_up_ = false;
        if (event.key.scancode == SDL_SCANCODE_S || event.key.scancode == SDL_SCANCODE_DOWN) is_down_ = false;
        if (event.key.scancode == SDL_SCANCODE_A || event.key.scancode == SDL_SCANCODE_LEFT) is_left_ = false;
        if (event.key.scancode == SDL_SCANCODE_D || event.key.scancode == SDL_SCANCODE_RIGHT) is_right_ = false;
        return true;
    }
    Object::handleEvents(event);
    return false;
}

// void MoveControl::checkInput()
// {
//     auto keyboard = SDL_GetKeyboardState(NULL);
//     is_up_ = keyboard[SDL_SCANCODE_W] || keyboard[SDL_SCANCODE_UP];
//     is_down_ = keyboard[SDL_SCANCODE_S] || keyboard[SDL_SCANCODE_DOWN];
//     is_left_ = keyboard[SDL_SCANCODE_A] || keyboard[SDL_SCANCODE_LEFT];
//     is_right_ = keyboard[SDL_SCANCODE_D] || keyboard[SDL_SCANCODE_RIGHT];
// }
