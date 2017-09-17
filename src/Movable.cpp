//
// Created by max on 5/3/17.
//

#include "Movable.h"
#include <math.h>
#include <iostream>

float Movable::degreesToRadians(float degrees)
{
    return static_cast<float>((degrees / 180) * M_PI);
}

float Movable::radiansToDegrees(float radians)
{
    return static_cast<float>(360 * radians / (2 * M_PI));
}

Movable::Movable(std::string const &filePath,
                 sf::Vector2f pixelCoordinates,
                 float width, float height, float s) :
        Entity(filePath, pixelCoordinates, width, height),
        speed{s}
{}

void Movable::setAngle(float a)
{
    angle = a;
}

float Movable::getSpeed() const
{
    return speed;
}

void Movable::setSpeed(float s)
{
    speed = s;
}
void Movable::move(sf::Time deltaTime)
{
    sf::Vector2f newCoordinates;
    float specificSpeed = speed * deltaTime.asSeconds();
    sf::Vector2f oldCoordinates = getPixelCoordinates();
    newCoordinates.x = oldCoordinates.x + cos(degreesToRadians(angle)) * specificSpeed;
    newCoordinates.y = oldCoordinates.y - sin(degreesToRadians(angle)) * specificSpeed; // -sin to correct for SFML:s inverted Y-axis
    setPixelCoordinates(newCoordinates);
}
