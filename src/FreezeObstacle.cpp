//
// Created by maxlu701 on 2017-05-19.
//

#include "FreezeObstacle.h"

FreezeObstacle::FreezeObstacle(std::string const &filePath, sf::Vector2f position, float width, float height) :
        Obstacle(filePath, position, width, height, ObstacleInfo("Freeze Obstacle",
                                                                 "Slows down minions",
                                                                 20, 50, 25))
{}

void FreezeObstacle::onCollision(Minion & minion)
{
    std::vector<int> collidedObstacleIds = minion.getCollidedObstacleIds();
    if (find(begin(collidedObstacleIds), end(collidedObstacleIds), id) == end(collidedObstacleIds))
    {
        collidedObstacleIds.push_back(id);
        minion.setCollidedObstacleIds(collidedObstacleIds);
        FreezeEffect* fe = new FreezeEffect(&minion);
        minion.addActiveEffect(fe);
        --durability;
    }
}

ObstacleInfo FreezeObstacle::getInfo() const
{
    return ObstacleInfo(type, description, damage, durability, cost);
}
