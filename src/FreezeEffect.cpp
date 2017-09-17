//
// Created by maxlu701 on 2017-05-19.
//

#include "FreezeEffect.h"
#include "Minion.h"

FreezeEffect::FreezeEffect(Minion* minion) : Effect(minion)
{
    minion->setSpeed(minion->getSpeed() * 0.5f);
}

void FreezeEffect::update(sf::Time deltaTime)
{
    if (myMinion->getSpeed() < myMinion->getOriginalSpeed())
    {
        myMinion->setSpeed( myMinion->getSpeed() + (deltaTime.asSeconds() * 5));
    }
    else
    {
        myMinion->setSpeed(myMinion->getOriginalSpeed());
    }
}
