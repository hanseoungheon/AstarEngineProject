#include "Player.h"
#include "Engine.h"
#include "Game/Game.h"
#include "Input.h"
#include "Level/Level.h"
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
}

void Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (Input::Get().GetKeyDown(VK_ESCAPE))
	//{
	//	Game::GetController().Quit();
	//	return;
	//}


}
