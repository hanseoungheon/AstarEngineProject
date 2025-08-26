#include "Game.h"

Game* Game::instance = nullptr;
Game::Game()
{
	instance = this;
}

Game::~Game()
{
	CleanUp();
}

void Game::ToggleMenu()
{
}

void Game::CleanUp()
{
	if(showMenu)
	{
		mainLevel = nullptr;
	}

	SafeDelete(menuLevel);
	Engine::CleanUp();
}

Game& Game::Get()
{
	return *instance;
}