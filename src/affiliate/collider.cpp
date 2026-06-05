#include "collider.h"

void Collider::render()
{
#ifdef DEBUG_MODE
    ObjectAffiliate::render();
    auto pos = parent_->getRenderPosition() + offset_;
    Game::getInstance().renderFillCircle(pos, size_, 0.3f); 
#endif
}

Collider *Collider::addColliderChild(ObjectScreen *parent, const glm::vec2 &size, Type, Anchor anchor)
{
    auto collider = new Collider();  //调用Collider的默认构造函数，创建碰撞体对象（new：在堆（动态内存）上分配对象并返回其指针）
    collider->init();
    collider->setAnchor(anchor);
    collider->setParent(parent);
    collider->setSize(size);
    collider->setOffsetByAnchor(anchor);
    parent->addChild(collider);
    return collider;
}

bool Collider::isColliding(const Collider *other) // other只是普通形参，与this不同
{
    if (other == nullptr) return false;  //函数类型是bool返回false，是void直接return
    if (type_ == Type::CIRCLE && other->getType() == Type::CIRCLE) {
        auto point1 = parent_->getPosition() + offset_ + size_ * 0.5f;
        auto point2 = other->getParent()->getPosition() + other->getOffset() + other->size_ * 0.5f;
        return glm::length(point1 - point2) < (size_.x + other->size_.x) * 0.5f;
    }
    //TODO: 其他类型的碰撞检测
    return false;
}