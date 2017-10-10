//
// Created by johan on 2017-05-08.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include "Game.h"
#include "Tower.h"
#include "Button.h"
#include <sstream>
#include "BulletTower.h"
#include "FlameTower.h"
#include "BombTower.h"
#include "ArrowTower.h"
#include <memory>
#include <random>
#include "SpikeObstacle.h"
#include "FreezeObstacle.h"
#include "PoisonObstacle.h"
#include "AreaTower.h"

using namespace std;

const BulletTower bulletTowerTemplate{"../res/bullet_tower.png", sf::Vector2f(), 0, 0};
const FlameTower flameTowerTemplate{"../res/flame_tower.png", sf::Vector2f(), 0, 0};
const BombTower bombTowerTemplate{"../res/bomb_tower.png", sf::Vector2f(), 0, 0};
const ArrowTower arrowTowerTemplate{"../res/arrow_tower.png", sf::Vector2f(), 0, 0};
const AreaTower areaTowerTemplate{"../res/area_tower.png", sf::Vector2f(), 0, 0};
const SpikeObstacle spikeObstacleTemplate{"../res/spike_obstacle.png", sf::Vector2f(), 0, 0};
const FreezeObstacle freezeObstacleTemplate{"../res/freeze_obstacle.png", sf::Vector2f(), 0, 0};
const PoisonObstacle poisonObstacleTemplate{"../res/poison_obstacle.png", sf::Vector2f(), 0, 0};


const TowerInfo bulletTowerInfo = bulletTowerTemplate.getInfo();
const TowerInfo flameTowerInfo = flameTowerTemplate.getInfo();
const TowerInfo bombTowerInfo = bombTowerTemplate.getInfo();
const TowerInfo arrowTowerInfo = arrowTowerTemplate.getInfo();
const TowerInfo areaTowerInfo = areaTowerTemplate.getInfo();
const ObstacleInfo spikeObstacleInfo = spikeObstacleTemplate.getInfo();
const ObstacleInfo freezeObstacleInfo = freezeObstacleTemplate.getInfo();
const ObstacleInfo poisonObstacleInfo = poisonObstacleTemplate.getInfo();

sf::Vector2f Game::startPosition;
std::vector<std::unique_ptr<Tower>> Game::towers;
std::vector<std::unique_ptr<Minion>> Game::minions;
std::vector<std::unique_ptr<Projectile>> Game::projectiles;
std::vector<std::unique_ptr<Obstacle>> Game::obstacles;
sf::Clock Game::mainClock;
sf::Clock Game::frameClock;
sf::Clock Game::minionClock;
sf::Clock Game::waveClock;

int Game::bank = 100;
int Game::lives = 20;
int Game::score = 0;
int Game::wave = 1;
float getMouseX(sf::RenderWindow & window, sf::FloatRect const & viewRect);
float getMouseY(sf::RenderWindow & window, sf::FloatRect const & viewRect);
bool isHovered(const float mouseX, const float mouseY, sf::Text const & textB);
int Obstacle::idCounter = 0;
float Game::gameSpeed{1};
sf::Time Game::gameTime;
bool fun = false;

void preloadResources();

Game::Game(sf::RenderWindow & window) : window{window} {
   window.setKeyRepeatEnabled(false);
   window.setVerticalSyncEnabled(true);
   level.breadth_first_search(level.getEndPositions().at(0));
   startPosition = level.tileToPixelCoordinates(level.getStartPositions().at(0));
   preloadResources();
}


