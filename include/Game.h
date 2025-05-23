#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "TextureMapper.h"

class Game
{
  public:
    Game();
    ~Game();

    bool Initialize();
	void Run();
	void Shutdown();

	std::vector<std::unique_ptr<class Entity>> const& GetEntities() { return mEntities;}

  private:
    void ProcessInput();
	void UpdateGame(sf::Time deltaTime);
	void UpdateActors(sf::Time deltaTime);
	void GenerateOutput();
	void TranslateInput(sf::Keyboard::Key key, bool isPressed);

	void AddActor(std::unique_ptr<class Actor> actor);
	void AddEntity(std::unique_ptr<class Entity> entity);
	bool IsEqual(const std::unique_ptr<Actor>& obj,std::uintptr_t & id);

	const sf::RenderWindow* GetWindow() {return mWindow.get();}
	void LoadData();
	void GetFileTextures(std::string);

	uint32_t mTicksCount;
	bool mIsRunning;
	sf::Time mTimePerFrame;
	bool mUpdatingActors;

	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;
    TextureMapper mTextureMapper;

    std::shared_ptr<sf::RenderWindow> mWindow;
    //Actors all moving  objects
    std::vector<std::unique_ptr<class Actor>> mActors;
	std::vector<std::unique_ptr<class Actor>> mPendingActors;

	//Entities all non moving objects such as platforms
	std::vector<std::unique_ptr<class Entity>> mEntities;
};

#endif // GAME_H
