#ifndef SPELL_H
#define SPELL_H

#include "../core/object_world.h"
#include "../affiliate/sprite_anim.h"

class Spell : public ObjectWorld
{
protected:
    std::string file_path_;
    float scale_ = 1.0f;
    SpriteAnim* sprite_ = nullptr;
    float damage_ = 60.0f;

public:
    static Spell* addSpellChild(Object* parent, const std::string& file_path, glm::vec2 pos, float damage, float scale = 1.0f, Anchor anchor = Anchor::CENTER);
    void update(float dt) override;

    virtual Spell* clone() override;

    //getters and setters
    float getDamage() const { return damage_; }
    void setDamage(float damage) { damage_ = damage; }
    SpriteAnim* getSprite() const { return sprite_; }
    void setSprite(SpriteAnim* sprite) { sprite_ = sprite; }
    const std::string& getFilepath() const { return file_path_; }
    void setFilepath(const std::string& file_path) { file_path_ = file_path; }
    float getScale() const { return scale_; }
    void setScale(float scale) { scale_ = scale; }

private:
    void attack();
};




#endif // SPELL_H