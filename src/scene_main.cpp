#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "spawner.h"
#include "scene_title.h"
#include "screen/ui_mouse.h"
#include "screen/hud_stats.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "screen/hud_skill.h"
#include "world/spell.h"
#include "world/effect.h"
#include "raw/timer.h"
#include "raw/bg_star.h"
#include <fstream>

void SceneMain::init()
{
    Scene::init();
    SDL_HideCursor();
    Game::getInstance().playMusic("assets/bgm/OhMyGhost.ogg");
    world_size_ = Game::getInstance().getScreenSize() * 3.0f;
    camera_position_ = world_size_ / 2.0f - Game::getInstance().getScreenSize() / 2.0f;
    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f);
    addChild(player_);

    BgStar::addBgStarChild(this, 2000, 0.2f, 0.5f, 0.8f);

    end_timer_ = Timer::addTimerChild(this);

    spawner_ = new Spawner();
    spawner_->init();
    spawner_->setTarget(player_);
    addChild(spawner_);

    button_pause_ = HUDButton::addHUDButtonChild(this, Game::getInstance().getScreenSize() - glm::vec2(230.0f, 50.0f), "assets/UI/A_Pause1.png", "assets/UI/A_Pause2.png", "assets/UI/A_Pause3.png");
    button_restart_ = HUDButton::addHUDButtonChild(this, Game::getInstance().getScreenSize() - glm::vec2(140.0f, 50.0f), "assets/UI/A_Restart1.png", "assets/UI/A_Restart2.png", "assets/UI/A_Restart3.png");
    button_back_ = HUDButton::addHUDButtonChild(this, Game::getInstance().getScreenSize() - glm::vec2(50.0f, 50.0f), "assets/UI/A_Back1.png", "assets/UI/A_Back2.png", "assets/UI/A_Back3.png");

    hud_stats_ = HUDStats::addHUDStatsChild(this, player_, glm::vec2(30.0f));
    hud_text_score_ = HUDText::addHUDTextChild(this, "Store: 0", glm::vec2(Game::getInstance().getScreenSize().x - 120.f, 30.0f), glm::vec2(200, 50));

    auto scene = Game::getInstance().getCurrentScene();
    auto pos = glm::vec2(Game::getInstance().getScreenSize().x - 300, 30);
    auto hud_skill_ = HUDSkill::addHUDSkillChild(scene, "assets/UI/Electric-Icon.png", pos, 0.14f, Anchor::CENTER);

    player_->getWeapon()->setHudSkill(hud_skill_);  //技能与武器绑定

    ui_mouse_ = UIMouse::addUIMouseChild(this,"assets/UI/29.png", "assets/UI/30.png", 1.0); //最后添加
}

bool SceneMain::handleEvents(SDL_Event& event)
{
    if(Scene::handleEvents(event)) return true;
    return false;
}

void SceneMain::update(float dt)
{
    checkTimeManage(dt);  //必须在update的开头
    Scene::update(dt);
    updateScore();
    checkButtonPause();
    checkButtonRestart();
    checkButtonBack();
    if(player_ && !player_->getActive()){
        end_timer_->start();
        saveData("assets/score.dat");
    }
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

void SceneMain::saveData(const std::string &file_path)
{
    auto score = Game::getInstance().getHighScore();
    std::ofstream file(file_path, std::ios::binary);  //将数据从内存写入文件
    if (!file.is_open()) return;
    file.write(reinterpret_cast<const char*>(&score), sizeof(score));  //将所有数据类型改为字符类型，（字符，长度）
    file.close();
}   

void SceneMain::renderBackground()
{
    auto start =  - camera_position_;
    auto end = world_size_ - camera_position_;
    Game::getInstance().drawGrid(start, end, 80.0f, {0.5f, 0.5f, 0.5f, 1.0f});
    Game::getInstance().drawBoundary(start, end, 5.0f, {1.0f, 1.0f, 1.0f, 1.0f});
}

void SceneMain::updateScore()
{
    hud_text_score_->setText("Store: " + std::to_string(Game::getInstance().getScore()));
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
        saveData("assets/score.dat");
        Game::getInstance().setScore(0);
        auto scene = new SceneMain();        
        Game::getInstance().safeChangeScene(scene);
    }
}

void SceneMain::checkButtonBack()
{
    if (button_back_->getIsTrigger())
    {
        saveData("assets/score.dat");
        Game::getInstance().setScore(0);
        auto scene = new SceneTitle();
        Game::getInstance().safeChangeScene(scene);
    }
}

void SceneMain::checkEndTimer()
{
    if (!end_timer_->timerOut()) return;
    pause();
    button_restart_->setRenderPosition(Game::getInstance().getScreenSize() / 2.0f - glm::vec2(200.0f, 0.0f));
    button_restart_->setScale(3.5f);
    button_back_->setRenderPosition(Game::getInstance().getScreenSize() / 2.0f + glm::vec2(200.0f, 0.0f));
    button_back_->setScale(3.5f);
    button_pause_->setActive(false);
    end_timer_->stop();
}

void SceneMain::checkTimeManage(float &dt)
{
    if (Game::getInstance().getMouseButtons() & SDL_BUTTON_X2MASK){
        dt *= 0.1f;
    }
    if (Game::getInstance().getMouseButtons() & SDL_BUTTON_X1MASK){
        dt *= 2.0f;
    }
}
