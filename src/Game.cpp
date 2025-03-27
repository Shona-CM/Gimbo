#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "AnimSpriteSheetComponent.h"
#include <iostream>
#include <fstream>
#include <sstream>

Game::Game() : mTicksCount(0)
    ,mIsRunning(true)
    ,mTimePerFrame(sf::seconds(1.0f / 60.0f))
    ,mUpdatingActors(false)
    ,mIsMovingUp(false)
    ,mIsMovingDown(false)
    ,mIsMovingLeft(false)
    ,mIsMovingRight(false)
{
    //ctor
}

Game::~Game()
{
   std::cout << "Pending clear " << '\n';
   mPendingActors.clear();
   std::cout << "Actors clear " << '\n';
   mActors.clear();
   std::cout << "Delete Game " << '\n';
     //dtor
}
bool Game::Initialize()
{
    std::string title = "Neptune Game Engine";
    mWindow =  std::make_shared<sf::RenderWindow>(sf::VideoMode(800,600), title);

    mCircle.setFillColor(sf::Color::Yellow);
    mCircle.setRadius(40.0);
    mCircle.setPosition(100.0f,100.0f);

    LoadData();

    return true;
}

void Game::LoadData()
{
    GetFileTextures("./ImagePaths");

    std::unique_ptr<Actor> temp = std::make_unique<Actor>(this);
	temp->SetPosition(sf::Vector2f(400.0f, 384.0f));

	std::unique_ptr<AnimSpriteComponent> component = std::make_unique<AnimSpriteComponent>(temp.get(),100);
	component->SetAnimSprites(&mTextureMapper,"ship",4);
	component->SetFrameStartAndEnd(0,4);
    temp->AddComponent(std::move(component));
    //do all work on actor before moving
	AddActor(std::move(temp));



   /* std::unique_ptr<Actor> enemy = std::make_unique<Actor>(this);
	enemy->SetPosition(sf::Vector2f(256.0f, 384.0f));

	std::unique_ptr<AnimSpriteComponent> component2 = std::make_unique<AnimSpriteComponent>(enemy.get(),100);
	component2->SetAnimSprites(&mTextureMapper,"eship",6);
	component2->SetFrameStartAndEnd(0,6);
    enemy->AddComponent(std::move(component2));
    //do all work on actor before moving
	AddActor(std::move(enemy));*/


    std::unique_ptr<Actor> person = std::make_unique<Actor>(this);
	person->SetPosition(sf::Vector2f(100.0f, 100.0f));
	person->SetState(Actor::Active);

	std::unique_ptr<AnimSpriteSheetComponent> component3 = std::make_unique<AnimSpriteSheetComponent>(person.get(),100);
	component3->SetupSprite(&mTextureMapper,"per1");
	component3->SetFrameStartAndEnd(8,12);
	component3->SetImageWidth(256);
	component3->SetImageHeight(256);
	component3->SetSpriteWidth(64);
	component3->SetSpriteHeight(64);
	component3->SetAnimFPS(5);
    person->AddComponent(std::move(component3));

    AddActor(std::move(person));

    std::unique_ptr<Actor> platform1 = std::make_unique<Actor>(this);
    platform1->SetStatic(true);
    std::unique_ptr<SpriteComponent> platform1Sprite = std::make_unique<SpriteComponent>(platform1.get(),50);
    platform1Sprite->SetupSprite(&mTextureMapper,"plat1");
    platform1->AddComponent(std::move(platform1Sprite));
	platform1->SetPosition(sf::Vector2f(300.0f, 500.0f));
    AddActor(std::move(platform1));
}

void Game::GetFileTextures(std::string filePath )
{
    std::string delimiter = "#=";
    std::ifstream file;
    file.open(filePath);
    std::vector<std::string> paths;
    if (file.is_open())
    {
        std::string line;
        // Read data from the file object and put it into a string.
        while (getline(file, line))
        {
           if(line == "")
             continue;

           std::string token = line.substr(0, line.find(delimiter));
           std::string data = line.substr(line.find(delimiter) + 2);

           mTextureMapper.Load(token,data);
        }

        // Close the file object.
        file.close();
     }
     else
     {
         std::cout << "Could not open file  " <<  filePath << '\n';
     }
}


void Game::Run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while(mIsRunning)
  {
     ProcessInput();
     timeSinceLastUpdate += clock.restart();

     while(timeSinceLastUpdate > mTimePerFrame)
     {
        timeSinceLastUpdate -= mTimePerFrame;
        UpdateGame(mTimePerFrame);
     }

     GenerateOutput();
  }
}

void Game::UpdateGame(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f,0.f);
    auto speed = 5.f * 60.f;   //5 pixels per second
    speed *= deltaTime.asSeconds();

    //std::cout << deltaTime.asSeconds() << '\n';

    if(mIsMovingUp)
        movement.y -= speed;
    if(mIsMovingDown)
        movement.y += speed;
    if(mIsMovingLeft)
        movement.x -= speed;
    if(mIsMovingRight)
        movement.x += speed;

    mCircle.move(movement);

    auto currentPos = mCircle.getPosition();

    if(currentPos.x < 0.f)
        mCircle.setPosition(0.f,currentPos.y);

    if(currentPos.x > 720.f)
        mCircle.setPosition(720.f,currentPos.y);

    if(currentPos.y < 0.f)
        mCircle.setPosition(currentPos.x,0.f);

    if(currentPos.y > 520.f)
        mCircle.setPosition(currentPos.x,520.f);

    for (const auto& actor : mActors)
	{
	    if(actor->GetStatic() == false)
	    {
            auto currentPos = actor->GetPosition();
            currentPos.x += movement.x;
            currentPos.y += movement.y;
            actor->SetPosition(currentPos);
	    }
	}

    UpdateActors(deltaTime);
}

void Game::UpdateActors(sf::Time deltaTime)
{
    // Update all actors
	mUpdatingActors = true;
	for (const auto& actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// Move any pending actors to mActors
    mActors.insert(mActors.end(), make_move_iterator(mPendingActors.begin()), make_move_iterator(mPendingActors.end()));
    mPendingActors.clear();

	 // Remove any dead actors remove
     for (auto&& it = mActors.begin(); it != mActors.end(); it++)
     {
        if(it->get()->GetState() == Actor::Dead)
            mActors.erase(it--);
     }
}

void Game::ProcessInput()
{
  sf::Event event;

  while(mWindow->pollEvent(event))
  {
     switch(event.type)
     {
        case sf::Event::KeyPressed :
            TranslateInput(event.key.code,true);
            break;
        case sf::Event::KeyReleased :
            TranslateInput(event.key.code,false);
            break;
        case sf::Event::Closed :
            mIsRunning = false;
            break;
     }
  }
}

void Game::TranslateInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if(key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if(key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if(key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

void Game::GenerateOutput()
{
   mWindow->clear(sf::Color::Blue);

   mWindow->draw(mCircle);

   for(const auto& actor : mActors)
   {
        actor->Draw(*mWindow);
   }

   mWindow->display();
}

void Game::Shutdown()
{

}

void Game::AddActor(std::unique_ptr<Actor> actor)
{
     std::cout << "Adding Actor "  <<  '\n';
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(std::move(actor));
	}
	else
	{
		mActors.emplace_back(std::move(actor));
	}
}
