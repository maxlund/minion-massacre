//
// Created by maxlu701 on 2017-05-19.
//

#ifndef TDDI22_PROJEKT_FREEZEOBSTACLE_H
#define TDDI22_PROJEKT_FREEZEOBSTACLE_H

#include "Obstacle.h"
#include "FreezeEffect.h"

class FreezeObstacle: public Obstacle
{
public:
    FreezeObstacle(std::string const & filePath, sf::Vector2f position, float width, float height);
    void onCollision(Minion&) override;
    ObstacleInfo getInfo() const override;
};


#endif //TDDI22_PROJEKT_FREEZEOBSTACLE_H
