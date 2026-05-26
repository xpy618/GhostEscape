#ifndef UI_MOUSE_H
#define UI_MOUSE_H

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

class UIMouse : public ObjectScreen
{
protected:
    Sprite* sprite1_ = nullptr;
    Sprite* sprite2_ = nullptr;
    float timer_ = 0.0f;

public:
    static UIMouse* addUIMouseChild(Object* parent, const std::string& file_path1, const std::string& file_path2, float scale, Anchor anchor = Anchor::CENTER);
    virtual void update(float dt) override;

    //getters and setters
    Sprite* getSprite1() const { return sprite1_; }
    void setSprite1(Sprite* value) { sprite1_ = value; }
    Sprite* getSprite2() const { return sprite2_; }
    void setSprite2(Sprite* value) { sprite2_ = value; }

};


#endif // UI_MOUSE_H