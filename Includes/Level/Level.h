#pragma once
#include "Core.h"
#include <vector>
#include "RTTI.h"

class Actor; //전방선언.
class UI;

class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)
public:
	Level();
	virtual ~Level();

	// 레벨에 액터를 추가할 때 사용
	void AddActor(Actor* newActor);
	void AddUI(UI* newUI);

	// 액터 삭제 함수
	void DestroyActor(Actor* destroyedActor);
	void DestroyUI(UI* destroyedUI);

	// 엔진 이벤트 함수
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	//추가 및 삭제 요청된 액터를 처리하는 함수
	void ProcessAddAndDestroyActors();
	void ProcessAddAndDestroyUI_InLevel();

public:
	//Getter
	std::vector<Actor*> GetActorBuffer() const
	{
		return tempActor;
	}

	void ClearActorBuffer()
	{
		//for (Actor* actor : tempActor)
		//{
		//	SafeDelete(actor);
		//}

		tempActor.clear();
	}

private:
	void SortActorsBySortingOrder();

public:
	// 레벨에 배치된 모든액터를 관리하는 배열
	std::vector<Actor*> actors;

	//레벨에 배치된 모든 UI를 관리하는 배열
	std::vector<UI*> ui_inLevel;
protected:
	//추가 요청된 액터를 관리하는 배열
	std::vector<Actor*> addRequestedActors;

	//삭제 요청된 액터를 관리하는 배열
	std::vector<Actor*> destroyRequstedActors;

	//탐탁치 않지만 엔진에서 에이스타를 위한 벡터배열 추가해버리기.
	std::vector<Actor*> tempActor;


	std::vector<UI*> addRequestedUI;
	std::vector<UI*> destroyRequestedUI;



};