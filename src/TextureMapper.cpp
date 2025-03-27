#include "TextureMapper.h"

#include<assert.h>

TextureMapper::TextureMapper()
{
    //ctor
}

TextureMapper::~TextureMapper()
{
    //dtor
}


void TextureMapper::Load(std::string id,const std::string& filename)
{
    std::unique_ptr<sf::Texture> texture(std::make_unique<sf::Texture>());

    if(! texture->loadFromFile(filename))
     {
       throw std::runtime_error("TextureMapper::Load - failed to load " + filename);
     }


    auto inserted = mTextureMap.insert(std::make_pair(id, std::move(texture)));
    assert(inserted.second);

}

 sf::Texture& TextureMapper::Get(std::string id)
 {
    auto found = mTextureMap.find(id);
    assert(found != mTextureMap.end());

    return *found->second;
 }

 const sf::Texture& TextureMapper::Get(std::string id) const
 {
    auto found = mTextureMap.find(id);
    assert(found != mTextureMap.end());

    return *found->second;
 }

