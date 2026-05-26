#include "object.h"

void Object::handleEvents(SDL_Event &event)
{
    for (auto& child : children_){
        if(child->getActive()){
            child->handleEvents(event);
        }
    }
}

void Object::update(float dt) //迭代器写法可以删改元素
{
    for (auto& child : object_to_add_){
        addChild(child);
    }
    object_to_add_.clear();
    
    for (auto it = children_.begin(); it != children_.end();){
        auto child = *it;
        if(child->getNeedRemove()){
            it = children_.erase(it);
            child->clean();  //清理对象持有的资源，但对象还在
            delete child;  //释放指针指向的动态内存，但指针还在
            child = nullptr; //避免悬空指针
        } else{
            if (child->getActive()){
                child->update(dt);
            } 
            ++it;
        }
    }
}

void Object::render()
{
    for (auto& child : children_){
        if(child->getActive()){
            child->render();
        }
    }
}

void Object::clean()
{
    for (auto& child : children_){
        child->clean();
    }
    children_.clear();
}