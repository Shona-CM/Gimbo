#include "ObjectBase.h"
#include <iostream>

ObjectBase::ObjectBase()
	: mPosition(sf::Vector2(0.f,0.f))
	, mScale(sf::Vector2f(1.0f,1.0f))
	, mRotation(0.0f)
	, mCollisionWidth(0.0f)
	, mCollisionHeight(0.0f)
	, mName("")
	, mGroup("")
{
    //ctor
}

ObjectBase::~ObjectBase()
{
    std::cout << "Delete Object Base" << '\n';
}

void ObjectBase::SetCollisionBox(float left,float top,float width, float height)
{
   mCollisionBox.min.x = left;
   mCollisionBox.min.y = top;
   mCollisionWidth = width;
   mCollisionHeight = height;
   mCollisionBox.max.x = left + mCollisionWidth;
   mCollisionBox.max.y = top + mCollisionHeight;
}

void ObjectBase::SetCollisionBox(AABB collisionBox)
{
   mCollisionBox.min = collisionBox.min;
   mCollisionBox.max = collisionBox.max;
}


bool ObjectBase::CheckCollision(AABB& collider)
{
    float d1x = collider.min.x - mCollisionBox.max.x;
    float d1y = collider.min.y - mCollisionBox.max.y;
    float d2x = mCollisionBox.min.x - collider.max.x;
    float d2y = mCollisionBox.min.y - collider.max.y;

    if (d1x > 0.0f || d1y > 0.0f)
        return false;

    if (d2x > 0.0f || d2y > 0.0f)
        return false;

    return true;
}


void ObjectBase::DrawCollisionBox(sf::RenderWindow& window)
{
    AABB  box = GetCollisionBox();

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(box.min.x, box.min.y)),
        sf::Vertex(sf::Vector2f(box.max.x, box.min.y)),
        sf::Vertex(sf::Vector2f(box.max.x, box.min.y)),
        sf::Vertex(sf::Vector2f(box.max.x, box.max.y)),
        sf::Vertex(sf::Vector2f(box.max.x, box.max.y)),
        sf::Vertex(sf::Vector2f(box.min.x, box.max.y)),
        sf::Vertex(sf::Vector2f(box.min.x, box.max.y)),
        sf::Vertex(sf::Vector2f(box.min.x, box.min.y))
    };

    window.draw(line, 8, sf::Lines);
}

