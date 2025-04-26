#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "TextureMapper.h"
#include "Component.h"
#include <iostream>

class SpriteComponent : public Component
{
    public:
        SpriteComponent(class ObjectBase* const owner, int drawOrder);
        virtual ~SpriteComponent();

        virtual void Draw(sf::RenderWindow& window);
        virtual void SetupSprite(const TextureMapper* textures,std::string token);
        virtual void SetSprite(sf::Sprite sprite);

        int GetDrawOrder() const { return mDrawOrder; }
        int GetSpriteHeight() const { return mSpriteHeight; }
        int GetSpriteWidth() const { return mSpriteWidth; }

    protected:
        sf::Sprite mSprite;
        int mDrawOrder;
        int mSpriteWidth;
        int mSpriteHeight;

        virtual void FlipHorizontal(bool flip);
};

#endif // SPRITECOMPONENT_H
