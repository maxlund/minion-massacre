#include "Button.h"
#include <iostream>
#include <sstream>

using namespace std;

Button::Button(std::string const &filePath, sf::Vector2f coordinates, sf::Vector2f size, TowerInfo tower)
{
    rectangle.setPosition(coordinates);
    rectangle.setSize(size);
    rectangle.setFillColor(sf::Color::Transparent);
    sprite.setTexture(*ResourceManager::loadTexture(filePath));
    sprite.setPosition( rectangle.getPosition() );
    auto spriteSize = sprite.getTexture()->getSize();
    sprite.setScale(rectangle.getSize().x/spriteSize.x, rectangle.getSize().y/spriteSize.y);
    towerInfo = tower;
    towerText = Tower::buildTowerString(towerInfo);
    clicked = false;
    obstacleType = "";
}

Button::Button(std::string const &filePath, sf::Vector2f coordinates, sf::Vector2f size, ObstacleInfo obstacle)
{
    rectangle.setPosition(coordinates);
    rectangle.setSize(size);
    rectangle.setFillColor(sf::Color::Black);
    sprite.setTexture(*ResourceManager::loadTexture(filePath));
    sprite.setPosition( rectangle.getPosition() );
    auto spriteSize = sprite.getTexture()->getSize();
    sprite.setScale(rectangle.getSize().x/spriteSize.x, rectangle.getSize().y/spriteSize.y);
    obstacleInfo = obstacle;
    towerText = Obstacle::buildObstacleString(obstacleInfo);
    clicked = false;
    obstacleType = obstacleInfo.type;
}


void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(rectangle);
    target.draw(sprite, states);
}

bool Button::isHovered(float mouseX, float mouseY) const
{
    bool hovered=false;
    if ( mouseX >= rectangle.getPosition().x &&
            mouseX <= (rectangle.getPosition().x + rectangle.getSize().x) )
    {
        if ( mouseY >= rectangle.getPosition().y &&
                mouseY <= (rectangle.getPosition().y + rectangle.getSize().y) )
        {
            hovered=true;
        }
    }
    return hovered;
}

void Button::setColor(const sf::Color &color)
{
    rectangle.setFillColor(color);
}

sf::Sprite Button::getSprite() const
{
    sf::Sprite temp;
    temp = sprite;
    auto size = temp.getTexture()->getSize();
    temp.setScale( (float)32/size.x, (float)32/size.y );
    return temp;
}

TowerInfo Button::getTowerInfo() const
{
    return towerInfo;
}

std::string Button::getTowerText() const
{
    return towerText;
}

void Button::setTowerText(std::string text)
{
    towerText = text;
}

void Button::click()
{
    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color::Green);
    clicked = true;
}

void Button::hovered()
{
    if(!clicked)
    {
        rectangle.setFillColor(sf::Color::White);
    }
}

bool Button::isClicked() const
{
    return clicked;
}

void Button::unClick()
{
    clicked = false;
    rectangle.setOutlineColor(sf::Color::Transparent);
    rectangle.setFillColor(sf::Color::Transparent);
}

std::string Button::getObstacleType() const
{
    return obstacleType;
}

ObstacleInfo Button::getObstacleInfo() const
{
    return obstacleInfo;
}