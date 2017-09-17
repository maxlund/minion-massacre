//
// Created by max on 5/11/17.
//

#ifndef TDDI22_PROJEKT_LASERTOWER_H
#define TDDI22_PROJEKT_LASERTOWER_H

#include "Tower.h"
#include <iostream>

class FlameTower: public Tower
{
public:
    FlameTower(std::string const & filePath, sf::Vector2f pixelCoordinates,
    float width, float height);
    std::vector<Projectile*> fire(Minion const &) override;
    bool upgrade() override;
    TowerInfo getInfo() const override;

private:
    const std::string thisName{"Flame Tower"};
};


#endif //TDDI22_PROJEKT_LASERTOWER_H
