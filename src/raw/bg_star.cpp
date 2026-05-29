#include "bg_star.h"
#include "../core/scene.h"

BgStar *BgStar::addBgStarChild(Object *parent, int num, float scale_far, float scale_mid, float scale_near)
{
    auto bg_star = new BgStar();
    bg_star->init();
    bg_star->setNum(num);
    bg_star->setScaleFar(scale_far);
    bg_star->setScaleMid(scale_mid);
    bg_star->setScaleNear(scale_near);
    bg_star->star_far_.reserve(num);  //预分配内存
    bg_star->star_mid_.reserve(num);
    bg_star->star_near_.reserve(num);
    auto extra = Game::GetInstance().getCurrentScene()->getWorldSize() - Game::GetInstance().getScreenSize();
    for (auto i = 0; i < num; ++i)
    {
        bg_star->star_far_.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreenSize() + extra * scale_far));
        bg_star->star_mid_.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreenSize() + extra * scale_mid));
        bg_star->star_near_.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreenSize() + extra * scale_near));
    }
    if (parent) parent->addChild(bg_star);
    return bg_star;
}

void BgStar::update(float dt)
{
    //更新颜色
    timer_ += dt;
    color_far_ = {0.5f + 0.5f * sinf(timer_ * 0.8f), 0.5f + 0.5f * sinf(timer_ * 0.9f), 0.5f + 0.5f * sinf(timer_ * 1.0f), 1};
    color_mid_ = {0.5f + 0.5f * sinf(timer_ * 0.7f), 0.5f + 0.5f * sinf(timer_ * 0.8f), 0.5f + 0.5f * sinf(timer_ * 0.9f), 1};
    color_near_ = {0.5f + 0.5f * sinf(timer_ * 0.6f), 0.5f + 0.5f * sinf(timer_ * 0.7f), 0.5f + 0.5f * sinf(timer_ * 0.8f), 1};
}

void BgStar::render()
{
    auto pos = - game.getCurrentScene()->getCameraPosition();
    game.drawPoints(star_far_, pos * scale_far_, color_far_);
    game.drawPoints(star_mid_, pos * scale_mid_, color_mid_);
    game.drawPoints(star_near_, pos * scale_near_, color_near_);
}
