//
// Created by maxlu701 on 2017-05-19.
//

#ifndef TDDI22_PROJEKT_FLAMEEFFECT_H
#define TDDI22_PROJEKT_FLAMEEFFECT_H


#include "Effect.h"
#include <SFML/System/Clock.hpp>

class PoisonEffect: public Effect
{
public:
    PoisonEffect(Minion*);
    void update(sf::Time deltaTime) override;
private:
    sf::Clock poisonClock;
};


#endif //TDDI22_PROJEKT_FLAMEEFFECT_H
