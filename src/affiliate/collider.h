#ifndef COLLIDER_H
#define COLLIDER_H

#include "../core/object_affiliate.h"

class Spell;
class Collider : public ObjectAffiliate
{
    //友元
    friend Spell;
    enum class Type{
        RECTANGLE,   //size_的x为直径
        CIRCLE
    };
    Type type_ = Type::CIRCLE;    

public:
    virtual void render() override ;

    static Collider* addColliderChild(ObjectScreen* parent, const glm::vec2& size, Type type = Type::CIRCLE, Anchor anchor = Anchor::CENTER);
    bool isColliding(const Collider* other);

    //getters and setters
    Type getType() const { return type_; }
    void setType(Type type) { type_ = type; }
};




#endif // COLLIDER_H