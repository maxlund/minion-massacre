//
// Created by johan on 2017-05-07.
//

#ifndef TDDI22_PROJEKT_PROJECTILE_H
#define TDDI22_PROJEKT_PROJECTILE_H


#include "Collidable.h"

class Projectile : public Collidable, public Movable
{
public:

    Projectile(std::string const & filePath, sf::Vector2f, float angle, float spriteRotation, float width, float height,
               float damage, float speed, float splashSize, sf::Time lifeTime, int durability = 1);
    bool hasSplashDamage() const;
    sf::Vector2f getSplashSize() const;
    sf::Time const & getStartTime() const;
    sf::Time const & getLifeTime() const;
protected:
    float splashSize;
    sf::Time startTime;
    sf::Time lifeTime;
};


#endif //TDDI22_PROJEKT_PROJECTILE_H
