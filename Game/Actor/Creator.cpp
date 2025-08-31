#include "Creator.h"
#include "Level/Level.h"
#include "Game/Game.h"
#include "Player.h"
#include "Target.h"
#include "Wall.h"
#include "Ground.h"
#include "Input.h"
#include "Interface/ICanPlayerMove.h"

Creator::Creator(Vector2& position)
	:Actor("C",Color::Yellow,position,'C')

{
	SetSortingOrder(4);
}

void Creator::BeginPlay()
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

void Creator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 입력처리!
	//어떻게? 음.. 내가 생각하는 바로는 

	if (Input::GetController().GetKeyDown('S'))
	{
		CreatePlayer();
	}

	if (Input::GetController().GetKeyDown('G'))
	{
		CreateTarget();
	}

	if (Input::GetController().GetKeyDown('W'))
	{
		CreateWall();
	}


	//입력 매핑


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

void Creator::CreatePlayer()
{
	if (GetOwner() == nullptr)
	{
		return;
	}

	for (Actor* actor : GetOwner()->actors)
	{
		Player* player = actor->As<Player>();

		if (player != nullptr)
		{
			//플레이어가 맵에 있으면 일단 삭제
			GetOwner()->DestroyActor(player);
			break;
		}

	}
	//플레이어가 맵에 없으면 생성.
	GetOwner()->AddActor(new Player(position));
}

void Creator::CreateTarget()
{
	if (GetOwner() == nullptr)
	{
		return;
	}

	for (Actor* actor : GetOwner()->actors)
	{
		Target* target = actor->As<Target>();

		if (target != nullptr)
		{
			//타겟이 맵에 있으면 일단 삭제
			GetOwner()->DestroyActor(target);
			break;
		}
	}
	//플레이어가 맵에 없으면 생성.
	GetOwner()->AddActor(new Target(position));
}

void Creator::CreateWall()
{
	if (GetOwner() == nullptr)
	{
		return;
	}

	for (Actor* actor : GetOwner()->actors)
	{
		Wall* wall = actor->As <Wall>();
		Ground* ground = actor->As<Ground>();

		if (wall != nullptr && wall->GetActorPosition() == position)
		{
			//벽을 설치하려는데 크리에이터의 위치와 벽의 위치가 똑같으면 지우고 종료.
			GetOwner()->DestroyActor(wall);
			return;
		}

		//MapGrid편집 필수.
		
		//if (ground != nullptr && (ground->GetActorPosition() == this->position))
		//{
		//	GetOwner()->DestroyActor(ground);
		//	break;
		//}
	}

	GetOwner()->AddActor(new Wall(position));
}
