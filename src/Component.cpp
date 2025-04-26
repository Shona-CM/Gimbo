#include "Component.h"
#include "ObjectBase.h"
#include <iostream>

Component::Component(ObjectBase* const owner, int updateOrder)
    :mOwner(owner)
	,mUpdateOrder(updateOrder)
{

    //mId = reinterpret_cast<std::uintptr_t>(this);
    std::cout << "Create Component" << '\n';
}

Component::~Component()
{
     std::cout << "Delete Component" << '\n';
}

void Component::Update(sf::Time deltaTime)
{

}

void Component::Draw(sf::RenderWindow& window)
{

}
