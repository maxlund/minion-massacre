//
// Created by joaka568 on 08/05/17.
//

#include "ArrowTower.h"
#include <iostream>
#include <math.h>


ArrowTower::ArrowTower(std::string const &filePath, sf::Vector2f pixelCoordinates, float width, float height) :
        Tower(filePath, pixelCoordinates, width, height, TowerInfo("Arrow Tower", 128, 20, 4, 30, 50, 0))
{
    name = thisName;
}

ArrowTower::~ArrowTower()
{

}

int ArrowTower::getRange()
{
    return range;
}


bool ArrowTower::upgrade()
{
    range += 10;
    rateOfFire *= 1.1;
    damage *= 1.4;
    upgradeCost *= 2;
    setRangeCircle();
    level++;
    return true;
}

std::vector<Projectile*> ArrowTower::fire(Minion const & target)
{
        lastFire = Game::getElapsedTime();
        sf::Vector2f center{getPixelCoordinates().x + 16, getPixelCoordinates().y + 16};

        // SFML:s Y-axis is inverted, "y - target.y" corrects for it
        float angle =  Movable::radiansToDegrees(atan2f(center.y - target.getPixelCoordinates().y,
                                                        target.getPixelCoordinates().x - center.x));
        std::vector<Projectile*> projectiles;
        projectiles.push_back(new Projectile("../res/arrow.png", center, angle, (180-angle), 12, 12, damage, 800, 0, sf::seconds(
                (static_cast<float>(range) * 1.1f) / 800)));
    return projectiles;


}

TowerInfo ArrowTower::getInfo() const
{
    return TowerInfo("Arrow Tower", range, damage, rateOfFire, cost, upgradeCost, level);
}

