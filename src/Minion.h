//
// Created by maxlu701 on 2017-05-04.
//

#ifndef TDDI22_PROJEKT_MINION_H
#define TDDI22_PROJEKT_MINION_H

#include "Movable.h"
#include "Effect.h"

class Minion: public Movable
{
public:
    Minion(std::string const & filePath, sf::Vector2f pixelCoordinates,
           float width, float height,
           float speed, float health, float value);
    void move(sf::Time deltaTime) override;
    bool hasReachedExit() const;
    void setHealth(float);
    float getHealth() const;
    float getMaxHealth();
    float getValue() const;
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
    void drawHealthBar(sf::RenderTarget &) const;
    std::vector<Effect*> getActiveEffects();
    std::vector<int> getCollidedObstacleIds();
    void setCollidedObstacleIds(std::vector<int>);
    void addActiveEffect(Effect*);
    float getOriginalSpeed() const;
    sf::Shader* getShader();
    float poisonEffectTime;
    float poisonEffectScale;
private:
    bool atExit{false};
    float health;
    float maxHealth;
    float value;
    float originalSpeed;
    std::vector<Effect*> activeEffects;
    std::vector<int> collidedObstacleIds;
    sf::Shader* effectShader;
};


#endif //TDDI22_PROJEKT_MINION_H
