#pragma once
#include "Core.h"
#include <vector>
#include "RTTI.h"

class Actor; //전방선언.
class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level,RTTI)

public:
	Level();
	virtual ~Level();
	
	//액터추가요청
	void AddActor(Actor* newActor);

	//액터 삭제요청.
	void DestroyActor(Actor* destroyedActor);

	virtual void BeginPlay();
	virtual void Tick(float DeltaTime = 0.0f);
	virtual void Render();

	//추가 및 삭제 요청된 액터들 처리하는 함수.
	void ProcessAddAndDestroyActors();

private:
	void SortActorsBySortingOrder();

protected:
	//레벨에 배치된 모든 액터를 관리하는 배열.
	std::vector<Actor*> actors;

	//추가 요청된 액터를 관리하는 배열.
	std::vector<Actor*> addRequestedActors;

	std::vector<Actor*> destroyRequsetedActors;
};
