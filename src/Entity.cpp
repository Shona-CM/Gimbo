#include "Entity.h"
#include <iostream>

Entity::Entity(Game* const game) : ObjectBase()
	, mGame(game)
{
    //ctor
}

Entity::~Entity()
{
    std::cout  <<  "clear all for Entity" <<  '\n';
    mComponents.clear();
    std::cout << "Delete Entity " << '\n';
}

void Entity::Draw(sf::RenderWindow& window)
{
  DrawComponents(window);
  DrawCollisionBox(window);
}

void Entity::DrawComponents(sf::RenderWindow& window)
{
    for(const auto& component : mComponents)
    {
       component->Draw(window);
    }
}

void Entity::AddComponent(std::unique_ptr<Component>component)
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

void Entity::RemoveComponent(std::uintptr_t id)
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


