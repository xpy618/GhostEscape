#include "button_press.h"
#include "button_normal.h"

void ButtonPress::onEnter()
{
    Game::getInstance().playSound("assets/sound/UI_button08.wav");
    parent_->getSpritePress()->setActive(true);
}

void ButtonPress::onExit()
{
    parent_->getSpritePress()->setActive(false);
}

bool ButtonPress::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        if (event.button.button == SDL_BUTTON_LEFT){
        auto pos = parent_->getRenderPosition() + parent_->getSpritePress()->getOffset();
        auto size = parent_->getSpritePress()->getSize();
        if (Game::getInstance().isMouseInRect(pos, pos + size)){
            parent_->setIsTrigger(true);
        }
        parent_->changeState(new ButtonNormal());
        return true;
        }
    }
    return false;
}
