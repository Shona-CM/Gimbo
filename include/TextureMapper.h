#ifndef TEXTUREMAPPER_H
#define TEXTUREMAPPER_H

#include <map>
#include <memory>
#include<string>

#include <SFML/Graphics.hpp>

class TextureMapper
{
    public:
        TextureMapper();
        ~TextureMapper();

        void Load(std::string id,const std::string& filename);
        sf::Texture& Get(std::string id);
        const sf::Texture& Get(std::string id) const;

    protected:

    private:
     std::map<std::string,std::unique_ptr<sf::Texture>> mTextureMap;
};

#endif // TEXTUREMAPPER_H



#ifndef TEXTUREMAPPER_H
#define TEXTUREMAPPER_H

#include <map>
#include <memory>
#include<string>

#include <SFML/Graphics.hpp>

class TextureMapper
{
    public:
        TextureMapper();
        ~TextureMapper();

        void Load(std::string id,const std::string& filename);
        sf::Texture& Get(std::string id);
        const sf::Texture& Get(std::string id) const;

    protected:

    private:
     std::map<std::string,std::unique_ptr<sf::Texture>> mTextureMap;
};

#endif // TEXTUREMAPPER_H




