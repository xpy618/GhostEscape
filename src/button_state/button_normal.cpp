#include "button_normal.h"
#include "button_hover.h"

void ButtonNormal::onEnter()
{
    parent_->getSpriteNormal()->setActive(true);
}

void ButtonNormal::onExit()
{
    parent_->getSpriteNormal()->setActive(false);
}

bool ButtonNormal::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_MOTION){
        auto pos = parent_->getRenderPosition() + parent_->getSpriteNormal()->getOffset();
        auto size = parent_->getSpriteNormal()->getSize();
        if (Game::getInstance().isMouseInRect(pos, pos + size))
        {
            parent_->changeState(new ButtonHover());
            return true;
        }
    }
    return false;
}
