#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Tower.h"
#include "Obstacle.h"

class Button: public sf::Drawable
{
public:
    Button(std::string const &filePath, sf::Vector2f coordinates, sf::Vector2f size, TowerInfo tower);
    Button(std::string const &filePath, sf::Vector2f coordinates, sf::Vector2f size, ObstacleInfo obstacleInfo);
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
    bool isHovered(float mouseX, float mouseY) const;
    void setColor(const sf::Color &color);
    sf::Sprite getSprite() const;
    TowerInfo getTowerInfo() const;
    std::string getTowerText() const;
    void setTowerText(std::string text);
    ObstacleInfo getObstacleInfo() const;
    void click();
    void hovered();
    bool isClicked() const;
    void unClick();
    std::string getObstacleType() const;
private:
    std::string obstacleType;
    sf::RectangleShape rectangle;
    sf::Sprite sprite;
    bool clicked;
    TowerInfo towerInfo;
    std::string towerText;
    ObstacleInfo obstacleInfo;
};

#endif
