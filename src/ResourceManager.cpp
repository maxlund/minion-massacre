#include "ResourceManager.h"

sf::Texture* ResourceManager::loadTexture(std::string fileName)
{
    if (textures.count(fileName) > 0)
    {
        return textures[fileName];
    }
    else
    {
        sf::Texture* texture = new sf::Texture();
        texture->loadFromFile(fileName);
        textures[fileName] = texture;
        return texture;
    }
}

sf::Font* ResourceManager::loadFont(std::string fileName)
{
    if (fonts.count(fileName) > 0)
    {
        return fonts[fileName];
    }
    else
    {
        sf::Font* font = new sf::Font();
        font->loadFromFile(fileName);
        fonts[fileName] = font;
        return font;
    }
}

sf::Shader* ResourceManager::loadShader(std::string fileName, sf::Shader::Type type)
{
    if (shaders.count(fileName) > 0)
    {
        return shaders[fileName];
    }
    else
    {
        sf::Shader* shader = new sf::Shader();
        shader->loadFromFile(fileName, type);
        shaders[fileName] = shader;
        return shader;
    }
}