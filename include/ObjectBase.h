#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include <SFML/Graphics.hpp>

class ObjectBase
{
    public:
        typedef struct
        {
            sf::Vector2f min;
            sf::Vector2f max;
        } AABB;


        ObjectBase();
        virtual ~ObjectBase();

        const sf::Vector2f GetPosition() const { return mPosition; }
        void SetPosition(const sf::Vector2f pos) { mPosition = pos; }
        sf::Vector2f GetScale() const { return mScale; }
        void SetScale(sf::Vector2f scale) { mScale = scale; }
        void SetScale(float scale) {mScale = sf::Vector2f(scale,scale);}
        float GetRotation() const { return mRotation; }
        void SetRotation(float rotation) { mRotation = rotation; }

        void SetCollisionBox(float left,float top,float width, float height);
        void SetCollisionBox(AABB collisionBox);
        float GetCollisionWidth() const {return mCollisionWidth;}
        float GetCollisionHeight() const {return mCollisionHeight;}
        bool CheckCollision(AABB& collider);
        AABB GetCollisionBox() {return mCollisionBox;}
        void DrawCollisionBox(sf::RenderWindow& window);


    protected:
        sf::Vector2f mPosition;
        sf::Vector2f mScale;
        float mRotation;
        float mCollisionWidth;
        float mCollisionHeight;
        AABB mCollisionBox;
};

#endif // OBJECTBASE_H
