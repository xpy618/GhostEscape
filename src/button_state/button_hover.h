#ifndef BUTTON_HOVER_H
#define BUTTON_HOVER_H

#include "button_state.h"

class ButtonHover : public ButtonState
{
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual bool handleEvents(SDL_Event& event) override;
};



#endif // BUTTON_HOVER_H