#include "sprite_anim.h"

SpriteAnim *SpriteAnim::addSpriteAnimChild(ObjectScreen *parent, const std::string &file_path, float scale, Anchor anchor)
{
    auto sprite_anim = new SpriteAnim();
    sprite_anim->init();
    sprite_anim->setAnchor(anchor);
    sprite_anim->setTexture(Texture(file_path));  //先调用构造函数使用文件路径获得纹理，再set
    sprite_anim->setScale(scale);
    sprite_anim->setParent(parent); //this指针自动指向player
    parent->addChild(sprite_anim);
    return sprite_anim;
}

void SpriteAnim::update(float dt)
{
    if (is_finish_) return; 
    frame_time_ += dt;
    if(frame_time_ >= 1.0f / fps_)
    {
        current_frame_++;
        if (current_frame_ >= total_frames_)
        {
            current_frame_ = 0;
            if (!is_loop_) is_finish_ = true;
        }
        frame_time_ = 0.0f;
    }
    texture_.src_rect.x = texture_.src_rect.w * current_frame_;
}

void SpriteAnim::setTexture(const Texture &texture)
{
    texture_ = texture;  //texture_是成员变量,texture是参数用完就没了
    total_frames_ = static_cast<int>(texture.src_rect.w / texture.src_rect.h);
    texture_.src_rect.w = texture.src_rect.h;
    size_ = glm::vec2(texture_.src_rect.w, texture_.src_rect.h);
}
