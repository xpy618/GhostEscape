#include "sprite.h"

Texture::Texture(const std::string &file_path)
{
    texture = Game::GetInstance().getAssetStore()->getImage(file_path);
    SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

Sprite *Sprite::addSpriteChild(ObjectScreen *parent, const std::string &file_path, float scale, Anchor anchor)
{
    auto sprite = new Sprite();
    sprite->init();
    sprite->setAnchor(anchor);
    sprite->setTexture(Texture(file_path));  //先调用构造函数使用文件路径获得纹理，再set
    sprite->setScale(scale);
    sprite->setParent(parent); //this指针自动指向player
    parent->addChild(sprite);
    return sprite;
}

void Sprite::render()
{
    if (!texture_.texture || !parent_ || is_finish_) return;
    auto pos = parent_->getRenderPosition() + offset_;
    game.renderTexture(texture_, pos, size_, percentage_);   //解耦
}

void Sprite::setTexture(const Texture & texture)
{
    texture_ = texture;
    size_ = glm::vec2(texture.src_rect.w, texture.src_rect.h);
}
