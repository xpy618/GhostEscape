#ifndef SPELL_THUNDER_H
#define SPELL_THUNDER_H

#include "spell_creator.h"

class SpellThunder : public SpellCreator
{
public:
    virtual Spell* createSpell() override;
};



#endif // SPELL_THUNDER_H