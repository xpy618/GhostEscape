#ifndef AFFILIATE_BAR_H
#define AFFILIATE_BAR_H

#include "../core/object_affiliate.h"

class AffiliateBar : public ObjectAffiliate
{
protected:
    float percentage_ = 1.0f;  //百分比
    SDL_FColor color_high_ = {0, 1, 0, 1};  // green
    SDL_FColor color_mid_ = {1, 0.65f, 0, 1};  // orange
    SDL_FColor color_low_ = {1, 0, 0, 1};  // red

public:
    static AffiliateBar* addAffiliateBarChild(ObjectScreen* parent, glm::vec2 size, Anchor anchor = Anchor::CENTER);
    virtual void render () override;

    //getters and setters
    float getPercentage() { return percentage_; }
    void setPercentage(float percentage) { percentage_ = percentage; }

    SDL_FColor getColorHigh() { return color_high_; }
    void setColorHigh(SDL_FColor color) { color_high_ = color; }
    SDL_FColor getColorMid() { return color_mid_; }
    void setColorMid(SDL_FColor color) { color_mid_ = color; }
    SDL_FColor getColorLow() { return color_low_; }
    void setColorLow(SDL_FColor color) { color_low_ = color; }
};





#endif // AFFILIATE_BAR_H