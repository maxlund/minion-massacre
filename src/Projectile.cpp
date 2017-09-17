//
// Created by johan on 2017-05-07.
//

#include "Projectile.h"

Projectile::Projectile(std::string const & filePath, sf::Vector2f position, float angle, float spriteRotation, float width, float height,
                       float damage, float speed, float splash, sf::Time lifeTime, int durability) :
        Collidable(damage, durability),
        Movable(filePath, position, width, height, speed),
        splashSize{splash},
        startTime{Game::getElapsedTime()},
        lifeTime{lifeTime}
{
    setRotation(spriteRotation);
    setAngle(angle);
}

bool Projectile::hasSplashDamage() const
{
    return splashSize > 0;
}

sf::Vector2f Projectile::getSplashSize() const
{
    return sf::Vector2f(splashSize, splashSize);
}

sf::Time const & Projectile::getStartTime() const
{
    return startTime;
}

sf::Time const & Projectile::getLifeTime() const
{
    return lifeTime;
}
