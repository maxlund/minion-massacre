//
// Created by max on 5/3/17.
//

#include "Entity.h"
#include "ResourceManager.h"

Entity::Entity(std::string const & filePath,
               sf::Vector2f pixelCoordinates,
               float w, float h) :
        level{&Game::getLevel()},
        width{w},
        height{h}
{
    setSprite(filePath);
    setPixelCoordinates(pixelCoordinates);
}

void Entity::setSprite(std::string const & path)
{
    sprite.setTexture(*ResourceManager::loadTexture(path));
    sprite.setPosition(pixelCoordinates);
    auto size = sprite.getTexture()->getSize();
    sprite.setScale(width/size.x, height/size.y);
    sprite.setOrigin(size.x / 2, size.y / 2);
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform.translate(width / 2, height / 2);
    target.draw(sprite, states);
}

void Entity::setPixelCoordinates(sf::Vector2f c)
{
    pixelCoordinates = c;
    sprite.setPosition(pixelCoordinates);
}

sf::Vector2f Entity::getPixelCoordinates() const
{
    return pixelCoordinates;
}

sf::Vector2f Entity::getSize() const
{
    return sf::Vector2f(width, height);
}

void Entity::rotate(float a)
{
    sprite.setRotation(-a);
}

Entity::~Entity() {}

void Entity::setRotation(float angle)
{
    sprite.setRotation(angle);
}
