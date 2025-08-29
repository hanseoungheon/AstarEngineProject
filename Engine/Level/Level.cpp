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
		//삭제 요청이 들어오거나 활성화가 안된 상태의 액터는 건너뜀
		if (actor->isActive == false || actor->isExpired == true)
		{
			continue;
		}

		//이미 호출이 된 개체는 건너뛰기.
		if (actor->HasBeganPlay() == true)
		{
			continue;
		}

		//액터 실행시키기.
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

		//검사 -> 같은 위치에 정렬 순서 높은 액터가 있는지 확인하기.
		for (Actor* const otherActor : actors)
		{
			if (actor == otherActor)
			{
				continue;
			}

			if (actor->GetActorPosition() == otherActor->GetActorPosition())
			{
				//정렬 순서 비교 후 더 높은 액터가 덮어씌움.
				if (actor->sortingOrder < otherActor->sortingOrder)
				{
					searchedActor = otherActor;
					break;
				}
			}
		}

		//어떤 액터와 같은 위치에 정렬 순서가 더 높은 액터가 있으면, 그러지 않고 건너뛰기.
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

		//UI는 정렬순서를 신경쓰지 않음.
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
		//삭제 요청된 액터 확인 후 배열에서 제외시키는 함수.
		//포인터를 가르키는 포인터가 바로 이터레이터 (*iterator = Actor*)
		if ((*iterator)->isExpired)
		{
			iterator = actors.erase(iterator);
			continue;
		}

		++iterator;
	}

	//배열을 순회하면서 액터 지우기.
	for (auto* actor : destroyRequstedActors)
	{
		Utils::SetConsolePosition(actor->position);

		for (int i = 0; i < actor->width; ++i)
		{
			std::cout << " ";
		}

		SafeDelete(actor);
	}

	//배열 초기화
	destroyRequstedActors.clear();

	for (Actor* const actor : addRequestedActors)
	{
		actors.emplace_back(actor);
		actor->SetOwner(this);
	}

	//배열 초기화.
	addRequestedActors.clear();
}


void Level::ProcessAddAndDestroyUI_InLevel()
{
	for (auto iterator = ui_inLevel.begin(); iterator != ui_inLevel.end();)
	{
		//삭제 요청된 액터 확인 후 배열에서 제외시키는 함수.
		//포인터를 가르키는 포인터가 바로 이터레이터 (*iterator = Actor*)
		if ((*iterator)->isExpiredUI)
		{
			iterator = ui_inLevel.erase(iterator);
			continue;
		}

		++iterator;
	}

	//배열을 순회하면서 액터 지우기.
	for (auto* UI_InLevel : destroyRequestedUI)
	{
		Utils::SetConsolePosition(UI_InLevel->position);

		for (int i = 0; i < UI_InLevel->width; ++i)
		{
			std::cout << " ";
		}

		SafeDelete(UI_InLevel);
	}

	//배열 초기화
	destroyRequestedUI.clear();

	for (UI* const UI_InLevel : addRequestedUI)
	{
		ui_inLevel.emplace_back(UI_InLevel);
		UI_InLevel->SetOwner(this);
	}

	//배열 초기화.
	addRequestedUI.clear();
}


void Level::SortActorsBySortingOrder()
{
	// 버블 정렬.
	for (int ix = 0; ix < (int)actors.size(); ++ix)
	{
		for (int jx = 0; jx < (int)actors.size() - 1; ++jx)
		{
			// sortingOrder 값이 클수록 뒤 쪽에 배치.
			if (actors[jx]->sortingOrder > actors[jx + 1]->sortingOrder)
			{
				// 두 액터 위치 교환.
				std::swap(actors[jx], actors[jx + 1]);
			}
		}
	}
}
