#include "button_hover.h"
#include "button_press.h"
#include "button_normal.h"

void ButtonHover::onEnter()
{
    Game::getInstance().playSound("assets/sound/UI_button12.wav"); 
    parent_->getSpriteHover()->setActive(true);
}

void ButtonHover::onExit()
{
    parent_->getSpriteHover()->setActive(false);
}

bool ButtonHover::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_MOTION){
        auto pos = parent_->getRenderPosition() + parent_->getSpriteHover()->getOffset();
        auto size = parent_->getSpriteHover()->getSize();
        if (!Game::getInstance().isMouseInRect(pos, pos + size)){
            parent_->changeState(new ButtonNormal());
            return true;
        }
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)  //不能套在上面，因为鼠标按下时不可能移动
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            parent_->changeState(new ButtonPress());
            return true;
        }
    }
    return false;
}
