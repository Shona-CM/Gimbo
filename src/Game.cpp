#include "Game.h"

Game::Game()
    :mWindow(sf::VideoMode(640,480),"SFML Game Development"),
     mPlayer()
{
    mPlayer.setRadius(40.0f);
    mPlayer.setPosition(100.0f,100.0f);
    mPlayer.setFillColor(sf::Color::Blue);
}

Game::~Game()
{
    //dtor
}

void Game::Run()
{

    while(mWindow.isOpen())
    {
        ProcessEvents();
        Update();
        Render();
    }

}

void Game::ProcessEvents()
{
    sf::Event event;

    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();
    }

}

void Game::Update()
{

}

void Game::Render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();

}
