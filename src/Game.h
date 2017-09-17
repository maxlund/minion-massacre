//
// Created by johan on 2017-05-08.
//

#ifndef TDDI22_PROJEKT_GAME_H
#define TDDI22_PROJEKT_GAME_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "Level.h"
//#include "Button.h"
//#include "Tower.h"

// Forward declaration to prevent circular import
class Tower;
//class Arrow_tower;
class Minion;
class Movable;
class Projectile;
class Obstacle;
class Button;

class Game
{
public:
    Game(sf::RenderWindow &);
    void run();
    static sf::Time getElapsedTime();
    static Level & getLevel();
    static std::vector<std::unique_ptr<Tower>> & getTowers();
    static std::vector<std::unique_ptr<Minion>> & getMinions();
    static std::vector<std::unique_ptr<Projectile>> & getProjectiles();
    static std::vector<std::unique_ptr<Obstacle>> & getObstacles();
    template <typename T>
    static int cleanupProjectiles(std::vector<T> &);
    template <typename T>
    static int cleanupObstacles(std::vector<T> &);
    template <typename T>
    static int cleanupMinions(std::vector<T> &);
    void setViewRect(sf::FloatRect const &);
    sf::Vector2f getMouseTileCoordinates();
    static float gameSpeed;

private:
    static int bank;
    static int lives;
    static int score;
    static int wave;
    sf::RenderWindow & window;
    sf::RenderTexture canvas;
    sf::FloatRect viewRect;
    static Level level;
    sf::Shader* damageShader;
    sf::Shader* grayShader;
    sf::Time lastDamage;
    static sf::Vector2f startPosition;
    static std::vector<std::unique_ptr<Tower>> towers;
    static std::vector<std::unique_ptr<Minion>> minions;
    static std::vector<std::unique_ptr<Projectile>> projectiles;
    static std::vector<std::unique_ptr<Obstacle>> obstacles;
    static sf::Clock mainClock;
    static sf::Clock frameClock;
    static sf::Clock minionClock;
    static sf::Clock waveClock;
    bool startNewWave{true};
    float minionHealth{100};
    float minionValue{1};
    std::vector<std::string> minionPaths{"../res/minion1.png", "../res/minion2.png", "../res/minion3.png"};
    static sf::Time gameTime;
    sf::Sprite followerSprite;
    sf::CircleShape followerSpriteRange;
    void restart();
    void setFollower(Button & b, sf::Text & towerText, sf::Sprite & followerSprite, std::string & followerType, bool & following, sf::RenderWindow & window, sf::FloatRect const & viewRect);
    void unMark(std::vector<std::unique_ptr<Tower>> & towers, std::vector<Button> & buttons);
};


#endif //TDDI22_PROJEKT_GAME_H
