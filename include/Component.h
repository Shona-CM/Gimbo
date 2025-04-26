#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>
#include <cstdint>


class Component
{
    public:
        Component(class ObjectBase* const owner, int updateOrder = 100);
        virtual ~Component();

        virtual void Draw(sf::RenderWindow& window);
        virtual void Update(sf::Time deltaTime);
	    int GetUpdateOrder() const { return mUpdateOrder; }
        std::uintptr_t GetId() const {return mId;}

    protected:
        class ObjectBase* const mOwner;
        int mUpdateOrder;
        std::uintptr_t  mId;
};

#endif // COMPONENT_H
