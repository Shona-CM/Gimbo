#include "Actor.h"
#include "Entity.h"
#include <iostream>
#include <bits/stdc++.h>

Actor::Actor(Game* const game) : ObjectBase()
    , mIsJumping(false)
    , mIsFalling(false)
    , mWalkingSpeed(5.0f * 60.0f)  //5 pixels per second
    , mJumpSpeed(120.0f * 60.0f)
    , mJumpStartHeight(0.0)
    , mState(Active)
	, mGame(game)
{
}

Actor::~Actor()
{
    std::cout  <<  "clear all " <<  '\n';
    mComponents.clear();
    std::cout << "Delete Actor " << '\n';
}


void Actor::Update(sf::Time deltaTime)
{
    UpdateComponents(deltaTime);
}

void Actor::UpdateComponents(sf::Time deltaTime)
{
    for(const auto& component : mComponents)
    {
       component->Update(deltaTime);
    }
}

void Actor::UpdateActor(sf::Time deltaTime)
{
}

void Actor::Draw(sf::RenderWindow& window)
{
  DrawComponents(window);
  DrawCollisionBox(window);
}

void Actor::DrawComponents(sf::RenderWindow& window)
{
    for(const auto& component : mComponents)
    {
       component->Draw(window);
    }
}

void Actor::AddComponent(std::unique_ptr<Component>component)
{
    // Find the insertion point in the sorted vector
    // (The first element with a order higher than me)
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (;iter != mComponents.end();++iter)
    {
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }

    // Inserts element before position of iterator
    mComponents.insert(iter,std::move(component));

    std::cout << "Number  of components " << mComponents.size() << '\n';
}

void Actor::RemoveComponent(std::uintptr_t id)
{
    auto iter = mComponents.begin();
	for (;iter != mComponents.end();++iter)
    {
        if(id == (*iter)->GetId())
            break;
    }

	if (iter != mComponents.end())
	{
	   std::cout << " erase component  " <<  id << '\n';
       mComponents.erase(iter);
	}
}

void Actor::UpdateMovement(ObjectBase::MovementActions actions,sf::Time deltaTime)
{
    sf::Vector2f velocity(0.f,0.f);
    float gravity = 3.0f;
    float jumpToFallingDistance = 5.0f;  // the distance of a fall in the jump that indicates the player has jumped off a platform

    if(GetGroup() == "Player")
    {
        Entity* entity = CheckPlayerGrounded();

        if(entity == nullptr)
        {
            velocity.y += gravity + deltaTime.asSeconds();

            if(mIsJumping == false)
                mIsFalling = true;
            else if(mPosition.y > mJumpStartHeight + jumpToFallingDistance)
                mIsFalling = true;
        }
        else
        {
            ObjectBase::AABB entityBox = entity->GetCollisionBox();
            float diffY = entityBox.min.y -mCollisionBox.max.y;
            velocity.y += diffY;
        }

        if(velocity.y == 0)
        {
            mIsJumping = false;
            mIsFalling = false;
            mJumpStartHeight = 0.0f;
        }


        if (mIsJumping == false && actions.JumpPressed)
        {
            velocity.y -=  mJumpSpeed* deltaTime.asSeconds();
            mIsJumping = true;
            mJumpStartHeight = mPosition.y;
        }
    }

    auto speed = mWalkingSpeed * deltaTime.asSeconds();

    if(mIsFalling == false)
    {
        if(actions.LeftPressed)
            velocity.x -= speed;
        if(actions.RightPressed)
            velocity.x += speed;
    }

    mPosition.x += velocity.x;
    mPosition.y += velocity.y;
    SetCollisionBox(mPosition.x,mPosition.y,mCollisionWidth,mCollisionHeight);
}

Entity* Actor::CheckPlayerGrounded()
{
    Entity* collidingEntity = nullptr;

    for (const auto& entity : mGame->GetEntities())
	{
		 ObjectBase::AABB box = entity->GetCollisionBox();

		 if(CheckCollision(box) == true)
		 {
            collidingEntity = entity.get();
            break;
		 }
	}

	return collidingEntity;
}

