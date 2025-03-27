#include <SFML/Graphics.hpp>

#include "Game.h"
#include "iostream"

int main()
{
    Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.Run();
	}
	game.Shutdown();

	std::cout << "Exit Main." << '\n';
}
