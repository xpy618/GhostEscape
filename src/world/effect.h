#ifndef EFFECT_H
#define EFFECT_H

#include "../core/object_world.h"
#include "../affiliate/sprite_anim.h"

class Effect : public ObjectWorld
{
    SpriteAnim* sprite_ = nullptr;
    ObjectWorld* next_object_ = nullptr;  //效果结束后添加到场景

public:
    static Effect* addEffectChild(Object* parent, const std::string& file_path, glm::vec2 pos, float scale = 1.0f, ObjectWorld* next_object = nullptr);
    virtual void update(float dt) override;
    //getters and setters
    SpriteAnim* getSpriteAnim() const { return sprite_; }
    void setSpriteAnim(SpriteAnim* value) { sprite_ = value; }
    ObjectWorld* getNextObject() const { return next_object_; }
    void setNextObject(ObjectWorld* value) { next_object_ = value; }

private:
    void checkFinish();
};




#endif // EFFECT_H