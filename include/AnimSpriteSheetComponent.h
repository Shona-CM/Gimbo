#ifndef ANIMSPRITESHEETCOMPONENT_H
#define ANIMSPRITESHEETCOMPONENT_H

#include "SpriteComponent.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "TextureMapper.h"
#include "Actor.h"

class AnimSpriteSheetComponent : public SpriteComponent
{
    public:
        AnimSpriteSheetComponent(class Actor* owner, int drawOrder);
        virtual ~AnimSpriteSheetComponent();

        void Draw(sf::RenderWindow& window) override;
        virtual void Update(sf::Time deltaTime);
	    void UpdateRect();

	    float GetAnimFPS() const { return mAnimFPS; }
	    void SetAnimFPS(float fps) { mAnimFPS = fps; }
	    void SetFrameStartAndEnd(int startFrame, int endFrame);
	    void SetImageWidth(int width) {mImageWidth = width;}
	    void SetImageHeight(int Height) {mImageHeight = Height;}
	    void SetSpriteWidth(int width) {mSpriteWidth = width;}
	    void SetSpriteHeight(int height) {mSpriteHeight = height;}

    protected:
         sf::IntRect FlipSpriteHorizontal(bool flip);

    private:
        float mCurrFrame;
        float mAnimFPS;
        int mFrameStart;
        int mFrameEnd;
        int mImageWidth;
        int mImageHeight;
        sf::IntRect source_rect;
};

#endif // ANIMSPRITESHEETCOMPONENT_H
