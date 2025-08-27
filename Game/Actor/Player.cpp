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
	if (GetOwner())
	{
		canPlayerMoveInterface =
			dynamic_cast<ICanPlayerMove*>(GetOwner());

		if (!canPlayerMoveInterface)
		{
			std::cout << "Can not cast owener level to ICanPlayerMove.\n";
		}
	}
}

void Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Input::GetController().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().Quit();
		return;
	}

	if (Input::GetController().GetKeyDown(VK_LEFT))
	{
		if (canPlayerMoveInterface->CanPlayerMove(GetActorPosition(),
			Vector2(GetActorPosition().x - 1, GetActorPosition().y)))
		{
			Vector2 currentPosition = GetActorPosition();
			currentPosition.x -= 1;
			SetActorPosition(currentPosition);
		}
	}

	if (Input::GetController().GetKeyDown(VK_RIGHT))
	{
		if (canPlayerMoveInterface->CanPlayerMove(GetActorPosition(),
			Vector2(GetActorPosition().x + 1, GetActorPosition().y)))
		{
			Vector2 currentPosition = GetActorPosition();
			currentPosition.x += 1;
			SetActorPosition(currentPosition);
		}
	}

	if (Input::GetController().GetKeyDown(VK_UP))
	{
		if (canPlayerMoveInterface->CanPlayerMove(GetActorPosition(),
			Vector2(GetActorPosition().x, GetActorPosition().y - 1)))
		{
			Vector2 currentPosition = GetActorPosition();
			currentPosition.y -= 1;
			SetActorPosition(currentPosition);
		}
	}

	if (Input::GetController().GetKeyDown(VK_DOWN))
	{
		if (canPlayerMoveInterface->CanPlayerMove(GetActorPosition(),
			Vector2(GetActorPosition().x, GetActorPosition().y + 1)))
		{
			Vector2 currentPosition = GetActorPosition();
			currentPosition.y += 1;
			SetActorPosition(currentPosition);
		}
	}

}
