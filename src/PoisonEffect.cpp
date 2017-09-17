//
// Created by maxlu701 on 2017-05-19.
//

#include "PoisonEffect.h"
#include "Minion.h"

PoisonEffect::PoisonEffect(Minion* minion) : Effect(minion)
{
    poisonClock.restart();
    minion->setHealth(minion->getHealth() * 0.8f);
}

void PoisonEffect::update(sf::Time deltaTime)
{
    sf::Time poisonTime = poisonClock.getElapsedTime();
    if (poisonTime.asMilliseconds() > 1500)
    {
        myMinion->setHealth(myMinion->getHealth() * 0.8f);
        myMinion->poisonEffectScale = std::max(myMinion->getHealth() / myMinion->getMaxHealth(), 0.2f);
        myMinion->poisonEffectTime = 1.0f;
        poisonClock.restart();
    }
    myMinion->poisonEffectTime = std::max(myMinion->poisonEffectTime - deltaTime.asSeconds(), 0.0f);
}
