//
// Created by johan on 2017-05-16.
//

#ifndef TDDI22_PROJEKT_BOMB_H
#define TDDI22_PROJEKT_BOMB_H


#include "Projectile.h"

class Bomb : public Projectile
{
public:
    Bomb(std::string const & filePath, sf::Vector2f, float angle, float spriteRotation, float width, float height,
    float damage, float speed, float splashSize, sf::Time lifeTime, int durability = 1);

    void onCollision(Minion &) override;
};


#endif //TDDI22_PROJEKT_BOMB_H
