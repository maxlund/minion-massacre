//
// Created by johan on 2017-05-16.
//

#include <cmath>
#include "Bomb.h"

Bomb::Bomb(std::string const & filePath, sf::Vector2f position, float angle, float spriteRotation, float width, float height,
                       float damage, float speed, float splash, sf::Time lifeTime, int durability) :
        Projectile(filePath, position, angle, spriteRotation, width, height, damage, speed, splash, lifeTime, durability)
{}

void Bomb::onCollision(Minion & minion)
{
    if (durability-- > 0)
    {
        for (std::unique_ptr<Minion> const & m : Game::getMinions())
        {
            sf::Vector2f diff = pixelCoordinates - m->getPixelCoordinates() +
                    sf::Vector2f(m->getSize().x / 2, m->getSize().y / 2);
            if (sqrt(pow(diff.x, 2) + pow(diff.y, 2)) <= splashSize)
            {
                m->setHealth(m->getHealth() - damage);
            }
        }
    }
}