#include <iostream>
#include "Level/SokobanLevel.h"
#include "Game/Game.h"


int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(927);
	Game AstarTestingDemo;
	//std::cout << "test";
	AstarTestingDemo.Run();


	//std::cin.get();

	//Todo: 이제 남은거? 경로 찍고 나서 초기화해보기!
	//초기화를 위해 필요한 과정?
	//프론트엔드-> 표시된 경로 초기화하기.
	//백엔드-> 노드 초기화하기.
}