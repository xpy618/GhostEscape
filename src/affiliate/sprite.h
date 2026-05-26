#ifndef SPRITE_H
#define SPRITE_H

#include "../core/object_affiliate.h"
#include <string>

struct Texture
{
    SDL_Texture* texture = nullptr;
    SDL_FRect src_rect = {0, 0, 0, 0};  //源矩形{x,y,w,h}，决定绘制纹理的哪一部分
    float angle = 0.0f;  //旋转角度
    bool is_flip = false;  //是否水平翻转
    Texture() = default;
    Texture(const std::string& file_path);
};


class Sprite : public ObjectAffiliate
{
protected:
    Texture texture_;
    bool is_finish_ = false;
    glm::vec2 percentage_ = glm::vec2 (1.0f);

public:
    static Sprite* addSpriteChild(ObjectScreen* parent, const std::string& file_path, float scale = 1.0f, Anchor anchor = Anchor::CENTER);

    Sprite() = default;
    virtual void render() override;
    //getters and setters
    Texture getTexture() const { return texture_; }
    virtual void setTexture(const Texture& texture);
    float getAngle() const { return texture_.angle; }
    void setAngle(float angle) { texture_.angle = angle; }
    bool getFlip() const { return texture_.is_flip; }
    void setFlip(bool is_flip) { texture_.is_flip = is_flip; }
    bool getFinish() { return is_finish_; }   
    void setFinish(bool is_finish) { is_finish_ = is_finish; }
    glm::vec2 getPercentage() const { return percentage_; }
    void setPercentage(glm::vec2 porcentage) { percentage_ = porcentage; }
};

#endif // SPRITE_H