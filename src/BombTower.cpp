//
// Created by max on 5/12/17.
//

#include <cmath>
#include "BombTower.h"
#include "Bomb.h"

BombTower::BombTower(std::string const &filePath, sf::Vector2f pixelCoordinates, float width, float height) :
        Tower(filePath, pixelCoordinates, width, height, TowerInfo("Bomb Tower", 128, 60, 1, 40, 50, 0))
{
    name = thisName;
}

std::vector<Projectile*> BombTower::fire(Minion const & target)
{
    lastFire = Game::getElapsedTime();
    sf::Vector2f center{getPixelCoordinates().x + 16, getPixelCoordinates().y + 16};

    // SFML:s Y-axis is inverted, "y - target.y" corrects for it
    float angle =  Movable::radiansToDegrees(atan2f(center.y - target.getPixelCoordinates().y,
                                                    target.getPixelCoordinates().x - center.x));
    std::vector<Projectile*> projectiles;
    projectiles.push_back(new Bomb("../res/bomb.png", center, angle, 0, 22, 22, damage, 300, splashSize, sf::seconds(
            (static_cast<float>(range) * 1.1f) / 300)));
    return projectiles;
}

bool BombTower::upgrade()
{
    range *= 1.05;
    damage *= 1.4;
    splashSize += 2;
    upgradeCost *= 2;
    setRangeCircle();
    level++;
    return true;
}

TowerInfo BombTower::getInfo() const
{
    return TowerInfo("Bomb Tower", range, damage, rateOfFire, cost, upgradeCost, level);
}
