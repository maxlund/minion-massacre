//
// Created by johan on 2017-05-07.
//

#include "Collidable.h"

void Collidable::onCollision(Minion & minion)
{
    if (durability > 0)
        minion.setHealth(minion.getHealth() - damage);
    durability--;
}

Collidable::Collidable(float damage, int dur) : damage{damage}, durability{dur}
{}

int Collidable::getDurability() const
{
    return durability;
}
