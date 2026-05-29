#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "spawner.h"
#include "scene_title.h"
#include "screen/ui_mouse.h"
#include "screen/hud_stats.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "world/spell.h"
#include "world/effect.h"
#include "raw/timer.h"

void SceneMain::init()
{
    Scene::init();
    SDL_HideCursor();
    game.playMusic("assets/bgm/OhMyGhost.ogg");
    world_size_ = game.getScreenSize() * 3.0f;
    camera_position_ = world_size_ / 2.0f - game.getScreenSize() / 2.0f;
    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f);
    addChild(player_);

    end_timer_ = Timer::addTimerChild(this);

    spawner_ = new Spawner();
    spawner_->init();
    spawner_->setTarget(player_);
    addChild(spawner_);

    button_pause_ = HUDButton::addHUDButtonChild(this, game.getScreenSize() - glm::vec2(230.0f, 50.0f), "assets/UI/A_Pause1.png", "assets/UI/A_Pause2.png", "assets/UI/A_Pause3.png");
    button_restart_ = HUDButton::addHUDButtonChild(this, game.getScreenSize() - glm::vec2(140.0f, 50.0f), "assets/UI/A_Restart1.png", "assets/UI/A_Restart2.png", "assets/UI/A_Restart3.png");
    button_back_ = HUDButton::addHUDButtonChild(this, game.getScreenSize() - glm::vec2(50.0f, 50.0f), "assets/UI/A_Back1.png", "assets/UI/A_Back2.png", "assets/UI/A_Back3.png");

    hud_stats_ = HUDStats::addHUDStatsChild(this, player_, glm::vec2(30.0f));
    hud_text_score_ = HUDText::addHUDTextChild(this, "Store: 0", glm::vec2(game.getScreenSize().x - 120.f, 30.0f), glm::vec2(200, 50));

    ui_mouse_ = UIMouse::addUIMouseChild(this,"assets/UI/29.png", "assets/UI/30.png", 1.0); //最后添加
}

bool SceneMain::handleEvents(SDL_Event& event)
{
    if(Scene::handleEvents(event)) return true;
    return false;
}

void SceneMain::update(float dt)
{
    Scene::update(dt);
    updateScore();
    checkButtonPause();
    checkButtonRestart();
    checkButtonBack();
    if(player_ && !player_->getActive()) end_timer_->start();
    checkEndTimer();
}

void SceneMain::render()
{
    renderBackground();
    Scene::render();
}

void SceneMain::clean()
{
    Scene::clean();
}

void SceneMain::renderBackground()
{
    auto start =  - camera_position_;
    auto end = world_size_ - camera_position_;
    game.drawGrid(start, end, 80.0f, {0.5f, 0.5f, 0.5f, 1.0f});
    game.drawBoundary(start, end, 5.0f, {1.0f, 1.0f, 1.0f, 1.0f});
}

void SceneMain::updateScore()
{
    hud_text_score_->setText("Store: " + std::to_string(game.getScore()));
}

void SceneMain::checkButtonPause()
{
    if (!button_pause_->getIsTrigger()) return;
    if (is_pause_) resume();
    else pause();

}

void SceneMain::checkButtonRestart()
{
    if (button_restart_->getIsTrigger())
    {
        game.setScore(0);
        auto scene = new SceneMain();        
        game.safeChangeScene(scene);
    }
}

void SceneMain::checkButtonBack()
{
    if (button_back_->getIsTrigger())
    {
        game.setScore(0);
        auto scene = new SceneTitle();
        game.safeChangeScene(scene);
    }
}

void SceneMain::checkEndTimer()
{
    if (!end_timer_->timerOut()) return;
    pause();
    button_restart_->setRenderPosition(game.getScreenSize() / 2.0f - glm::vec2(200.0f, 0.0f));
    button_restart_->setScale(3.5f);
    button_back_->setRenderPosition(game.getScreenSize() / 2.0f + glm::vec2(200.0f, 0.0f));
    button_back_->setScale(3.5f);
    button_pause_->setActive(false);
    end_timer_->stop();
}
