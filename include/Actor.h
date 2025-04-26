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
        void Draw(sf::RenderWindow& window);
        void DrawComponents(sf::RenderWindow& window);

        State GetState() const { return mState; }
        void SetState(State state) { mState = state;}

        void AddComponent(std::unique_ptr<Component> component);
        void RemoveComponent(std::uintptr_t);

        Game* GetGame() {return mGame;}

    private:
        State mState;
	    Game* const mGame;   // do not manually delete !!!

	   std::vector<std::unique_ptr<Component>> mComponents;

};

#endif // ACTOR_H
