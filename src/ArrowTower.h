//
// Created by joaka568 on 08/05/17.
//

#ifndef TDDI22_PROJEKT_ARROW_TOWER_H
#define TDDI22_PROJEKT_ARROW_TOWER_H


#include "Tower.h"

class ArrowTower: public Tower
{
public:
    ArrowTower(std::string const &filePath, sf::Vector2f pixelCoordinates, float width, float height);
    ~ArrowTower() override;
    int getRange();
    bool upgrade() override;
    std::vector<Projectile*> fire(Minion const &) override;
    TowerInfo getInfo() const override;

private:
    const std::string thisName{"Arrow Tower"};
};


#endif //TDDI22_PROJEKT_ARROW_TOWER_H
