#ifndef SPELL_FIRE_H
#define SPELL_FIRE_H

#include "spell_creator.h"

class SpellFire : public SpellCreator
{
public:
    virtual Spell* createSpell() override;
};





#endif // SPELL_FIRE_H