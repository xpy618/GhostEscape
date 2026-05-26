#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

#include "../core/object_affiliate.h"
#include <string>

class TextLabel : public ObjectAffiliate
{
protected:
    TTF_Text* ttf_text_ = nullptr;
    std::string font_path_ ;
    int font_size_ = 16;

public:
    static TextLabel* addTextLabelChild(ObjectScreen* parent, const std::string& text, const std::string& font_path, int font_size, Anchor anchor = Anchor::CENTER);
    virtual void render() override;
    virtual void clean() override;
    //setters and getters
    void setFont(const std::string& font_path, int font_size);
    void setFontPath(std::string font_path);
    void setFontSize(int font_size);
    void setText(std::string ttf_text) { TTF_SetTextString (ttf_text_, ttf_text.c_str(), 0); }
    std::string getText() const { return ttf_text_->text; }

private:
    void updateSize();  //根据文字内容决定大小
};




#endif // TEXT_LABEL_H