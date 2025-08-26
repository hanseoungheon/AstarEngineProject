#include "Player.h"
#include "Engine.h"
#include "Game/Game.h"
#include "Input.h"
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"
#include <iostream>

Player::Player(const Vector2& position)
	:Actor("P", Color::Red, position)
{
	SetSortingOrder(3);
}

void Player::BeginPlay()
{
	Super::BeginPlay();

	//인터페이스 얻어오기.
	if (GetOwner() != nullptr)
	{
		canPlayerMoveInterface
			= dynamic_cast<ICanPlayerMove*>(GetOwner());

		if (canPlayerMoveInterface == nullptr)
		{
			std::cout << "Can not cast Owner Level to ICanPlayerMove.\n";
		}
	}
}

void Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().Quit();
		return;
	}


}
