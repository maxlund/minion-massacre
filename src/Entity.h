//
// Created by max on 5/3/17.
//

#ifndef TDDI22_PROJEKT_ENTITY_H
#define TDDI22_PROJEKT_ENTITY_H

#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Game.h"

class Entity: public sf::Drawable
{
public:
    Entity(std::string const & filePath,
           sf::Vector2f pixelCoordinates,
           float width, float height);
    virtual ~Entity() = 0;
    void setSprite(std::string const &);
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
    void setRotation(float angle);
    void setPixelCoordinates(sf::Vector2f);
    sf::Vector2f getPixelCoordinates() const;
    sf::Vector2f getSize() const;
    void rotate(float a);

protected:
    Level* level;
    sf::Vector2f pixelCoordinates;
    sf::Sprite sprite;
    float width;
    float height;
};

#endif //TDDI22_PROJEKT_ENTITY_H
