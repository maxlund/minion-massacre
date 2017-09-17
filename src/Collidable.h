//
// Created by johan on 2017-05-07.
//

#ifndef TDDI22_PROJEKT_COLLIDABLE_H
#define TDDI22_PROJEKT_COLLIDABLE_H


#include "Minion.h"

class Collidable
{
public:

    virtual void onCollision(Minion&);
    int getDurability() const;

protected:
    Collidable(float damage, int durability);
    int durability;
    int maxDurability{durability};
    float damage;
};


#endif //TDDI22_PROJEKT_COLLIDABLE_H
