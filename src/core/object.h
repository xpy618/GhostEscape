#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"
#include "defs.h"
#include <vector>

class Object {
protected:
    ObjectType type_ = ObjectType::NONE;
    Game& game = Game::GetInstance();
    std::vector<Object*> children_;
    std::vector<Object*> object_to_add_; 
    bool is_active_ = true; 
    bool need_remove_ = false; 
public:
    Object() = default;
    virtual ~Object() = default;   //所有的类，不在构造函数和析构函数中做任何事

    virtual void init() {}   //需要初始化，在init中做
    virtual void handleEvents(SDL_Event& event);
    virtual void update(float dt);
    virtual void render();
    virtual void clean();  //需要清理，在clean中做

    virtual void safeAddChild(Object* child) { object_to_add_.push_back(child); }
    virtual void addChild(Object* child) { children_.push_back(child);}
    virtual void removeChild(Object* child) {
         children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());}
    
    // getters and setters
    ObjectType getType() const { return type_; }
    void setType(ObjectType type) { type_ = type; }
    bool getActive() const { return is_active_; }
    void setActive(bool active) { is_active_ = active; }
    bool getNeedRemove() const { return need_remove_; }
    void setNeedRemove(bool remove) { need_remove_ = remove; }
};



#endif // OBJECT_H