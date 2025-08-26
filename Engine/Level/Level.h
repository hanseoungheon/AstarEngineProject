#pragma once
#include "Core.h"
#include <vector>
#include "RTTI.h"

class Actor; //���漱��.
class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level,RTTI)

public:
	Level();
	virtual ~Level();
	
	//�����߰���û
	void AddActor(Actor* newActor);

	//���� ������û.
	void DestroyActor(Actor* destroyedActor);

	virtual void BeginPlay();
	virtual void Tick(float DeltaTime = 0.0f);
	virtual void Render();

	//�߰� �� ���� ��û�� ���͵� ó���ϴ� �Լ�.
	void ProcessAddAndDestroyActors();

private:
	void SortActorsBySortingOrder();

protected:
	//������ ��ġ�� ��� ���͸� �����ϴ� �迭.
	std::vector<Actor*> actors;

	//�߰� ��û�� ���͸� �����ϴ� �迭.
	std::vector<Actor*> addRequestedActors;

	std::vector<Actor*> destroyRequsetedActors;
};
