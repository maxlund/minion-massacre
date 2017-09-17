//
// Created by maxlu701 on 2017-05-19.
//

#ifndef TDDI22_PROJEKT_EFFECT_H
#define TDDI22_PROJEKT_EFFECT_H

#include <SFML/System/Time.hpp>

class Minion;

class Effect
{
public:
    Effect(Minion*);
    virtual void update(sf::Time deltaTime) = 0;
protected:
    Minion* myMinion;
};


#endif //TDDI22_PROJEKT_EFFECT_H
