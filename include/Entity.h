#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <memory>
#include <cstdint>

#include "Game.h"
#include "Component.h"
#include "ObjectBase.h"


class Entity : public ObjectBase
{
    public:
        Entity(Game* const game);
        virtual ~Entity();

        void Draw(sf::RenderWindow& window);
        void DrawComponents(sf::RenderWindow& window);

        void AddComponent(std::unique_ptr<Component> component);
        void RemoveComponent(std::uintptr_t);

        Game* GetGame() {return mGame;}

    private:
	    Game* const mGame;   // do not manually delete !!!

	   std::vector<std::unique_ptr<Component>> mComponents;
};

#endif // ENTITY_H
