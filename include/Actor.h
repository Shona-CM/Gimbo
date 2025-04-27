#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <memory>

#include "Game.h"
#include "Component.h"
#include <cstdint>

#include "ObjectBase.h"

class Actor : public ObjectBase
{
    public:

        enum State
        {
            Active,
            Paused,
            Dead
        };

        Actor(Game* const game);
        virtual ~Actor();

        void Update(sf::Time deltaTime);
        void UpdateComponents(sf::Time deltaTime);
        virtual void UpdateActor(sf::Time deltaTime);
        void UpdateMovement(ObjectBase::MovementActions actions,sf::Time deltaTime);
        void Draw(sf::RenderWindow& window);
        void DrawComponents(sf::RenderWindow& window);

        void SetIsJumping(bool isJumping) {mIsJumping = isJumping;}
        bool GetIsJumping() const {return mIsJumping;}
        class Entity* CheckPlayerGrounded();

        State GetState() const { return mState; }
        void SetState(State state) { mState = state;}

        void AddComponent(std::unique_ptr<Component> component);
        void RemoveComponent(std::uintptr_t);

        Game* GetGame() {return mGame;}

    private:
        bool mIsJumping;
        bool mIsFalling;
        float mWalkingSpeed;
        float mJumpSpeed;
        float mJumpStartHeight;
        State mState;
	    Game* const mGame;   // do not manually delete !!!

	   std::vector<std::unique_ptr<Component>> mComponents;

};

#endif // ACTOR_H
