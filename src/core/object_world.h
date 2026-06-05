#ifndef OBJECT_WORLD_H
#define OBJECT_WORLD_H

#include "object_screen.h"
#include "../affiliate/collider.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 position_ = glm::vec2(0, 0);  //世界坐标
    Collider* collider_ = nullptr;   

public:
    virtual void init() override { type_ = ObjectType::OBJECT_WORLD; }
    virtual void update(float dt) override;

    virtual ObjectWorld* clone() { return nullptr; }  //默认不支持克隆，子类需要克隆的话重写这个方法

    virtual void takeDamage(float) {return;};
    
    //getters and setters
    virtual glm::vec2 getPosition() const override { return position_; }
    void setPosition(const glm::vec2 &position);
    virtual void setRenderPosition(const glm::vec2 &render_position) override;
    Collider* getCollider() const { return collider_; }
    void setCollider(Collider* collider) { collider_ = collider; }
};


#endif // OBJECT_WORLD_H