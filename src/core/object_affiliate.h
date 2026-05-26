#ifndef OBJECT_AFFILIATE_H
#define OBJECT_AFFILIATE_H

#include "object_screen.h"

class ObjectAffiliate: public Object
{
protected:
    ObjectScreen* parent_ = nullptr;  //父节点，实例化一个objectscreen，能直接借此访问其public函数
    glm::vec2 offset_ = glm::vec2(0, 0);  //偏移量
    glm::vec2 size_ = glm::vec2(0, 0);  //大小
    Anchor anchor_ = Anchor::CENTER; 

public:
    void setOffsetByAnchor(Anchor anchor);

    //getters and setters
    ObjectScreen* getParent() const { return parent_; }
    void setParent(ObjectScreen* parent) { parent_ = parent; }
    glm::vec2 getOffset() const { return offset_; }
    void setOffset(const glm::vec2 &offset) { offset_ = offset; }
    glm::vec2 getSize() const { return size_; }
    void setSize(const glm::vec2 size);
    void setScale(float scale);//缩放
    Anchor getAnchor() const { return anchor_; }
    void setAnchor(Anchor anchor) { anchor_ = anchor; }
}; 

#endif // OBJECT_AFFILIATE_H