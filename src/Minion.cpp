//
// Created by maxlu701 on 2017-05-04.
//

#include <iostream>
#include <cmath>
#include "Minion.h"
#include "ResourceManager.h"

Minion::Minion(std::string const & filePath,
               sf::Vector2f pixelCoordinates,
               float width, float height,
               float speed, float hel, float val) :
   Movable(filePath, pixelCoordinates, width, height, speed),
   health{hel},
   maxHealth{hel},
   value{val},
   originalSpeed{speed}
{
   effectShader = ResourceManager::loadShader("../res/shader_minion_effects.frag", sf::Shader::Fragment);
   effectShader->setUniform("texture", sf::Shader::CurrentTexture);
}

bool approximate(sf::Vector2f turnCoordinates, sf::Vector2f pixelCoordinates, float epsilon)
{
   return abs(static_cast<int>(turnCoordinates.x - pixelCoordinates.x)) < epsilon &&
          abs(static_cast<int>(turnCoordinates.y - pixelCoordinates.y)) < epsilon;
}

void Minion::move(sf::Time deltaTime)
{
   sf::Vector2f pixelCoordinates = getPixelCoordinates();

   // find in which 32x32 pixel tile the current pixel is located
   int x = static_cast<int>(pixelCoordinates.x);
   int y = static_cast<int>(pixelCoordinates.y);
   x = (x - (x % 32)) / 32;
   y = (y - (y % 32)) / 32;
   sf::Vector2f tileCoordinates{static_cast<float>(x), static_cast<float>(y)};
   sf::Vector2f turnCoordinates{static_cast<float>(x*32), static_cast<float>(y*32)};

   // check if minion is at goal/exit
   atExit = (level->getEndPositions().at(0) == tileCoordinates);

   if ( approximate(turnCoordinates, pixelCoordinates, 6) && !atExit )
   {
      // get the direction for current tile and set minion to that direction
      setAngle(level->getTileDirection(tileCoordinates));
      rotate(level->getTileDirection(tileCoordinates));
   }
   Movable::move(deltaTime);
}

bool Minion::hasReachedExit() const
{
   return atExit;
}

void Minion::setHealth(float h)
{
   health = h;
}

float Minion::getHealth() const
{
   return health;
}

float Minion::getMaxHealth()
{
   return maxHealth;
}

float Minion::getValue() const
{
   return value;
}

void Minion::draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const
{
   effectShader->setUniform("freezeScale", 1 - getSpeed() / getOriginalSpeed());
   effectShader->setUniform("poisonClock", poisonEffectTime);
   effectShader->setUniform("poisonScale", poisonEffectScale);
   renderStates.shader = effectShader;
   Entity::draw(renderTarget, renderStates);
}

void Minion::drawHealthBar(sf::RenderTarget & renderTarget) const
{
   sf::RectangleShape healthBackground{sf::Vector2f(width, 5)};
   healthBackground.setFillColor(sf::Color::Red);
   healthBackground.setPosition(getPixelCoordinates() - sf::Vector2f(0, 10));

   sf::RectangleShape healthForeground{sf::Vector2f(std::max(health / maxHealth, 0.0f) * width, 5)};
   healthForeground.setFillColor(sf::Color{0, 128, 0});
   healthForeground.setPosition(getPixelCoordinates() - sf::Vector2f(0, 10));

   renderTarget.draw(healthBackground);
   renderTarget.draw(healthForeground);
}

std::vector<Effect *> Minion::getActiveEffects()
{
   return activeEffects;
}

std::vector<int> Minion::getCollidedObstacleIds()
{
   return collidedObstacleIds;
}

void Minion::setCollidedObstacleIds(std::vector<int> obstacleIds)
{
   collidedObstacleIds = obstacleIds;
}

void Minion::addActiveEffect(Effect* effect)
{
   activeEffects.push_back(effect);
}

float Minion::getOriginalSpeed() const
{
   return originalSpeed;
}

sf::Shader *Minion::getShader()
{
   return effectShader;
}
