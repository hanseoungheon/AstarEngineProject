#include "Level.h"
#include "Actor/Actor.h"
#include "Actor/UI.h"
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

	for (Actor* actor : tempActor)
	{
		SafeDelete(actor);
	}

	tempActor.clear();
	for (UI* UI_InLevel : ui_inLevel)
	{
		SafeDelete(UI_InLevel);
	}
	ui_inLevel.clear();

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
		if (actor->HasBeganPlay() == true)
		{
			continue;
		}

		//���� �����Ű��.
		actor->BeginPlay();
	}

	for (UI* UI_InLevel : ui_inLevel)
	{
		if (UI_InLevel->isActiveUI == false || UI_InLevel->isExpiredUI == true)
		{
			continue;
		}

		if (UI_InLevel->HasBeganPlay() == true)
		{
			continue;
		}

		UI_InLevel->BeginPlay();
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

	for (UI* UI_InLevel : ui_inLevel)
	{
		if (UI_InLevel->isActiveUI == false || UI_InLevel->isExpiredUI == true)
		{
			continue;
		}

		UI_InLevel->Tick(DeltaTime);
	}

}

void Level::Render()
{
	SortActorsBySortingOrder();

	for (Actor* const actor : actors)
	{
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

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

	for (UI* const UI_InLevel : ui_inLevel)
	{
		if (UI_InLevel->isActiveUI == false || UI_InLevel->isExpiredUI == true)
		{
			continue;
		}

		UI* searchedUI = nullptr;

		//UI�� ���ļ����� �Ű澲�� ����.
		//for (UI* const otherUI : ui_inLevel)
		//{

		//}

		UI_InLevel->Render();
	}
}

void Level::AddActor(Actor* newActor)
{
	addRequestedActors.emplace_back(newActor);
	tempActor.emplace_back(newActor);
	//newActor->SetOwner(this);
}
void Level::DestroyActor(Actor* destroyedActor)
{
	destroyRequstedActors.emplace_back(destroyedActor);
}

void Level::AddUI(UI* newUI)
{
	addRequestedUI.emplace_back(newUI);
}

void Level::DestroyUI(UI* destroyedUI)
{
	destroyRequestedUI.emplace_back(destroyedUI);
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
	for (auto* actor : destroyRequstedActors)
	{
		Utils::SetConsolePosition(actor->position);

		for (int i = 0; i < actor->width; ++i)
		{
			std::cout << " ";
		}

		SafeDelete(actor);
	}

	//�迭 �ʱ�ȭ
	destroyRequstedActors.clear();

	for (Actor* const actor : addRequestedActors)
	{
		actors.emplace_back(actor);
		actor->SetOwner(this);
	}

	//�迭 �ʱ�ȭ.
	addRequestedActors.clear();
}


void Level::ProcessAddAndDestroyUI_InLevel()
{
	for (auto iterator = ui_inLevel.begin(); iterator != ui_inLevel.end();)
	{
		//���� ��û�� ���� Ȯ�� �� �迭���� ���ܽ�Ű�� �Լ�.
		//�����͸� ����Ű�� �����Ͱ� �ٷ� ���ͷ����� (*iterator = Actor*)
		if ((*iterator)->isExpiredUI)
		{
			iterator = ui_inLevel.erase(iterator);
			continue;
		}

		++iterator;
	}

	//�迭�� ��ȸ�ϸ鼭 ���� �����.
	for (auto* UI_InLevel : destroyRequestedUI)
	{
		Utils::SetConsolePosition(UI_InLevel->position);

		for (int i = 0; i < UI_InLevel->width; ++i)
		{
			std::cout << " ";
		}

		SafeDelete(UI_InLevel);
	}

	//�迭 �ʱ�ȭ
	destroyRequestedUI.clear();

	for (UI* const UI_InLevel : addRequestedUI)
	{
		ui_inLevel.emplace_back(UI_InLevel);
		UI_InLevel->SetOwner(this);
	}

	//�迭 �ʱ�ȭ.
	addRequestedUI.clear();
}


void Level::SortActorsBySortingOrder()
{
	// ���� ����.
	for (int ix = 0; ix < (int)actors.size(); ++ix)
	{
		for (int jx = 0; jx < (int)actors.size() - 1; ++jx)
		{
			// sortingOrder ���� Ŭ���� �� �ʿ� ��ġ.
			if (actors[jx]->sortingOrder > actors[jx + 1]->sortingOrder)
			{
				// �� ���� ��ġ ��ȯ.
				std::swap(actors[jx], actors[jx + 1]);
			}
		}
	}
}
