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

	//�������̽� ������.
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
	// �Է�ó��!
	//���? ��.. ���� �����ϴ� �ٷδ� 

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


	//�Է� ����


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
			//�÷��̾ �ʿ� ������ �ϴ� ����
			GetOwner()->DestroyActor(player);
			break;
		}

	}
	//�÷��̾ �ʿ� ������ ����.
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
			//Ÿ���� �ʿ� ������ �ϴ� ����
			GetOwner()->DestroyActor(target);
			break;
		}
	}
	//�÷��̾ �ʿ� ������ ����.
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
			//���� ��ġ�Ϸ��µ� ũ���������� ��ġ�� ���� ��ġ�� �Ȱ����� ����� ����.
			GetOwner()->DestroyActor(wall);
			return;
		}

		//MapGrid���� �ʼ�.
		
		//if (ground != nullptr && (ground->GetActorPosition() == this->position))
		//{
		//	GetOwner()->DestroyActor(ground);
		//	break;
		//}
	}

	GetOwner()->AddActor(new Wall(position));
}
