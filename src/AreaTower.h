//
// Created by johan on 2017-05-19.
//

#ifndef TDDI22_PROJEKT_AREATOWER_H
#define TDDI22_PROJEKT_AREATOWER_H


#include "Tower.h"

class AreaTower : public Tower
{
public:
    AreaTower(std::string const & filePath, sf::Vector2f pixelCoordinates,
    float width, float height);
    std::vector<Projectile*> fire(Minion const &) override;
    bool upgrade() override;
    TowerInfo getInfo() const override;

private:
    const std::string thisName{"Area Tower"};
};


#endif //TDDI22_PROJEKT_AREATOWER_H
