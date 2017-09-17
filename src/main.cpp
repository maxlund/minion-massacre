#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"
#include "ResourceManager.h"
#include "Game.h"


using namespace std;

std::map<std::string, sf::Texture*> ResourceManager::textures{};
std::map<std::string, sf::Font*> ResourceManager::fonts{};
std::map<std::string, sf::Shader*> ResourceManager::shaders{};
sf::Vector2f mouseTileCoordinates(sf::RenderWindow&, const Level&);

Level Game::level{"../res/level.tmx"};

int main()
{
   // sf::RenderWindow window{/*sf::VideoMode::getFullscreenModes().at(0) */ sf::VideoMode(840, 640), "Tower Defense" /* sf::Style::Fullscreen */};
    sf::RenderWindow window{sf::VideoMode::getDesktopMode(), "Tower Defense"/*, sf::Style::Fullscreen*/};
    Game game{window};
    sf::Vector2f levelSize{static_cast<float>(Game::getLevel().getWidth()),
                           static_cast<float>(Game::getLevel().getHeight())};
    float viewWidth = window.getSize().x * (levelSize.y / window.getSize().y);
    sf::FloatRect viewRect = sf::FloatRect(-(viewWidth - levelSize.x) / 2, 0, viewWidth, levelSize.y);
    game.setViewRect(viewRect);

    game.run();

    return 0;
}
