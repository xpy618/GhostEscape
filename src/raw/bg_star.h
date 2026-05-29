#ifndef BG_STAR_H
#define BG_STAR_H

#include "../core/object.h"

class BgStar : public Object
{
protected:
    std::vector<glm::vec2> star_far_;
    std::vector<glm::vec2> star_mid_;
    std::vector<glm::vec2> star_near_;
    float scale_far_ = 0.2f;
    float scale_mid_ = 0.5f;
    float scale_near_ = 0.8f;
    SDL_FColor color_far_ = {0, 0, 0, 1};
    SDL_FColor color_mid_ = {0, 0, 0, 1};
    SDL_FColor color_near_ = {0, 0, 0, 1};
    float timer_ = 0.0f;
    int num_ = 2000;   //number of stars

public:
    static BgStar* addBgStarChild(Object* parent, int num, float scale_far, float scale_mid, float scale_near);
    virtual void update(float dt) override;
    virtual void render() override;

    //getters and setters
    void setNum(int num) { num_ = num; }
    void setScaleFar(float scale_far) { scale_far_ = scale_far; }
    void setScaleMid(float scale_mid) { scale_mid_ = scale_mid; }
    void setScaleNear(float scale_near) { scale_near_ = scale_near; }
};





#endif // BG_STAR_H