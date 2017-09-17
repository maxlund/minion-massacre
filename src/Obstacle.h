//
// Created by johan on 2017-05-18.
//

#ifndef TDDI22_PROJEKT_OBSTACLE_H
#define TDDI22_PROJEKT_OBSTACLE_H


#include "Collidable.h"

struct ObstacleInfo
{
    ObstacleInfo(std::string type, std::string description, float damage, int durability, int cost) :
    type{type}, description{description}, damage{damage}, durability{durability}, cost{cost}
    {}
    ObstacleInfo() :
            ObstacleInfo{"Undefined", "", 0, 0, 0}
    {}
    std::string type;
    std::string description;
    float damage;
    int durability;
    int cost;
};

class Obstacle : public Collidable, public Entity
{
public:
    ~Obstacle();
    void drawDurabilityBar(sf::RenderTarget &) const;
    static int idCounter;
    int getId() const;
    virtual ObstacleInfo getInfo() const = 0;
    static std::string buildObstacleString(ObstacleInfo);
protected:
    Obstacle(std::string const & filePath, sf::Vector2f position, float width, float height, ObstacleInfo);
    int id;
    int cost;
    std::string type;
    std::string description;
};


#endif //TDDI22_PROJEKT_OBSTACLE_H
