#include "text_label.h"

TextLabel *TextLabel::addTextLabelChild(ObjectScreen *parent, const std::string &text, const std::string &font_path, int font_size, Anchor anchor)
//这里用objectscreen是因为parent需要调用getRenderPosition()函数，只在ObjectScreen类中有
{
    auto text_label = new TextLabel();
    text_label->init();
    text_label->setFont(font_path, font_size);
    text_label->setText(text);
    text_label->setAnchor(anchor);
    text_label->updateSize();
    if(parent){
        parent->addChild(text_label);
        text_label->setParent(parent);
    }
    return text_label;
}

void TextLabel::render()
{
    ObjectAffiliate::render();
    auto pos = parent_->getRenderPosition() + offset_;
    TTF_DrawRendererText(ttf_text_, pos.x, pos.y);
}

void TextLabel::clean()
{
    if(!ttf_text_)return;
    TTF_DestroyText(ttf_text_);
}

void TextLabel::setFont(const std::string &font_path, int font_size)
{
    font_path_ = font_path;
    font_size_ = font_size;
    auto font = game.getAssetStore()->getFont(font_path_, font_size_);
    if(!ttf_text_)ttf_text_ = game.createTTF_Text("",font_path_, font_size_);
    TTF_SetTextFont(ttf_text_, font);
    updateSize();
}

void TextLabel::setFontPath(std::string font_path)
{
    font_path_ = font_path;
    auto font = game.getAssetStore()->getFont(font_path_, font_size_);
    TTF_SetTextFont(ttf_text_, font);
    updateSize();
}

void TextLabel::setFontSize(int font_size)
{
    font_size_ = font_size;
    auto font = game.getAssetStore()->getFont(font_path_, font_size_);
    TTF_SetTextFont(ttf_text_, font);
    updateSize();
}

void TextLabel::setText(std::string ttf_text)
{
    TTF_SetTextString (ttf_text_, ttf_text.c_str(), 0); 
    updateSize();
}

void TextLabel::updateSize()
{
    int w,h;
    TTF_GetTextSize(ttf_text_, &w, &h);
    setSize(glm::vec2(w,h));
}
