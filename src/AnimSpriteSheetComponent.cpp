#include "AnimSpriteSheetComponent.h"

#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include <iostream>


AnimSpriteSheetComponent::AnimSpriteSheetComponent(class Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
	, mFrameStart(0)
	, mFrameEnd(1)
{
     std::cout << "Create Sprite Sheet Animated Sprite" << '\n';
}

AnimSpriteSheetComponent::~AnimSpriteSheetComponent()
{
    std::cout << "Delete Sprite Sheet Animated Sprite" << '\n';
}


void AnimSpriteSheetComponent::Draw(sf::RenderWindow& window)
{

    mSprite.setPosition(mOwner->GetPosition());
    mSprite.setRotation(mOwner->GetRotation());
    mSprite.scale(mOwner->GetScale());

    sf::IntRect displayRect = FlipSpriteHorizontal(true);
    mSprite.setTextureRect(displayRect);

    window.draw(mSprite);

    //std::cout << " rect  = " << source_rect.left << " "  << source_rect.top  <<'\n';
    //std::cout << " override frame  = " << mSprite.getTextureRect().left << " "  << mSprite.getTextureRect().top  <<'\n';
}

sf::IntRect AnimSpriteSheetComponent::FlipSpriteHorizontal(bool flip)
{
    if(flip)
    {
          sf::IntRect flipRect;
          flipRect.left = source_rect.left + source_rect.width;
          flipRect.width = -source_rect.width;
          flipRect.top = source_rect.top;
          flipRect.height = source_rect.height;
          return flipRect;
    }
    else
    {
         return source_rect;
    }

}


void AnimSpriteSheetComponent::SetFrameStartAndEnd(int startFrame, int endFrame)
{
   //sanitize input
   mFrameStart = startFrame;
   mFrameEnd = endFrame;


   if(mFrameStart == mFrameEnd)
   {
     mFrameEnd += 1;
   }
   else if(startFrame > endFrame)
   {
     mFrameStart = endFrame;
     mFrameEnd = startFrame;
   }
}

void AnimSpriteSheetComponent::UpdateRect()
{
   // get source location in sprite sheet
   int numberOfSpritesPerLine = mImageWidth / mSpriteWidth;
   int framePos = static_cast<int>(mCurrFrame);
   int startLine = static_cast<int>(framePos/ numberOfSpritesPerLine);
   int startX = static_cast<int>(framePos * mSpriteWidth) - static_cast<int>(startLine * mImageWidth);

   source_rect.width = mSpriteWidth;
   source_rect.height = mSpriteHeight;
   source_rect.left = startX;
   source_rect.top = startLine * mSpriteHeight;
}

void AnimSpriteSheetComponent::Update(sf::Time deltaTime)
{
	   SpriteComponent::Update(deltaTime);

		// Update the current frame based on frame rate
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime.asSeconds();

		// Wrap current frame if needed
		while (mCurrFrame >= mFrameEnd)
		{
			mCurrFrame -= mFrameEnd;
		}

		if(mCurrFrame > mFrameEnd)
            mCurrFrame = mFrameEnd;
        else if(mCurrFrame < mFrameStart)
            mCurrFrame = mFrameStart;

      UpdateRect();
}
