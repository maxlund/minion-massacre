//
// Created by maxlu701 on 2017-05-19.
//

#ifndef TDDI22_PROJEKT_FREEZEEFFECT_H
#define TDDI22_PROJEKT_FREEZEEFFECT_H

#include "Effect.h"

class FreezeEffect: public Effect
{
public:
    FreezeEffect(Minion*);
    void update(sf::Time deltaTime) override;
};


#endif //TDDI22_PROJEKT_FREEZEEFFECT_H
