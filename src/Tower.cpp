//
// Created by joaka568 on 05/05/17.
//

#include "Tower.h"
#include <iostream>
#include <math.h>
#include <sstream>

using namespace std;

Tower::Tower(std::string const & filePath, sf::Vector2f pixelCoordinates,
             float width, float height, TowerInfo info):
   Entity(filePath, pixelCoordinates, width, height),
   range{info.range},
   damage{info.damage},
   rateOfFire{info.rateOfFire},
   cost{info.cost},
   upgradeCost{info.upgradeCost}
{
   marked = false;
   setRangeCircle();
}

Tower::~Tower() {}

void Tower::setRangeCircle()
{
   sf::CircleShape shape(range);
   shape.setOrigin(range-16, range-16); // Tar fram centrum på tornet
   shape.setPosition(getPixelCoordinates());
   shape.setFillColor(sf::Color::Transparent);
   if(marked)
   {
      shape.setOutlineColor(sf::Color::White);
      shape.setOutlineThickness(3.0);
   }
   else
   {
      shape.setOutlineColor(sf::Color::Black);
      shape.setOutlineThickness(0.8);
   }
   rangeCircle = shape;
}

void Tower::mark()
{
   rangeCircle.setOutlineColor(sf::Color::White);
   rangeCircle.setOutlineThickness(3.0);
   marked = true;
}

void Tower::hovered()
{
   rangeCircle.setOutlineColor(sf::Color::Black);
   rangeCircle.setOutlineThickness(0.8);
}

void Tower::unMark()
{
   rangeCircle.setOutlineColor(sf::Color::Transparent);
   marked = false;
}

bool Tower::isMarked() const
{
   return marked;
}

sf::CircleShape const & Tower::getRangeCircle() const
{
   return rangeCircle;
}

bool Tower::inRange(Minion const & minion)
{
   sf::Vector2f minionCoordinates = minion.getPixelCoordinates() + sf::Vector2f(minion.getSize().x / 2, minion.getSize().y / 2);
   sf::Vector2f towerCoordinates = getPixelCoordinates() + sf::Vector2f(16, 16);
   if (minionCoordinates.x < towerCoordinates.x - range || minionCoordinates.x > towerCoordinates.x + range
       || minionCoordinates.y < towerCoordinates.y - range || minionCoordinates.y > towerCoordinates.y + range)
   {
      return false;
   }

   //cirkelns ekvation (x-a)^2+(y-b)^2=r^2
   auto radius = sqrt(pow((minionCoordinates.x-getPixelCoordinates().x), 2) + pow((minionCoordinates.y-getPixelCoordinates().y),2));
   return radius <= range;
}


bool Tower::isReadyToFire() const
{
   return (Game::getElapsedTime() - lastFire).asSeconds() > (1 / rateOfFire);
}

int Tower::getCost()
{
   return cost;
}

string Tower::buildTowerString(TowerInfo info)
{
   stringstream ss;
   ss << "Type: " << info.type << endl
      << "Range: " << info.range << endl
      << "Damage: " << info.damage << endl
      << "Rate of fire: " << info.rateOfFire << endl
      << "Cost: " << info.cost << endl;
   return ss.str();
}

string Tower::buildTowerString(TowerInfo info, bool b)
{
   stringstream ss;
   ss << "Type: " << info.type << endl
      << "Range: " << info.range << endl
      << "Damage: " << info.damage << endl
      << "Rate of fire: " << info.rateOfFire << endl
      << "Level: " << info.level << endl
      << "Upgrade cost: " << info.upgradeCost << endl
      << "Sells for: " << info.upgradeCost / 3 << endl;
   return ss.str();
}
