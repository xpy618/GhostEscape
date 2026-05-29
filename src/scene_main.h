#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "core/scene.h"

class Spawner;
class Player;
class UIMouse;
class HUDStats;
class HUDText;
class HUDButton;
class Timer;
class SceneMain : public Scene
{
    Player* player_ = nullptr;
    Spawner* spawner_ = nullptr;
    UIMouse* ui_mouse_ = nullptr;
    HUDStats* hud_stats_ = nullptr;
    HUDText* hud_text_score_ = nullptr;
    HUDButton* button_pause_ = nullptr;
    HUDButton* button_restart_ = nullptr;
    HUDButton* button_back_ = nullptr;
    Timer* end_timer_ = nullptr;

public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override;
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    virtual void saveData(const std::string& file_path) override;

private:
    void renderBackground();
    void updateScore();

    void checkButtonPause();
    void checkButtonRestart();
    void checkButtonBack();
    void checkEndTimer();
};

#endif // SCENE_MAIN_H