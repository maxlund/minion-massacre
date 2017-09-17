//
// Created by johan on 2017-05-18.
//

#ifndef TDDI22_PROJEKT_SPIKEOBSTACLE_H
#define TDDI22_PROJEKT_SPIKEOBSTACLE_H


#include "Obstacle.h"

class SpikeObstacle : public Obstacle
{
public:
    SpikeObstacle(std::string const & filePath, sf::Vector2f position, float width, float height);
    ObstacleInfo getInfo() const override;
};


#endif //TDDI22_PROJEKT_SPIKEOBSTACLE_H
