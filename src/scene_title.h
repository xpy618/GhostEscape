#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "core/scene.h"

class HUDButton;
class SceneTitle : public Scene
{
protected:
    SDL_FColor boundary_color_ = {1.0f, 0.71f, 0.75f, 1.0f};
    float color_timer_ = 0.0f;
    HUDButton* button_start_ = nullptr;
    HUDButton* button_credits_ = nullptr;
    HUDButton* button_quit_ = nullptr;

public:
    virtual void init() override;
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

private:
    void renderBackground();
    void updateColor();
    void checkButtonQuit();
};





#endif // SCENE_TITLE_H