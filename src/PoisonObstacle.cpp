//
// Created by maxlu701 on 2017-05-19.
//

#include "PoisonObstacle.h"
#include "PoisonEffect.h"

PoisonObstacle::PoisonObstacle(std::string const &filePath, sf::Vector2f position, float width, float height) :
        Obstacle(filePath, position, width, height, ObstacleInfo("Poison Obstacle",
                                                                 "Deals damage over time",
                                                                 20, 50, 25))
{}

void PoisonObstacle::onCollision(Minion & minion)
{
    std::vector<int> collidedObstacleIds = minion.getCollidedObstacleIds();
    if (find(begin(collidedObstacleIds), end(collidedObstacleIds), id) == end(collidedObstacleIds))
    {
        collidedObstacleIds.push_back(id);
        minion.setCollidedObstacleIds(collidedObstacleIds);
        PoisonEffect* pe = new PoisonEffect(&minion);
        minion.addActiveEffect(pe);
        --durability;
    }
}

ObstacleInfo PoisonObstacle::getInfo() const
{
    return ObstacleInfo(type, description, damage, durability, cost);
}
