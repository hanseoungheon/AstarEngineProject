#include "Game.h"
#include "Level/SokobanLevel.h"
#include "Level/TestDemoLevel.h"

//Game* Game::instance = nullptr;
Game::Game()
{
	instance = this;
	AddLevel(new SokobanLevel());
	//AddLevel(new TestDemoLevel());
}

//Game::~Game()
//{
//	CleanUp();
//}

//void Game::ToggleMenu()
//{
//}
//
//void Game::CleanUp()
//{
//	if(showMenu)
//	{
//		mainLevel = nullptr;
//	}
//
//	SafeDelete(menuLevel);
//	Engine::CleanUp();
//}
//
//Game& Game::Get()
//{
//	return *instance;
//}