//
// Created by max on 5/11/17.
//


#include <cmath>
#include "FlameTower.h"


FlameTower::FlameTower(std::string const &filePath, sf::Vector2f pixelCoordinates, float width, float height) :
        Tower(filePath, pixelCoordinates, width, height, TowerInfo("Flame Tower", 70, 2, 60, 40, 50, 0))
{
    name = thisName;
}

std::vector<Projectile*> FlameTower::fire(Minion const & target)
{
    lastFire = Game::getElapsedTime();
    sf::Vector2f center{getPixelCoordinates().x + 7, getPixelCoordinates().y + 7};

    // SFML:s Y-axis is inverted, "y - target.y" corrects for it
    float angle = Movable::radiansToDegrees(atan2f(center.y - target.getPixelCoordinates().y,
                                                   target.getPixelCoordinates().x - center.x));
    std::vector<Projectile*> projectiles;

    projectiles.push_back(new Projectile("../res/fire.png", center, angle, 0, 18, 18, damage, 500, 0, sf::seconds(
            (static_cast<float>(range) * 1.1f) / 500)));
    return projectiles;
}

bool FlameTower::upgrade()
{
    range *= 1.075;
    damage *= 1.4;
    upgradeCost *= 2;
    setRangeCircle();
    level++;
    return true;
}

TowerInfo FlameTower::getInfo() const
{
    return TowerInfo("Flame Tower", range, damage, rateOfFire, cost, upgradeCost, level);
}
