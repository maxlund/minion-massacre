//
// Created by max on 5/11/17.
//


#include <cmath>
#include "BulletTower.h"

BulletTower::BulletTower(std::string const & filePath, sf::Vector2f pixelCoordinates, float width, float height) :
        Tower(filePath, pixelCoordinates, width, height, TowerInfo("Bullet Tower", 128, 35, 5, 35, 50, 0))
{
    name = thisName;
}

std::vector<Projectile*> BulletTower::fire(Minion const & target)
{
    lastFire = Game::getElapsedTime();
    sf::Vector2f center{getPixelCoordinates().x + 16, getPixelCoordinates().y + 16};

    // SFML:s Y-axis is inverted, "y - target.y" corrects for it
    float angle =  Movable::radiansToDegrees(atan2f(center.y - target.getPixelCoordinates().y,
                                                    target.getPixelCoordinates().x - center.x));
    std::vector<Projectile*> projectiles;
    projectiles.push_back(new Projectile("../res/bullet.png", center, angle, -angle, 12, 12, damage, 500, 0, sf::seconds(
            (static_cast<float>(range) * 1.1f) / 500)));
    return projectiles;

}

bool BulletTower::upgrade()
{
    range += 16;
    rateOfFire *= 1.1;
    damage *= 1.4;
    upgradeCost *= 2;
    setRangeCircle();
    level++;
    return true;
}

TowerInfo BulletTower::getInfo() const
{
    return TowerInfo("Bullet Tower", range, damage, rateOfFire, cost, upgradeCost, level);
}
