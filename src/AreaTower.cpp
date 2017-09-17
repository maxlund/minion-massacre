//
// Created by johan on 2017-05-19.
//

#include <cmath>
#include "AreaTower.h"

AreaTower::AreaTower(std::string const &filePath, sf::Vector2f pixelCoordinates, float width, float height) :
        Tower(filePath, pixelCoordinates, width, height, TowerInfo("Area Tower", 96, 40, 1, 40, 50, 0))
{
    name = thisName;
}

std::vector<Projectile*> AreaTower::fire(Minion const & target)
{
    lastFire = Game::getElapsedTime();
    sf::Vector2f center{getPixelCoordinates().x + 7, getPixelCoordinates().y + 7};

    std::vector<Projectile*> projectiles;
    for (int i = 0; i < 360; i += 360 / 8)
    {
        projectiles.push_back(new Projectile("../res/area_projectile.png", center, i, -i, 18, 18, damage, 500, 0, sf::seconds(
                (static_cast<float>(range) * 1.1f) / 500)));
    }
    return projectiles;
}

bool AreaTower::upgrade()
{
    range += 6;
    rateOfFire *= 1.1;
    damage *= 1.4;
    upgradeCost *= 2;
    setRangeCircle();
    level++;
    return true;
}

TowerInfo AreaTower::getInfo() const
{
    return TowerInfo("Area Tower", range, damage, rateOfFire, cost, upgradeCost, level);
}