void Game::run()
{
   random_device rng;
   uniform_int_distribution<int> dist{0, static_cast<int>(level.getStartPositions().size() - 1)};
   auto minionPathIterator = begin(minionPaths);

   gameTime = mainClock.getElapsedTime();

   sf::Font font;
   font.loadFromFile("../res/OptimusPrinceps.ttf");

   sf::Text fps{"FPS: ", font, 15};
   fps.setFillColor(sf::Color::White);
   fps.setPosition(viewRect.left, viewRect.top);

   vector<Button> buttons;
   Button b("../res/flame_tower.png", sf::Vector2f(660, 30), sf::Vector2f(40, 40), flameTowerInfo);
   Button b1("../res/bomb_tower.png", sf::Vector2f(710, 30), sf::Vector2f(40, 40), bombTowerInfo);
   Button b2("../res/bullet_tower.png", sf::Vector2f(760, 30), sf::Vector2f(40, 40), bulletTowerInfo);
   Button b3("../res/arrow_tower.png", sf::Vector2f(660, 80), sf::Vector2f(40, 40), arrowTowerInfo);
   Button b4("../res/area_tower.png", sf::Vector2f(710, 80), sf::Vector2f(40, 40), areaTowerInfo);
   Button b5("../res/spike_obstacle.png", sf::Vector2f(660, 130), sf::Vector2f(40, 40), spikeObstacleInfo);
   Button b6("../res/freeze_obstacle.png", sf::Vector2f(710, 130), sf::Vector2f(40, 40), freezeObstacleInfo);
   Button b7("../res/poison_obstacle.png", sf::Vector2f(760, 130), sf::Vector2f(40, 40), poisonObstacleInfo);

   buttons.push_back(b);
   buttons.push_back(b1);
   buttons.push_back(b2);
   buttons.push_back(b3);
   buttons.push_back(b4);
   buttons.push_back(b5);
   buttons.push_back(b6);
   buttons.push_back(b7);

   string followerType;
   bool following = false;
   followerSprite.setColor(sf::Color::Transparent);
   followerSpriteRange.setFillColor(sf::Color::Transparent);
   followerSpriteRange.setOutlineColor(sf::Color::Transparent);
   followerSpriteRange.setOutlineThickness(2);

   sf::Text upgradeB;
   upgradeB.setPosition(660, 365);
   upgradeB.setString("Upgrade");
   upgradeB.setCharacterSize(18);
   upgradeB.setFont(font);
   upgradeB.setFillColor(sf::Color::Transparent);

   sf::Text sellB;
   sellB.setPosition(760, 365);
   sellB.setString("Sell");
   sellB.setCharacterSize(18);
   sellB.setFont(font);
   sellB.setFillColor(sf::Color::Transparent);

   sf::Text restartB;
   restartB.setPosition(level.getWidth() / 2 - 100, 375);
   restartB.setString("Restart");
   restartB.setCharacterSize(18);
   restartB.setFont(font);
   restartB.setFillColor(sf::Color::Red);

   sf::Text exitB;
   exitB.setPosition(level.getWidth() / 2 + 100, 375);
   exitB.setString("Exit");
   exitB.setCharacterSize(18);
   exitB.setFont(font);
   exitB.setFillColor(sf::Color::Red);

   sf::Text towerText;
   towerText.setString("");
   towerText.setPosition(660, 190);
   towerText.setCharacterSize(18);
   towerText.setFont(font);
   towerText.setFillColor(sf::Color::White);

   sf::Text playerStatusText;
   playerStatusText.setPosition(660, 400);
   playerStatusText.setFont(font);
   playerStatusText.setCharacterSize(18);
   playerStatusText.setFillColor(sf::Color::White);

   sf::Text funMode;
   funMode.setString("Fun Mode!");
   funMode.setPosition(660, 440);
   funMode.setFont(font);
   funMode.setCharacterSize(18);
   funMode.setFillColor(sf::Color::Transparent);

   canvas.create(static_cast<unsigned int>(viewRect.width + viewRect.left * 2),
                 static_cast<unsigned int>(viewRect.height));
   sf::Sprite canvasSprite;

   if (sf::Shader::isAvailable())
   {
      damageShader = ResourceManager::loadShader("../res/shader_player_damage.frag", sf::Shader::Fragment);
      damageShader->setUniform("texture", sf::Shader::CurrentTexture);

      grayShader = ResourceManager::loadShader("../res/shader_grayscale.frag", sf::Shader::Fragment);
      grayShader->setUniform("texture", sf::Shader::CurrentTexture);
   }

   while (window.isOpen())
   {
      sf::Event event;
      while (window.pollEvent(event))
      {

         if (event.type == sf::Event::Closed ||
             event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
         {
            window.close();
         }
         if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
         {
            bool pressed{false};

            for (unsigned int i=0; i<buttons.size(); i++)
            {
               buttons.at(i).unClick();
            }

            //Select tower
            if (getMouseX(window, viewRect) <= 640)
            {
               sf::Vector2f tileCoordinates = getMouseTileCoordinates();
               if (level.getTileInfo(tileCoordinates) == Level::TILE_TOWER)
               {
                  for (unique_ptr<Tower> const & tower: towers)
                  {
                     tower->unMark();
                  }
                  for (unique_ptr<Tower> const & tower: towers)
                  {
                     if (level.pixelToTileCoordinates(tower->getPixelCoordinates()) == tileCoordinates)
                     {
                        towerText.setFillColor(sf::Color::White);
                        towerText.setString(Tower::buildTowerString(tower->getInfo(), true));
                        tower->mark();
                        upgradeB.setFillColor(sf::Color::White);
                        sellB.setFillColor(sf::Color::White);
                        pressed = true;
                     }
                  }
               }
            }

            //Tower & obstacle placement
            if (followerSprite.getColor() == sf::Color::White)
            {
               sf::Vector2f tileCoordinates = getMouseTileCoordinates();
               if (getMouseX(window, viewRect) <= 640)
               {
                  if (followerType == "Bullet Tower" && level.getTileInfo(tileCoordinates) == Level::TILE_GROUND &&
                      bulletTowerInfo.cost <= bank)
                  {
                     bank -= bulletTowerInfo.cost;
                     level.setTileInfo(tileCoordinates, Level::TILE_TOWER);
                     towers.push_back(
                        make_unique<BulletTower>("../res/bullet_tower.png",
                                                 level.tileToPixelCoordinates(tileCoordinates),
                                                 32, 32));
                  }
                  else if (followerType == "Flame Tower")
                  {
                     if (level.getTileInfo(tileCoordinates) == Level::TILE_GROUND && flameTowerInfo.cost <= bank)
                     {
                        bank -= flameTowerInfo.cost;
                        level.setTileInfo(tileCoordinates, Level::TILE_TOWER);
                        towers.push_back(make_unique<FlameTower>("../res/flame_tower.png",
                                                                 level.tileToPixelCoordinates(tileCoordinates),
                                                                 32, 32));
                     }
                  }
                  else if (followerType == "Bomb Tower")
                  {
                     if (level.getTileInfo(tileCoordinates) == Level::TILE_GROUND && bombTowerInfo.cost <= bank)
                     {
                        bank -= bombTowerInfo.cost;
                        level.setTileInfo(tileCoordinates, Level::TILE_TOWER);
                        towers.push_back(make_unique<BombTower>("../res/bomb_tower.png",
                                                                level.tileToPixelCoordinates(tileCoordinates),
                                                                32, 32));
                     }
                  }
                  else if (followerType == "Arrow Tower")
                  {
                     if (level.getTileInfo(tileCoordinates) == Level::TILE_GROUND && arrowTowerInfo.cost <= bank)
                     {
                        bank -= arrowTowerInfo.cost;
                        level.setTileInfo(tileCoordinates, Level::TILE_TOWER);
                        towers.push_back(make_unique<ArrowTower>("../res/arrow_tower.png",
                                                                 level.tileToPixelCoordinates(tileCoordinates),
                                                                 32, 32));
                     }
                  }
                  else if (followerType == "Area Tower")
                  {
                     if (level.getTileInfo(tileCoordinates) == Level::TILE_GROUND && areaTowerInfo.cost <= bank)
                     {
                        bank -= areaTowerInfo.cost;
                        level.setTileInfo(tileCoordinates, Level::TILE_TOWER);
                        towers.push_back(make_unique<AreaTower>("../res/area_tower.png",
                                                                level.tileToPixelCoordinates(tileCoordinates),
                                                                32, 32));
                     }
                  }
                  else if (followerType == "Spike Obstacle")
                  {
                     if (level.getTileInfo(tileCoordinates) == Level::TILE_PATH && spikeObstacleInfo.cost <= bank)
                     {
                        bank -= spikeObstacleInfo.cost;
                        level.setTileInfo(tileCoordinates, Level::TILE_OBSTACLE);
                        obstacles.push_back(make_unique<SpikeObstacle>("../res/spike_obstacle.png",
                                                                       level.tileToPixelCoordinates(tileCoordinates),
                                                                       32, 32));
                     }
                  }
                  else if (followerType == "Freeze Obstacle")
                  {
                     if (level.getTileInfo(tileCoordinates) == Level::TILE_PATH && freezeObstacleInfo.cost <= bank)
                     {
                        bank -= freezeObstacleInfo.cost;
                        level.setTileInfo(tileCoordinates, Level::TILE_OBSTACLE);
                        obstacles.push_back(make_unique<FreezeObstacle>("../res/freeze_obstacle.png",
                                                                        level.tileToPixelCoordinates(tileCoordinates),
                                                                        32, 32));
                     }
                  }
                  else if (followerType == "Poison Obstacle")
                  {
                     if (level.getTileInfo(tileCoordinates) == Level::TILE_PATH && poisonObstacleInfo.cost <= bank)
                     {
                        bank -= poisonObstacleInfo.cost;
                        level.setTileInfo(tileCoordinates, Level::TILE_OBSTACLE);
                        obstacles.push_back(make_unique<PoisonObstacle>("../res/poison_obstacle.png",
                                                                        level.tileToPixelCoordinates(tileCoordinates),
                                                                        32, 32));
                     }
                  }
               }
               followerSprite.setColor(sf::Color::Transparent);
               followerSpriteRange.setOutlineColor(sf::Color::Transparent);
               following = false;
               pressed = true;
            }

            //Check if any button is pressed
            for (unsigned int i=0; i<buttons.size(); i++)
            {
               if( buttons.at(i).isHovered(getMouseX(window, viewRect), getMouseY(window, viewRect))
                   && bank >= buttons.at(i).getTowerInfo().cost
                   && bank >= buttons.at(i).getObstacleInfo().cost)
               {
                  for (unique_ptr<Tower> const & tower: towers)
                  {
                     tower->unMark();
                  }
                  buttons.at(i).click();
                  towerText.setFillColor(sf::Color::White);
                  followerSprite = buttons.at(i).getSprite();
                  followerSpriteRange.setRadius(buttons.at(i).getTowerInfo().range);
                  followerSpriteRange.setOrigin(followerSpriteRange.getRadius() - level.getTileWidth() / 2,
                                                followerSpriteRange.getRadius() - level.getTileHeight() / 2);

                  if (buttons.at(i).getObstacleType() != "")
                     followerType = buttons.at(i).getObstacleType();
                  else
                     followerType = buttons.at(i).getTowerInfo().type;

                  followerSprite.setPosition(static_cast<int>(getMouseX(window, viewRect) / level.getTileWidth()) * level.getTileWidth(),
                                             static_cast<int>(getMouseY(window, viewRect) / level.getTileHeight()) * level.getTileHeight());
                  followerSpriteRange.setPosition(followerSprite.getPosition());
                  followerSprite.setColor(sf::Color::White);
                  followerSpriteRange.setOutlineColor(sf::Color::White);
                  following = true;
                  pressed = true;
               }
            }

            //Upgrade
            if (upgradeB.getFillColor() != sf::Color::Transparent)
            {
               if (isHovered(getMouseX(window, viewRect), getMouseY(window, viewRect), upgradeB))
               {
                  for (unique_ptr<Tower> const & tower: towers)
                  {
                     if (tower->isMarked() && bank >= tower->getInfo().upgradeCost)
                     {
                        int upgradeCost = tower->getInfo().upgradeCost;
                        if (tower->upgrade())
                        {
                           bank -= upgradeCost;
                        }
                        towerText.setString(Tower::buildTowerString(tower->getInfo(), true));
                     }
                  }
                  pressed = true;
               }
            }

            //Sell
            if (sellB.getFillColor() != sf::Color::Transparent)
            {
               if (isHovered(getMouseX(window, viewRect), getMouseY(window, viewRect), sellB))
               {
                  for (unique_ptr<Tower> const & tower : towers)
                  {
                     if (tower->isMarked())
                     {
                        bank += (tower->getInfo().upgradeCost) / 3;
                        level.setTileInfo(level.pixelToTileCoordinates(tower->getPixelCoordinates()), Level::TILE_GROUND);
                        auto itt = find(begin(towers), end(towers), *&tower);
                        towers.erase(itt);
                     }
                  }
               }
            }

            if (!pressed)
            {
               for (unique_ptr<Tower> const & tower: towers)
               {
                  tower->unMark();
               }
               towerText.setFillColor(sf::Color::Transparent);
               sellB.setFillColor(sf::Color::Transparent);
               upgradeB.setFillColor(sf::Color::Transparent);
            }
         }

         if (event.type == sf::Event::MouseMoved)
         {
            if (!following)
            {
               for (unsigned int i=0; i<buttons.size(); i++)
               {
                  if (buttons.at(i).isHovered(getMouseX(window, viewRect), getMouseY(window, viewRect)))
                  {
                     buttons.at(i).hovered();
                     towerText.setFillColor(sf::Color::White);
                     towerText.setString(buttons.at(i).getTowerText());
                     for (unique_ptr<Tower> const & tower: towers)
                     {
                        tower->unMark();
                     }
                     upgradeB.setFillColor(sf::Color::Transparent);
                     sellB.setFillColor(sf::Color::Transparent);
                  }
                  else if (!buttons.at(i).isClicked())
                  {
                     buttons.at(i).setColor(sf::Color::Transparent);
                  }
               }
            }

            if (upgradeB.getFillColor() != sf::Color::Transparent)
            {
               if (isHovered(getMouseX(window, viewRect), getMouseY(window, viewRect), upgradeB))
                  upgradeB.setFillColor(sf::Color::Red);
               else
                  upgradeB.setFillColor(sf::Color::White);
            }

            if (sellB.getFillColor() != sf::Color::Transparent)
            {
               if (isHovered(getMouseX(window, viewRect), getMouseY(window, viewRect), sellB))
                  sellB.setFillColor(sf::Color::Red);
               else
                  sellB.setFillColor(sf::Color::White);
            }

            bool towerMarked = false;
            for (unique_ptr<Tower> const & tower: towers)
            {
               if (tower->isMarked())
                  towerMarked = true;
            }

            if(!towerMarked)
            {
               for (unique_ptr<Tower> const & tower: towers)
               {
                  tower->unMark();
               }


               sf::Vector2f tileCoordinates = getMouseTileCoordinates();
               if (level.getTileInfo(tileCoordinates) == Level::TILE_TOWER)
               {
                  for (unique_ptr<Tower> const & tower: towers)
                  {
                     if (level.pixelToTileCoordinates(tower->getPixelCoordinates()) == tileCoordinates)
                     {
                        towerText.setFillColor(sf::Color::White);
                        towerText.setString(Tower::buildTowerString(tower->getInfo(), true));
                        tower->hovered();
                     }
                     else
                     {
                        tower->unMark();
                     }
                  }
               }
            }
            followerSprite.setPosition(getMouseTileCoordinates().x * level.getTileWidth(),
                                       getMouseTileCoordinates().y * level.getTileHeight());
            followerSpriteRange.setPosition(followerSprite.getPosition());
         }

         //Hotkeys
         if (event.type == sf::Event::KeyPressed)
         {
            if(event.key.code == sf::Keyboard::Num1)
            {
               unMark(towers, buttons);
               setFollower(buttons.at(0), towerText, followerSprite, followerType, following, window, viewRect);
            }
            else if(event.key.code == sf::Keyboard::Num2)
            {
               unMark(towers, buttons);
               setFollower(buttons.at(1), towerText, followerSprite, followerType, following, window, viewRect );
            }
            else if(event.key.code == sf::Keyboard::Num3)
            {
               unMark(towers, buttons);
               setFollower(buttons.at(2), towerText, followerSprite, followerType, following, window, viewRect );
            }
            else if(event.key.code == sf::Keyboard::Num4)
            {
               unMark(towers, buttons);
               setFollower(buttons.at(3), towerText, followerSprite, followerType, following, window, viewRect );
            }
            else if(event.key.code == sf::Keyboard::Num5)
            {
               unMark(towers, buttons);
               setFollower(buttons.at(4), towerText, followerSprite, followerType, following, window, viewRect );
            }
            else if(event.key.code == sf::Keyboard::Num6)
            {
               unMark(towers, buttons);
               setFollower(buttons.at(5), towerText, followerSprite, followerType, following, window, viewRect );
            }
            else if(event.key.code == sf::Keyboard::Num7)
            {
               unMark(towers, buttons);
               setFollower(buttons.at(6), towerText, followerSprite, followerType, following, window, viewRect );
            }
            else if(event.key.code == sf::Keyboard::Num8)
            {
               unMark(towers, buttons);
               setFollower(buttons.at(7), towerText, followerSprite, followerType, following, window, viewRect );
            }

            if(event.key.code == sf::Keyboard::F)
            {
               //Funmode
               fun = !fun;
               if (fun)
               {
                  funMode.setFillColor(sf::Color::Green);
               }
               else
               {
                  funMode.setFillColor(sf::Color::Transparent);
               }
            }
         }
      }

      canvas.clear();
      window.clear();
      canvas.draw(level);

      for (Button button : buttons)
      {
         if (grayShader != nullptr && (bank < button.getTowerInfo().cost
                                       || bank < button.getObstacleInfo().cost))
            window.draw(button, grayShader);
         else
            window.draw(button);

         if (button.isClicked())
            towerText.setString(button.getTowerText());
      }

      window.draw(towerText);
      window.draw(upgradeB);
      window.draw(sellB);
      window.draw(funMode);

      stringstream ss;
      ss << "Coins: " << Game::bank << endl
         << "Lives: " << Game::lives << endl
         << endl << endl << endl
         << "Score: " << Game::score << endl
         << "Wave: " << Game::wave << endl;
      playerStatusText.setString(ss.str());
      window.draw(playerStatusText);

      sf::Time deltaTime = frameClock.restart();
      sf::Time minionTime = minionClock.getElapsedTime();
      sf::Time waveTime = waveClock.getElapsedTime();

      fps.setString("FPS: " + to_string(static_cast<int>(1 / deltaTime.asSeconds())));
      window.draw(fps);

      deltaTime = sf::seconds(deltaTime.asSeconds() * gameSpeed);

      gameTime += deltaTime;
      sf::Time time = gameTime;

      if (waveTime.asMilliseconds() > 3000 / gameSpeed)
      {
         startNewWave = !startNewWave;
         waveClock.restart();
         if (startNewWave)
         {
            wave++;
            if (!fun)
            {
               startPosition = level.tileToPixelCoordinates(level.getStartPositions().at(static_cast<uint>(dist(rng))));
            }
            minionHealth *= 1.1;
            minionValue *= 1.05;
            minionPathIterator++;
            if (minionPathIterator == end(minionPaths))
               minionPathIterator = begin(minionPaths);
         }
      }

      if (startNewWave && minionTime.asMilliseconds() > 250 / gameSpeed)
      {
         minions.push_back(make_unique<Minion>(*minionPathIterator, startPosition, 32, 32, 120,
                                               minionHealth, minionValue));
         if (fun)
         {
            startPosition = level.tileToPixelCoordinates(level.getStartPositions().at(static_cast<uint>(dist(rng))));
         }
         minionClock.restart();
      }

      for (unique_ptr<Tower> const & tower : towers)
      {
         canvas.draw(*tower);
         canvas.draw(tower->getRangeCircle());
         for (auto it = minions.begin(); it != minions.end(); /* increment is inside loop */)
         {
            if (tower->inRange(**it) && tower->isReadyToFire())
            {
               std::vector<Projectile*> firedProjectiles = tower->fire(**it);
               for (Projectile* projectile : firedProjectiles)
               {
                  projectiles.push_back(unique_ptr<Projectile>(projectile));
               }
            }
            ++it;
         }
      }

      for (unique_ptr<Obstacle> const & obstacle : obstacles)
      {
         canvas.draw(*obstacle);
      }

      for (auto it = obstacles.begin(); it != obstacles.end(); it++)
      {
         (*it)->drawDurabilityBar(canvas);
      }

      for (auto it = minions.begin(); it != minions.end(); /* increment is inside loop */)
      {
         if ((*it)->hasReachedExit())
         {
            it = minions.erase(it);
            lives = max(lives - 1, 0);
            lastDamage = getElapsedTime();
         }
         else
         {
            (*it)->move(deltaTime);
            canvas.draw(**it);
            ++it;
         }
      }

      for (auto it = minions.begin(); it != minions.end(); it++)
      {
         (*it)->drawHealthBar(canvas);
      }

      for (unique_ptr<Projectile> const & projectile : projectiles)
      {
         projectile->move(deltaTime);
         canvas.draw(*projectile);
      }

      Game::cleanupProjectiles(projectiles);
      Game::cleanupObstacles(obstacles);
      score += Game::cleanupMinions(minions);

      for_each(begin(projectiles), end(projectiles), [](unique_ptr<Projectile> const & projectile)
               {
                  sf::FloatRect projectileHitbox{projectile->getPixelCoordinates(), projectile->getSize()};

                  for_each(begin(minions), end(minions), [&projectile, &projectileHitbox](unique_ptr<Minion> const & minion)
                           {
                              if (projectileHitbox.intersects(sf::FloatRect(minion->getPixelCoordinates(), minion->getSize())))
                                 projectile->onCollision(*minion);
                           });
               });

      for_each(begin(obstacles), end(obstacles), [](unique_ptr<Obstacle> const & obstacle)
               {
                  sf::FloatRect obstacleHitbox{obstacle->getPixelCoordinates(), obstacle->getSize()};

                  for_each(begin(minions), end(minions), [&obstacle, &obstacleHitbox](unique_ptr<Minion> const & minion)
                           {
                              if (obstacleHitbox.intersects(sf::FloatRect(minion->getPixelCoordinates(), minion->getSize())))
                                 obstacle->onCollision(*minion);
                           });
               });

      for (unique_ptr<Minion> const & minion : minions)
      {
         for (Effect* effect : minion->getActiveEffects())
         {
            effect->update(deltaTime);
         }
      }

      if (lives <= 0)
         gameSpeed = max(gameSpeed - 0.02f, 0.0f);

      if (gameSpeed == 0)
      {
         sf::Text gameOver{"Game Over", font, 100};
         gameOver.setFillColor(sf::Color::Red);
         gameOver.setOutlineColor(sf::Color(100, 0, 0));
         gameOver.setOutlineThickness(2);
         gameOver.setPosition(level.getWidth() / 2 - gameOver.getGlobalBounds().width / 2,
                              level.getHeight() / 2 - gameOver.getGlobalBounds().height);
         canvas.draw(gameOver);
         canvas.draw(restartB);
         canvas.draw(exitB);

         sf::Event end;
         while (window.pollEvent(end))
         {
            if (end.type == sf::Event::Closed ||
                end.type == sf::Event::KeyPressed && end.key.code == sf::Keyboard::Escape)
            {
               window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
               if (isHovered(getMouseX(window, viewRect), getMouseY(window, viewRect), restartB))
               {
                  restart();
               }
               if (isHovered(getMouseX(window, viewRect), getMouseY(window, viewRect), exitB))
               {
                  window.close();
               }
            }
         }
      }

      canvas.display();

      canvasSprite.setTexture(canvas.getTexture());
      if (damageShader != nullptr)
      {
         damageShader->setUniform("time", lastDamage.asSeconds() == 0 ? 1 : (getElapsedTime() - lastDamage).asSeconds());
         window.draw(canvasSprite, damageShader);
      } else
      {
         window.draw(canvasSprite);
      }
      window.draw(followerSprite);
      window.draw(followerSpriteRange);
      window.display();
   }
}

float getMouseX(sf::RenderWindow & window, sf::FloatRect const & viewRect)
{
   return (sf::Mouse::getPosition(window).x * (viewRect.width / window.getSize().x) + viewRect.left);
}

float getMouseY(sf::RenderWindow & window, sf::FloatRect const & viewRect)
{
   return (sf::Mouse::getPosition(window).y * (viewRect.height / window.getSize().y) + viewRect.top);
}

bool isHovered(const float mouseX, const float mouseY, sf::Text const & textB)
{
   bool hovered = false;
   if ( mouseX >= textB.getPosition().x &&
        mouseX <= (textB.getPosition().x + textB.getGlobalBounds().width + 5) )
   {
      if ( mouseY >= textB.getPosition().y &&
           mouseY <= (textB.getPosition().y + textB.getGlobalBounds().height + 5) )
      {
         hovered = true;
      }
   }
   return hovered;
}

sf::Time Game::getElapsedTime()
{
   return gameTime;
}

std::vector<unique_ptr<Tower>> & Game::getTowers()
{
   return towers;
}

std::vector<unique_ptr<Minion>> & Game::getMinions()
{
   return minions;
}

std::vector<unique_ptr<Projectile>> & Game::getProjectiles()
{
   return projectiles;
}

std::vector<unique_ptr<Obstacle>> &Game::getObstacles()
{
   return obstacles;
}

Level &Game::getLevel()
{
   return level;
}

template<typename T>
int Game::cleanupProjectiles(std::vector<T> & projectiles)
{
   auto it = remove_if(begin(projectiles), end(projectiles), [](unique_ptr<Projectile> const & projectile)
                       {
                          sf::Vector2f coords = projectile->getPixelCoordinates();
                          return coords.x < 0 || coords.x > level.getWidth()
                          || coords.y < 0 || coords.y > level.getHeight()
                          || projectile->getDurability() <= 0
                          || gameTime - projectile->getStartTime() > projectile->getLifeTime();
                       });
   int deleted = static_cast<int>(distance(it, end(projectiles)));
   projectiles.erase(it, end(projectiles));
   return deleted;
}

template<typename T>
int Game::cleanupObstacles(std::vector<T> & obstacles)
{
   auto it = remove_if(begin(obstacles), end(obstacles), [](unique_ptr<Obstacle> const & obstacle)
                       {
                          return obstacle->getDurability() <= 0;
                       });

   int deleted = static_cast<int>(distance(it, end(obstacles)));
   obstacles.erase(it, end(obstacles));
   return deleted;
}

template<typename T>
int Game::cleanupMinions(std::vector<T> & minions)
{
   auto it = remove_if(begin(minions), end(minions), [](unique_ptr<Minion> const & minion)
                       {
                          if (minion->getHealth() <= 0)
                             bank += minion->getValue();

                          return minion->getHealth() <= 0;
                       });

   int deleted = static_cast<int>(distance(it, end(minions)));
   minions.erase(it, end(minions));
   return deleted;
}

void Game::setViewRect(sf::FloatRect const & rect)
{
   viewRect = rect;
   window.setView(sf::View(viewRect));
}

sf::Vector2f Game::getMouseTileCoordinates()
{
   sf::Vector2f mousePixelCoordinates{ sf::Mouse::getPosition(window).x * (viewRect.width / window.getSize().x) + viewRect.left,
         sf::Mouse::getPosition(window).y * (viewRect.height / window.getSize().y) + viewRect.top };
   return sf::Vector2f(level.pixelToTileCoordinates(mousePixelCoordinates));
}

void preloadResources()
{
   ResourceManager::loadTexture("../res/minion1.png");
   ResourceManager::loadTexture("../res/minion2.png");
   ResourceManager::loadTexture("../res/minion3.png");
   ResourceManager::loadTexture("../res/bullet_tower.png");
   ResourceManager::loadTexture("../res/flame_tower.png");
   ResourceManager::loadTexture("../res/bomb_tower.png");
   ResourceManager::loadTexture("../res/arrow_tower.png");
   ResourceManager::loadTexture("../res/area_tower.png");
   ResourceManager::loadTexture("../res/bullet.png");
   ResourceManager::loadTexture("../res/fire.png");
   ResourceManager::loadTexture("../res/bomb.png");
   ResourceManager::loadTexture("../res/arrow.png");
   ResourceManager::loadTexture("../res/area_projectile.png");
   ResourceManager::loadTexture("../res/spike_obstacle.png");
   ResourceManager::loadTexture("../res/freeze_obstacle.png");
   ResourceManager::loadTexture("../res/poison_obstacle.png");
}

void Game::restart()
{
   bank            = 100;
   score           = 0;
   lives           = 20;
   wave            = 1;
   minionValue     = 1;
   minionHealth    = 100;
   gameSpeed       = 1;


   minions.erase(begin(minions),end(minions));
   towers.erase(begin(towers), end(towers));
   obstacles.erase(begin(obstacles), end(obstacles));

   level.levelRestart();
   canvas.clear();
   window.clear();

}

void Game::setFollower(Button & b, sf::Text & towerText, sf::Sprite & followerSprite, string & followerType, bool & following, sf::RenderWindow & window, sf::FloatRect const & viewRect)
{
   if (bank < b.getTowerInfo().cost || bank < b.getObstacleInfo().cost)
   {
      return;
   }
   b.click();
   towerText.setFillColor(sf::Color::White);
   followerSprite = b.getSprite();
   if (b.getObstacleType()!="")
   {
      followerType = b.getObstacleInfo().type;
   }
   else
   {
      followerType = b.getTowerInfo().type;
   }
   followerSprite.setPosition(getMouseTileCoordinates().x * level.getTileWidth(),
                              getMouseTileCoordinates().y * level.getTileHeight());
   followerSprite.setColor(sf::Color::White);
   following = true;
   followerSpriteRange.setRadius(b.getTowerInfo().range);
   followerSpriteRange.setOrigin(followerSpriteRange.getRadius() - level.getTileWidth() / 2,
                                 followerSpriteRange.getRadius() - level.getTileHeight() / 2);
   followerSpriteRange.setOutlineColor(sf::Color::White);
}

void Game::unMark(vector<unique_ptr<Tower>> & towers, vector<Button> & buttons)
{
   for (unique_ptr<Tower> const & tower: towers)
   {
      tower->unMark();
   }
   for (unsigned int i=0; i<buttons.size(); i++)
   {
      buttons.at(i).unClick();
   }
}
