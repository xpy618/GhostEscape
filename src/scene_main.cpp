#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"
#include "spawner.h"
#include "screen/ui_mouse.h"
#include "screen/hud_stats.h"
#include "screen/hud_text.h"
#include "world/spell.h"

void SceneMain::init()
{
    SDL_HideCursor();
    game.playMusic("assets/bgm/OhMyGhost.ogg");
    world_size_ = game.getScreenSize() * 3.0f;
    camera_position_ = world_size_ / 2.0f - game.getScreenSize() / 2.0f;
    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f);
    addChild(player_);

    spawner_ = new Spawner();
    spawner_->init();
    spawner_->setTarget(player_);
    addChild(spawner_);

    hud_stats_ = HUDStats::addHUDStatsChild(this, player_, glm::vec2(30.0f));
    hud_text_score_ = HUDText::addHUDTextChild(this, "Store: 0", glm::vec2(game.getScreenSize().x - 120.f, 30.0f), glm::vec2(200, 50));

    ui_mouse_ = UIMouse::addUIMouseChild(this,"assets/UI/29.png", "assets/UI/30.png", 1.0); //最后添加
}

void SceneMain::handleEvents(SDL_Event& event)
{
    Scene::handleEvents(event);
}

void SceneMain::update(float dt)
{
    Scene::update(dt);
    updateScore();
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
