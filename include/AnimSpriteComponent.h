#ifndef ANIMSPRITECOMPONENT_H
#define ANIMSPRITECOMPONENT_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "TextureMapper.h"

class SpriteComponent;

class AnimSpriteComponent : public SpriteComponent
{
    public:
        AnimSpriteComponent(class ObjectBase* const owner, int drawOrder);
        virtual ~AnimSpriteComponent();

        virtual void Update(sf::Time deltaTime);
        void SetAnimSprites(const TextureMapper* textures,std::string token, int textureCount);
        float GetAnimFPS() const { return mAnimFPS; }
        void SetAnimFPS(float fps) { mAnimFPS = fps; }
        void SetFrameStartAndEnd(int startFrame, int endFrame);

    private:
      std::vector<std::unique_ptr<sf::Sprite>> mAnimSprites;
	  float mCurrFrame;
	  float mAnimFPS;
	  int mFrameStart;
	  int mFrameEnd;
};

#endif // ANIMSPRITECOMPONENT_H
