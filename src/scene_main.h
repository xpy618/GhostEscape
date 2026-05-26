#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "core/scene.h"

class Spawner;
class Player;
class UIMouse;
class HUDStats;
class HUDText;
class SceneMain : public Scene
{
    Player* player_ = nullptr;
    Spawner* spawner_ = nullptr;
    UIMouse* ui_mouse_ = nullptr;
    HUDStats* hud_stats_ = nullptr;
    HUDText* hud_text_score_ = nullptr;
public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override;
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

private:
    void renderBackground();
    void updateScore();
};

#endif // SCENE_MAIN_H