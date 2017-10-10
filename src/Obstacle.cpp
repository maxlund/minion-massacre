//
// Created by johan on 2017-05-18.
//

#include "Obstacle.h"
#include <sstream>

Obstacle::Obstacle(std::string const & filePath, sf::Vector2f position, float width, float height, ObstacleInfo info) :
   Collidable(info.damage, info.durability), Entity(filePath, position, width, height),
   type{info.type},
   cost{info.cost},
   description{info.description}
{
   ++idCounter;
   id = idCounter;
}

Obstacle::~Obstacle()
{
   level->setTileInfo(level->pixelToTileCoordinates(pixelCoordinates), Level::TILE_PATH);
}

void Obstacle::drawDurabilityBar(sf::RenderTarget & renderTarget) const
{
   sf::RectangleShape durabilityBackground{sf::Vector2f(width, 5)};
   durabilityBackground.setFillColor(sf::Color::Cyan);
   durabilityBackground.setPosition(getPixelCoordinates() - sf::Vector2f(0, 10));

   sf::RectangleShape durabilityForeground{sf::Vector2f((static_cast<float>(durability) / static_cast<float>(maxDurability)) * width, 5)};
   durabilityForeground.setFillColor(sf::Color::Blue);
   durabilityForeground.setPosition(getPixelCoordinates() - sf::Vector2f(0, 10));

   renderTarget.draw(durabilityBackground);
   renderTarget.draw(durabilityForeground);
}

int Obstacle::getId() const
{
   return id;
}

std::string Obstacle::buildObstacleString(ObstacleInfo info)
{
   std::stringstream ss;
   ss << "Type: " << info.type << std::endl
      << info.description << std::endl
      << std::endl
      << "Durability: " << info.durability << std::endl
      << "Cost: " << info.cost;
   return ss.str();
}

