#ifndef WEAPON_H
#define WEAPON_H

#include "../core/object.h"
#include "../world/spell.h"
#include "../raw/spell_creator.h"

class Spell;
class Actor;
class HUDSkill;
class Weapon : public Object
{
protected:
    Actor* parent_ = nullptr;
    SpellCreator* spell_creator_ = nullptr;  
    SDL_MouseButtonFlags trigger_button_ = SDL_BUTTON_LEFT;
    HUDSkill* hud_skill_ = nullptr;
    std::string sound_path_ = "assets/sound/big-thunder.mp3";
    float cool_down_ = 1.0f;
    float mana_cost_ = 0.0f;
    float cool_down_timer_ = 0.0f;

public:
    static Weapon* addWeaponChild(Actor* parent, float cool_down, float mana_cost);
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;

    void attack(glm::vec2 position);
    bool canAttack() ;
    //getters and setters
    float getCoolDown() const { return cool_down_; };
    void setCoolDown(float cool_down) { cool_down_ = cool_down; };
    float getManaCost() const { return mana_cost_; };
    void setManaCost(float mana_cost) { mana_cost_ = mana_cost; };
    Actor* getParent() const { return parent_; };
    void setParent(Actor* parent) { parent_ = parent; };

    SpellCreator* getSpellCreator() const { return spell_creator_; };
    void setSpellCreator(SpellCreator* spell_creator) { spell_creator_ = spell_creator; };
    SDL_MouseButtonFlags getTriggerButton() const { return trigger_button_; };
    void setTriggerButton(SDL_MouseButtonFlags trigger_button) { trigger_button_ = trigger_button; };
    HUDSkill* getHudSkill() const { return hud_skill_; };
    void setHudSkill(HUDSkill* hud_skill) { hud_skill_ = hud_skill; };
    std::string getSoundPath() const { return sound_path_; };   
    void setSoundPath(std::string sound_path) { sound_path_ = sound_path; };


};



#endif // WEAPON_H