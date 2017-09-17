#ifndef TDDI22_PROJEKT_LEVEL_H
#define TDDI22_PROJEKT_LEVEL_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <vector>
#include <tmxparser/Tmx.h>

namespace std
{
    template<>
    struct hash<sf::Vector2f>
    {
        float operator()(sf::Vector2f const & key) const
        {
            return key.x * 21721 + key.y;
        }
    };
}

class Level : public sf::Drawable
{
public:
    enum tileInfo
    {
        TILE_INVALID = 0,
        TILE_GROUND,
        TILE_PATH,
        TILE_TOWER,
        TILE_OBSTACLE
    };

    Level(std::string fileName);
    void draw(sf::RenderTarget &, sf::RenderStates) const override;
    sf::Vector2f pixelToTileCoordinates(sf::Vector2f const &) const;
    sf::Vector2f tileToPixelCoordinates(sf::Vector2f const &) const;
    bool inBounds(sf::Vector2f const &) const;
    bool passable(sf::Vector2f const &) const;
    std::vector<sf::Vector2f> neighbors(sf::Vector2f) const;
    void setTileDirection(sf::Vector2f, sf::Vector2f);
    void breadth_first_search(sf::Vector2f goal);
    float getTileDirection(sf::Vector2f const &) const;
    std::vector<sf::Vector2f> getStartPositions() const;
    std::vector<sf::Vector2f> getEndPositions() const;
    int getHeight() const;
    int getWidth() const;
    int getTileWidth() const;
    int getTileHeight() const;
    tileInfo getTileInfo(sf::Vector2f) const;
    void setTileInfo(sf::Vector2f, tileInfo);
    void levelRestart();
private:
    int levelWidth;
    int levelHeight;
    int tileWidth;
    int tileHeight;
    Tmx::Map map;
    std::unordered_map<sf::Vector2f, tileInfo> level;
    std::unordered_map<sf::Vector2f, float> tileDirections;
    std::vector<sf::Vector2f> startPositions;
    std::vector<sf::Vector2f> endPositions;
    sf::RenderTexture canvas;

};

#endif //TDDI22_PROJEKT_LEVEL_H
