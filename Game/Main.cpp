#include <iostream>
#include "Level/SokobanLevel.h"
#include "Game/Game.h"


int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//_CrtSetBreakAlloc(878);
	Game AstarTestingDemo;
	//std::cout << "test";
	AstarTestingDemo.Run();
	//std::cin.get();

	
}