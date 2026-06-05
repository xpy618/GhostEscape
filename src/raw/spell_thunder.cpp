#include "spell_thunder.h"
#include "../core/scene.h"

Spell *SpellThunder::createSpell()
{
    return Spell::addSpellChild(Game::getInstance().getCurrentScene(), "assets/effect/Thunderstrike w blur.png", glm::vec2(0), 40.0f, 4.0f);
}
