#include "scene_title.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "scene_main.h"
#include <cmath>

void SceneTitle::init()
{
    Scene::init();
    auto size = glm::vec2(game.getScreenSize().x / 2.0f, game.getScreenSize().y / 3.0f);
    HUDText::addHUDTextChild(this, "幽 灵 逃 生", game.getScreenSize()/2.0f - glm::vec2(0,100), size, "assets/font/VonwaonBitmap-16px.ttf", 64);
    HUDText::addHUDTextChild(this, "最高分：" + std::to_string(game.getHighScore()), game.getScreenSize()/2.0f + glm::vec2(0,100), glm::vec2(200, 50), "assets/font/VonwaonBitmap-16px.ttf", 32);

    button_start_ = HUDButton::addHUDButtonChild(this, game.getScreenSize()/2.0f + glm::vec2(-200, 200),"assets/UI/A_Start1.png", "assets/UI/A_Start2.png", "assets/UI/A_Start3.png", 2.0);
    button_credits_ = HUDButton::addHUDButtonChild(this, game.getScreenSize()/2.0f + glm::vec2(0, 200),"assets/UI/A_Credits1.png", "assets/UI/A_Credits2.png", "assets/UI/A_Credits3.png", 2.0);
    button_quit_ = HUDButton::addHUDButtonChild(this, game.getScreenSize()/2.0f + glm::vec2(200, 200),"assets/UI/A_Quit1.png", "assets/UI/A_Quit2.png", "assets/UI/A_Quit3.png", 2.0);  //父节点是场景，故静态函数不能用objectScreen

    auto text = game.loadTextFile("assets/credits.txt");
    credits_text_ = HUDText::addHUDTextChild(this, text, game.getScreenSize()/2.0f, glm::vec2(800, 800), "assets/font/VonwaonBitmap-16px.ttf", 16);
    credits_text_->setBgSizeByText();
    credits_text_->setActive(false);
}

void SceneTitle::handleEvents(SDL_Event &event)
{
    if (credits_text_->getActive()) {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            credits_text_->setActive(false);
        }
        return;
    }
    Scene::handleEvents(event);
}

void SceneTitle::update(float dt)
{
    color_timer_ += dt;
    updateColor();
    if (credits_text_->getActive()) return;
    Scene::update(dt);
    checkButtonQuit();
    checkButtonStart();
    checkButtonCredits();
}

void SceneTitle::render()
{
    Scene::render();
    renderBackground();
}

void SceneTitle::clean()
{
    Scene::clean();
}

void SceneTitle::renderBackground()
{
    game.drawBoundary(glm::vec2(30.0f), glm::vec2(game.getScreenSize() - 30.0f), 10, boundary_color_);
}

void SceneTitle::updateColor()
{
    boundary_color_.r = 0.5f + 0.5f*sinf(color_timer_ * 1.5f);
    boundary_color_.g = 0.5f + 0.5f*sinf(color_timer_ * 0.7f);
    boundary_color_.b = 0.5f + 0.5f*sinf(color_timer_ * 0.6f);

}

void SceneTitle::checkButtonQuit()
{
    if (button_quit_->getIsTrigger())
    {
        game.quit();
    }
}

void SceneTitle::checkButtonStart()
{
    if (button_start_->getIsTrigger())
    {
        auto scene = new SceneMain();
        game.safeChangeScene(scene);
    }
}

void SceneTitle::checkButtonCredits()
{
    if (button_credits_->getIsTrigger())
    {
        credits_text_->setActive(true);
    }
}
