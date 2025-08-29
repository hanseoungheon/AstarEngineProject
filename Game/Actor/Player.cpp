#include "Player.h"
#include "Engine.h"
#include "Game/Game.h"
#include "Input.h"
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"
#include <iostream>

Player::Player(const Vector2& position)
	:Actor("P", Color::Red, position,'P')
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

	//if (Input::GetController().GetKeyDown(VK_RETURN))
	//{
	//	//IsTrigged는 static 변수입니다.
	//	IsTrigged = !IsTrigged;
	//}

	
	if (Input::GetController().GetKeyDown(VK_LEFT) && GetOwner()->GetLevelTrigget() == false)
	{
		if (canPlayerMoveInterface->CanPlayerMove(GetActorPosition(),
			Vector2(GetActorPosition().x - 1, GetActorPosition().y)))
		{
			Vector2 currentPosition = GetActorPosition();
			currentPosition.x -= 1;
			SetActorPosition(currentPosition);
		}
	}

	if (Input::GetController().GetKeyDown(VK_RIGHT) && GetOwner()->GetLevelTrigget() == false)
	{
		if (canPlayerMoveInterface->CanPlayerMove(GetActorPosition(),
			Vector2(GetActorPosition().x + 1, GetActorPosition().y)))
		{
			Vector2 currentPosition = GetActorPosition();
			currentPosition.x += 1;
			SetActorPosition(currentPosition);
		}
	}

	if (Input::GetController().GetKeyDown(VK_UP) && GetOwner()->GetLevelTrigget() == false)
	{
		if (canPlayerMoveInterface->CanPlayerMove(GetActorPosition(),
			Vector2(GetActorPosition().x, GetActorPosition().y - 1)))
		{
			Vector2 currentPosition = GetActorPosition();
			currentPosition.y -= 1;
			SetActorPosition(currentPosition);
		}
	}

	if (Input::GetController().GetKeyDown(VK_DOWN) && GetOwner()->GetLevelTrigget() == false)
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
