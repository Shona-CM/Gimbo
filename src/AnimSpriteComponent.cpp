
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include <iostream>

AnimSpriteComponent::AnimSpriteComponent(class ObjectBase* const owner, int drawOrder)
    :SpriteComponent(owner, drawOrder)
	,mCurrFrame(0.0f)
	,mAnimFPS(24.0f)
	,mFrameStart(0)
	,mFrameEnd(1)
{
    std::cout << "Create Animated Sprite" << '\n';
}

AnimSpriteComponent::~AnimSpriteComponent()
{
    std::cout << "Delete Animated Sprite" << '\n';
    mAnimSprites.clear();
}


void AnimSpriteComponent::Update(sf::Time deltaTime)
{
   SpriteComponent::Update(deltaTime);

	if (mAnimSprites.size() > 0)
	{
		// Update the current frame based on frame rate
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime.asSeconds();

		// Wrap current frame if needed
		while (mCurrFrame >= mFrameEnd)
		{
			mCurrFrame -= mFrameEnd;
		}

		// Set the current texture
		SetSprite(*mAnimSprites[static_cast<int>(mCurrFrame)]);
		//std::cout << mCurrFrame << '\n';

		if(mCurrFrame > mFrameEnd)
            mCurrFrame = mFrameEnd;
        else if(mCurrFrame < mFrameStart)
            mCurrFrame = mFrameStart;
	}

}

void AnimSpriteComponent::SetAnimSprites(const TextureMapper* textures,std::string token, int textureCount)
{
  //expect count to start at 1 and  run to textureCount.
  for(int i = 1; i <= textureCount; i++)
  {
    std::string fullToken =  token + std::to_string(i);
    mAnimSprites.emplace_back(std::make_unique<sf::Sprite>(textures->Get(fullToken)));

    // get values
    auto texture = textures->Get(fullToken);
	auto  textureSize = texture.getSize();
	mSpriteWidth = textureSize.x;
	mSpriteHeight = textureSize.y;
  }

  SetSprite(*mAnimSprites[0]);
}

void AnimSpriteComponent::SetFrameStartAndEnd(int startFrame, int endFrame)
{
  mFrameStart = startFrame;
  mFrameEnd = endFrame;

  if(mFrameEnd == mFrameStart)
     mFrameEnd += 1;
}
