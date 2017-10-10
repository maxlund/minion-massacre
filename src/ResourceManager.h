//
// Created by johan on 2017-05-02.
//

#ifndef TDDI22_PROJEKT_RESOURCEMANAGER_H
#define TDDI22_PROJEKT_RESOURCEMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>

class ResourceManager
{
public:
   static sf::Texture* loadTexture(std::string fileName);
   static sf::Font* loadFont(std::string fileName);
   static sf::Shader* loadShader(std::string fileName, sf::Shader::Type);
   static std::map<std::string, sf::Texture*> textures;
   static std::map<std::string, sf::Font*> fonts;
   static std::map<std::string, sf::Shader*> shaders;
};


#endif //TDDI22_PROJEKT_RESOURCEMANAGER_H
