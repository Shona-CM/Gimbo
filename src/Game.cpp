#include "Game.h"
#include "Actor.h"
#include "Entity.h"
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

    LoadData();

    return true;
}

void Game::LoadData()
{
    GetFileTextures("./ImagePaths");

    //test AnimSprites - single frames of animation
    /*std::unique_ptr<Actor> ship = std::make_unique<Actor>(this);
	ship->SetPosition(sf::Vector2f(400.0f, 384.0f));
	ship->SetName("Ship");
	ship->SetGroup("Coin");

	std::unique_ptr<AnimSpriteComponent> component = std::make_unique<AnimSpriteComponent>(ship.get(),100);
	component->SetAnimSprites(&mTextureMapper,"ship",4);
	component->SetFrameStartAndEnd(0,4);
	ship->SetCollisionBox(400.0f, 384.0f,component->GetSpriteWidth(),component->GetSpriteHeight());
    ship->AddComponent(std::move(component));
    //do all work on actor before moving
	AddActor(std::move(ship));*/

    //Test player as a sprite sheet
    std::unique_ptr<Actor> person = std::make_unique<Actor>(this);
    sf::Vector2f location = {350.0f,100.0f};
	person->SetPosition(location);
	person->SetState(Actor::Active);
	person->SetCollisionBox(location.x,location.y,64,60);
	person->SetName("Player");
	person->SetGroup("Player");

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

    //Add Static objects as platforms
    std::unique_ptr<Entity> platform1 = std::make_unique<Entity>(this);
    std::unique_ptr<SpriteComponent> platform1Sprite = std::make_unique<SpriteComponent>(platform1.get(),50);
    platform1Sprite->SetupSprite(&mTextureMapper,"plat1");

    double spriteWidth = platform1Sprite->GetSpriteWidth();
    double spriteHeight = platform1Sprite->GetSpriteHeight();
    sf::Vector2f position = {300.0f,300.0f};

    platform1->SetCollisionBox(position.x,position.y,spriteWidth,spriteHeight);
    platform1->AddComponent(std::move(platform1Sprite));
	platform1->SetPosition(sf::Vector2f(position.x,position.y));
	platform1->SetGroup("Platform");
    AddEntity(std::move(platform1));

    std::unique_ptr<Entity> platform2 = std::make_unique<Entity>(this);
    sf::Vector2f position2 = {0.0f,590.0f};
    platform2->SetCollisionBox(position2.x,position2.y,800.0f,10.0f);
    platform2->SetPosition(sf::Vector2f(position2.x,position2.y));
	platform2->SetGroup("Platform");
    AddEntity(std::move(platform2));

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

void Game::UpdateGame(sf::Time deltaTime)
{

    for (const auto& actor : mActors)
	{
        ObjectBase::MovementActions actions = {mIsMovingLeft,mIsMovingRight,mIsMovingUp};
        actor->UpdateMovement(actions,deltaTime);
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



void Game::TranslateInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::Space)
        mIsMovingUp = isPressed;
    else if(key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if(key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

void Game::GenerateOutput()
{
   mWindow->clear(sf::Color::Blue);

   for(const auto& entity : mEntities)
   {
        entity->Draw(*mWindow);
   }

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

void Game::AddEntity(std::unique_ptr<Entity> entity)
{
     std::cout << "Adding Entity"  <<  '\n';
     mEntities.emplace_back(std::move(entity));
}
