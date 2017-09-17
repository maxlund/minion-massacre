//
// Created by max on 5/3/17.
//

#ifndef TDDI22_PROJEKT_MOVABLE_H
#define TDDI22_PROJEKT_MOVABLE_H

#include "Entity.h"
#include <SFML/System/Time.hpp>

class Movable: public Entity
{
public:
    Movable(std::string const &filePath,
            sf::Vector2f pixelCoordinates,
            float width, float height, float speed);
    //virtual ~Movable() = 0;
    void setAngle(float);
    void setSpeed(float);
    float getSpeed() const;
    virtual void move(sf::Time deltaTime);
    static float degreesToRadians(float degrees);
    static float radiansToDegrees(float radians);
private:
    float angle;
    float speed;
};


#endif //TDDI22_PROJEKT_MOVABLE_H
