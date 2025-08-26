#include "Level.h"
#include "Actor/Actor.h"
#include "Utils/Utils.h"
#include <iostream>

Level::Level()
{

}

Level::~Level()
{
	for (Actor* actor : actors)
	{
		SafeDelete(actor);
	}

	actors.clear();
}

void Level::BeginPlay()
{
	for (Actor* actor : actors)
	{
		//���� ��û�� �����ų� Ȱ��ȭ�� �ȵ� ������ ���ʹ� �ǳʶ�
		if (actor->isActive == false || actor->isExpired == true)
		{
			continue;
		}

		//�̹� ȣ���� �� ��ü�� �ǳʶٱ�.
		if (actor->HasBeginPlay() == true)
		{
			continue;
		}

		//���� �����Ű��.
		actor->BeginPlay();
	}
}

void Level::Tick(float DeltaTime)
{
	for (Actor* actor : actors)
	{
		if (actor->isActive == false || actor->isExpired == true)
		{
			continue;
		}

		actor->Tick(DeltaTime);
	}

}

void Level::Render()
{
	SortActorsBySortingOrder();

	for (Actor* actor : actors)
	{
		if (actor->isActive == false || actor->isExpired == true)
			continue;

		Actor* searchedActor = nullptr;

		//�˻� -> ���� ��ġ�� ���� ���� ���� ���Ͱ� �ִ��� Ȯ���ϱ�.
		for (Actor* const otherActor : actors)
		{
			if (actor == otherActor)
			{
				continue;
			}

			if (actor->GetActorPosition() == otherActor->GetActorPosition())
			{
				//���� ���� �� �� �� ���� ���Ͱ� �����.
				if (actor->sortingOrder < otherActor->sortingOrder)
				{
					searchedActor = otherActor;
					break;
				}
			}
		}

		//� ���Ϳ� ���� ��ġ�� ���� ������ �� ���� ���Ͱ� ������, �׷��� �ʰ� �ǳʶٱ�.
		if (searchedActor != nullptr)
		{
			continue;
		}

		actor->Render();

	}
}

void Level::AddActor(Actor* newActor)
{
	addRequestedActors.emplace_back(newActor);
}

void Level::DestroyActor(Actor* destroyedActor)
{
	destroyRequsetedActors.emplace_back(destroyedActor);
}

void Level::ProcessAddAndDestroyActors()
{
	for (auto iterator = actors.begin(); iterator != actors.end();)
	{
		//���� ��û�� ���� Ȯ�� �� �迭���� ���ܽ�Ű�� �Լ�.
		//�����͸� ����Ű�� �����Ͱ� �ٷ� ���ͷ����� (*iterator = Actor*)
		if ((*iterator)->isExpired)
		{
			iterator = actors.erase(iterator);
			continue;
		}

		++iterator;
	}

	//�迭�� ��ȸ�ϸ鼭 ���� �����.
	for (auto* actor : destroyRequsetedActors)
	{
		Utils::SetConsolePosition(actor->position);

		for (int i = 0; i < actor->width; ++i)
		{
			std::cout << " ";
		}

		SafeDelete(actor);
	}

	//�迭 �ʱ�ȭ
	destroyRequsetedActors.clear();

	for (Actor* const actor : addRequestedActors)
	{
		actors.emplace_back(actor);
		actor->SetOwner(this);
	}

	//�迭 �ʱ�ȭ.
	addRequestedActors.clear();
}

void Level::SortActorsBySortingOrder()
{
	for (int ix = 0; ix < (int)actors.size(); ix++)
	{
		for (int jx = 0; jx < (int)actors.size(); ++jx)
		{
			if (actors[jx]->sortingOrder < actors[jx + 1]->sortingOrder)
				std::swap(actors[jx], actors[jx + 1]);
		}
	}
}

