#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <memory>

#include "Game.h"
#include "Component.h"
#include <cstdint>


class Actor
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

        const sf::Vector2f GetPosition() const { return mPosition; }
        void SetPosition(const sf::Vector2f pos) { mPosition = pos; }
        sf::Vector2f GetScale() const { return mScale; }
        void SetScale(sf::Vector2f scale) { mScale = scale; }
        void SetScale(float scale) {mScale = sf::Vector2f(scale,scale);}
        float GetRotation() const { return mRotation; }
        void SetRotation(float rotation) { mRotation = rotation; }

        State GetState() const { return mState; }
        void SetState(State state) { mState = state;}

        void SetStatic(bool isStatic) {mStatic = isStatic;}
        bool GetStatic() {return mStatic;}

        void AddComponent(std::unique_ptr<Component> component);
        void RemoveComponent(std::uintptr_t);

        Game* GetGame() {return mGame;}

    private:
        State mState;
        sf::Vector2f mPosition;
        sf::Vector2f mScale;
        float mRotation;
        bool mStatic;
	    Game* const mGame;   // do not manually delete !!!

	   std::vector<std::unique_ptr<Component>> mComponents;

};

#endif // ACTOR_H
