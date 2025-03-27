#include "Actor.h"
#include <iostream>
#include <bits/stdc++.h>

Actor::Actor(Game* const game):mState(Active)
	, mPosition(sf::Vector2(0.f,0.f))
	, mScale(sf::Vector2f(1.0f,1.0f))
	, mRotation(0.0f)
	, mStatic(false)
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
