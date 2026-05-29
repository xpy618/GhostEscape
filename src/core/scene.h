#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include "glm/glm.hpp"
#include "object_world.h"
#include <vector>
#include <string>

class Scene : public Object
{
protected:
    glm::vec2 camera_position_ = glm::vec2(0, 0); //相机位置
    glm::vec2 world_size_ = glm::vec2(0);
    std::vector<ObjectWorld*> children_world_;
    std::vector<ObjectScreen*> children_screen_;
    bool is_pause_ = false;

public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init() override {}
    virtual bool handleEvents(SDL_Event& event) override ;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    virtual void addChild(Object* child) override ;
    virtual void removeChild(Object* child) override ;

    virtual void saveData(const std::string& ) {}
    virtual void loadData(const std::string& ) {}

    glm::vec2 worldToScreen(glm::vec2 world_position){ return world_position - camera_position_; }
    glm::vec2 screenToWorld(glm::vec2 screen_position){ return screen_position + camera_position_; }

    void pause();
    void resume();
    //getters and setters
    glm::vec2 getCameraPosition() const { return camera_position_; }
    void setCameraPosition(glm::vec2 camera_position);
    glm::vec2 getWorldSize() const { return world_size_; }
    void setWorldSize(glm::vec2 world_size) { world_size_ = world_size; }
    std::vector<ObjectWorld*>& getChildrenWorld() { return children_world_; }
    std::vector<ObjectScreen*>& getChildrenScreen(){ return children_screen_; }
};



#endif // SCENE_H