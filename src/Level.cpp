#include "Level.h"
#include "ResourceManager.h"
#include <queue>
#include <iostream>

using namespace std;

Level::Level(string fileName)
{
    map.ParseFile(fileName);
    if (map.HasError())
    {
        throw logic_error{"Failed to load map"};
    }

    tileWidth = map.GetTileWidth();
    tileHeight = map.GetTileHeight();
    levelWidth = map.GetWidth() * tileWidth;
    levelHeight = map.GetHeight() * tileHeight;
    canvas.create(static_cast<unsigned int>(levelWidth),
                  static_cast<unsigned int>(levelHeight));

    string backgroundFileName;
    int tilesetWidth;

    for (Tmx::Tileset* tileSet : map.GetTilesets())
    {
        if (tileSet->GetName() == "Ground")
        {
            backgroundFileName = tileSet->GetImage()->GetSource();
            tilesetWidth = tileSet->GetImage()->GetWidth();
        }
    }

    for (Tmx::TileLayer* tileLayer : map.GetTileLayers())
    {
        if (tileLayer->GetName() == "Background")
        {
            for (int y = 0; y < map.GetHeight(); y++)
            {
                for (int x = 0; x < map.GetWidth(); x++)
                {
                    sf::Vector2f tileCoordinates{static_cast<float>(x), static_cast<float>(y)};
                    int id = tileLayer->GetTileId(x, y);
                    switch (id)
                    {
                        case 24:
                            level[tileCoordinates] = TILE_GROUND;
                            break;
                        case 93:
                            level[tileCoordinates] = TILE_PATH;
                            break;
                        default:
                            level[tileCoordinates] = TILE_GROUND;
                            break;
                    }
                    sf::Sprite sprite{*ResourceManager::loadTexture("../res/" + backgroundFileName)};
                    sf::IntRect rect((id * map.GetTileWidth()) % tilesetWidth,
                                     ((id * map.GetTileHeight()) / tilesetWidth) * map.GetTileHeight(),
                                     map.GetTileWidth(),
                                     map.GetTileHeight());
                    sprite.setTextureRect(rect);
                    sprite.setPosition(tileToPixelCoordinates(tileCoordinates));
                    canvas.draw(sprite);

                    // Required to prevent canvas being in an undefined state and inverting the Y-axis
                    canvas.display();
                }
            }
        }
    }

    for (Tmx::ObjectGroup* objectGroup : map.GetObjectGroups())
    {
        if (objectGroup->GetName() == "Waypoints")
        {
            for (Tmx::Object* object : objectGroup->GetObjects())
            {
                if (object->GetType() == "start")
                {
                    startPositions.emplace_back(object->GetX() / tileWidth, object->GetY() / tileHeight);
                }
                else if (object->GetType() == "end")
                {
                    endPositions.emplace_back(object->GetX() / tileWidth, (object->GetY() / tileHeight));
                }
            }
        }
    }
}

void Level::levelRestart()
{
    for (auto & element : level)
    {
        if (element.second == TILE_TOWER)
        {
            element.second = TILE_GROUND;
        }

        if (element.second == TILE_OBSTACLE)
        {
            element.second = TILE_PATH;
        }
    }
}
sf::Vector2f Level::pixelToTileCoordinates(sf::Vector2f const & pixelCoordinates) const
{
    int x = static_cast<int>(pixelCoordinates.x);
    int y = static_cast<int>(pixelCoordinates.y);
    x = (x - (x % tileWidth)) / tileWidth;
    y = (y - (y % tileHeight)) / tileHeight;
    sf::Vector2f tileCoordinates{static_cast<float>(x), static_cast<float>(y)};
    return tileCoordinates;
}

sf::Vector2f Level::tileToPixelCoordinates(sf::Vector2f const & tileCoordinates) const
{
    sf::Vector2f pixelCoordinates;
    pixelCoordinates.x = tileCoordinates.x * tileWidth;
    pixelCoordinates.y = tileCoordinates.y * tileHeight;
    return pixelCoordinates;
}

bool Level::inBounds(sf::Vector2f const & tileCoordinates) const
{
    sf::Vector2f pixelCoordinates;
    pixelCoordinates = tileToPixelCoordinates(tileCoordinates);
    return pixelCoordinates.x >= 0 && pixelCoordinates.x < levelWidth &&
           pixelCoordinates.y >= 0 && pixelCoordinates.y < levelHeight;
}

bool Level::passable(sf::Vector2f const & tileCoordinates) const
{
    return level.at(tileCoordinates) == TILE_PATH;
}

vector<sf::Vector2f> Level::neighbors(sf::Vector2f tileCoordinates) const
{
    float x = tileCoordinates.x;
    float y = tileCoordinates.y;
    vector<sf::Vector2f> dirs{ {x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1} };

    vector<sf::Vector2f> results;

    for (auto const & next : dirs)
    {
	if (inBounds(next) && passable(next))
	    results.push_back(next);
    }
		
    return results;
}

void Level::setTileDirection(sf::Vector2f next, sf::Vector2f current)
{
    if (next.x > current.x)
    {
        tileDirections[next] = 180; // tile path direction is west
    }
    else if (next.x < current.x)
    {
        tileDirections[next] = 0;  // tile path direction is east
    }
    else if (next.y > current.y)
    {
        tileDirections[next] = 90;  // tile path direction is north
    }
    else if (next.y < current.y)
    {
        tileDirections[next] = 270;  // tile path direction is south
    }
}

float Level::getTileDirection(sf::Vector2f const & tileCoordinates) const
{
    return tileDirections.at(tileCoordinates);
}

void Level::breadth_first_search(sf::Vector2f goal)
{
    queue<sf::Vector2f> frontier;
    frontier.push(goal);

    vector<sf::Vector2f> visited;
    visited.push_back(goal);

    while (!frontier.empty())
    {
        auto current = frontier.front();
        frontier.pop();

        for (auto next : neighbors(current))
        {
            if ( find(begin(visited), end(visited), next) == end(visited) )
            {
                frontier.push(next);
                visited.push_back(next);
                setTileDirection(next, current);
            }
        }
    }
}

void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    sf::Sprite background{canvas.getTexture()};
    target.draw(background, states);
}

std::vector<sf::Vector2f> Level::getStartPositions() const
{
    return startPositions;
}

std::vector<sf::Vector2f> Level::getEndPositions() const
{
    return endPositions;
}

int Level::getHeight() const
{
    return levelHeight;
}

int Level::getWidth() const
{
    return levelWidth;
}

int Level::getTileWidth() const
{
    return tileWidth;
}

int Level::getTileHeight() const
{
    return tileHeight;
}

Level::tileInfo Level::getTileInfo(sf::Vector2f tileCoordinates) const
{
    if (tileCoordinates.x < 0 || tileCoordinates.x >= levelWidth/tileWidth ||
        tileCoordinates.y < 0 || tileCoordinates.y >= levelHeight/tileHeight)
    {
        return TILE_INVALID;
    }

    return level.at(tileCoordinates);
}

void Level::setTileInfo(sf::Vector2f tileCoordinates, tileInfo info)
{
    level[tileCoordinates] = info;
}

