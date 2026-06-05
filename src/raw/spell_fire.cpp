#include "spell_fire.h"
#include "../core/scene.h"

Spell *SpellFire::createSpell()
{
    return Spell::addSpellChild(Game::getInstance().getCurrentScene(), "assets/effect/Explosion 2 SpriteSheet.png", glm::vec2(0), 20.0f, 2.0f);
}