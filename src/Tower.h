//
// Created by joaka568 on 05/05/17.
//

#ifndef TDDI22_PROJEKT_TOWER_H
#define TDDI22_PROJEKT_TOWER_H


#include "Entity.h"
#include "Minion.h"
#include "Projectile.h"
#include <vector>
#include <string>

struct TowerInfo
{
    TowerInfo(std::string type, int range, float damage, float rateOfFire, int cost, int upgradeCost, int level) :
        type{type}, range{range}, damage{damage}, rateOfFire{rateOfFire}, cost{cost}, upgradeCost{upgradeCost}, level{level}
    {}
    TowerInfo() :
        TowerInfo{"Undefined", 0, 0, 0, 0, 0, 0}
    {}
    std::string type;
    int range;
    float damage;
    float rateOfFire;
    int cost;
    int upgradeCost;
    int level;
};

class Tower: public Entity
{
public:
    Tower(std::string const & filePath, sf::Vector2f pixelCoordinates,
          float width, float height, TowerInfo info);
    virtual ~Tower() = 0;
    void setRangeCircle();
    void mark();
    void unMark();
    bool isMarked() const;
    void hovered();
    sf::CircleShape const & getRangeCircle() const;
    bool inRange(Minion const &);
    bool isReadyToFire() const;
    virtual std::vector<Projectile*> fire(Minion const &) = 0;
    int getCost();
    virtual bool upgrade() = 0;
    virtual TowerInfo getInfo() const = 0;
    static std::string buildTowerString(TowerInfo);
    static std::string buildTowerString(TowerInfo info, bool b);

protected:
    std::string name;
    unsigned int level{0};
    int cost;
    int upgradeCost;
    int range;
    sf::CircleShape rangeCircle;
    float damage;
    float rateOfFire;
    sf::Time lastFire;
    bool marked;
};


#endif //TDDI22_PROJEKT_TOWER_H
