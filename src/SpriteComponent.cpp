#include "SpriteComponent.h"
#include "ObjectBase.h"

SpriteComponent::SpriteComponent(class ObjectBase* const owner, int drawOrder)
    :Component(owner,drawOrder)
    ,mDrawOrder(drawOrder)
    ,mSpriteWidth(0)
    ,mSpriteHeight(0)
{
    std::cout << "Create sprite component " << '\n';
}

SpriteComponent::~SpriteComponent()
{
    std::cout << "Delete sprite component " << '\n';
}


void SpriteComponent::Draw(sf::RenderWindow& window)
{
    mSprite.setPosition(mOwner->GetPosition());
    mSprite.setRotation(mOwner->GetRotation());
    mSprite.scale(mOwner->GetScale());
    FlipHorizontal(false);
    window.draw(mSprite);
}

void SpriteComponent::FlipHorizontal(bool flip)
{
    if(flip)
        mSprite.setTextureRect(sf::IntRect(mSpriteWidth, 0, -mSpriteWidth, mSpriteHeight));
    else
        mSprite.setTextureRect(sf::IntRect(0, 0, mSpriteWidth, mSpriteHeight));

}

void SpriteComponent::SetupSprite(const TextureMapper* textures,std::string token)
{
    //add to sprite
    const sf::Texture& texture = textures->Get(token);
    mSprite.setTexture(texture);
    // get values
    auto  textureSize = texture.getSize();
    mSpriteWidth = textureSize.x;
    mSpriteHeight = textureSize.y;
}

void SpriteComponent::SetSprite(sf::Sprite sprite)
{
    mSprite = sprite;
}
