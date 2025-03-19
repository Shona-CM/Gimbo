#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
    public:
        Game();
        ~Game();

        void Run();

    private:
        void ProcessEvents();
        void Update();
        void Render();

    private:
        sf::RenderWindow mWindow;
        sf::CircleShape mPlayer;

};

#endif // GAME_H
