#ifndef HUD_TEXT_H
#define HUD_TEXT_H

#include "../core/object_screen.h"
#include "../affiliate/text_label.h"
#include "../affiliate/sprite.h"

class HUDText : public ObjectScreen
{
protected:
    TextLabel *text_label_ = nullptr;
    Sprite *sprite_bg_ = nullptr;
    glm::vec2 size_ = glm::vec2(0, 0);  //背景图片大小
public:
    static HUDText* addHUDTextChild(Object *parent, const std::string &text, glm::vec2 render_pos, glm::vec2 size , const std::string &font_path = "assets/font/VonwaonBitmap-16px.ttf", int font_size = 20, const std::string &bg_path = "assets/UI/Textfield_01.png", Anchor anchor = Anchor::CENTER);

    void setBgSizeByText(float margin = 50.0f);
    //getters and setters
    TextLabel *getTextLabel() { return text_label_; }
    void setTextLabel(TextLabel *text_label) { text_label_ = text_label; }  //使用哪个文字框
    Sprite *getSpriteBg() { return sprite_bg_; }
    void setSpriteBg(Sprite *sprite_bg) { sprite_bg_ = sprite_bg;}
    void setSize(const glm::vec2 &size);

    void setText(const std::string &text) { text_label_->setText(text); }  //文字框里写什么字
    std::string getText() { return text_label_->getText(); }

    void setBackground(const std::string &file_path);

};




#endif // HUD_TEXT_H