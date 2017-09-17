//
// Created by johan on 2017-05-18.
//

#include "SpikeObstacle.h"

SpikeObstacle::SpikeObstacle(std::string const &filePath, sf::Vector2f position, float width, float height) :
        Obstacle(filePath, position, width, height, ObstacleInfo("Spike Obstacle",
                                                                 "Deals 20 damage",
                                                                 20, 50, 25))
{}

ObstacleInfo SpikeObstacle::getInfo() const
{
    return ObstacleInfo(type, description, damage, durability, cost);
}