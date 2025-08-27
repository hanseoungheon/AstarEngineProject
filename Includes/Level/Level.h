#pragma once
#include "Core.h"
#include <vector>
#include "RTTI.h"

class Actor; //���漱��.

class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)
public:
	Level();
	virtual ~Level();

	// ������ ���͸� �߰��� �� ���
	void AddActor(Actor* newActor);

	// ���� ���� �Լ�
	void DestroyActor(Actor* destroyedActor);

	// ���� �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	//�߰� �� ���� ��û�� ���͸� ó���ϴ� �Լ�
	void ProcessAddAndDestroyActors();

public:
	//Getter
	std::vector<Actor*> GetActorBuffer() const
	{
		return tempActor;
	}

	void ClearActorBuffer()
	{
		tempActor.clear();
	}

private:
	void SortActorsBySortingOrder();

public:
	// ������ ��ġ�� �����͸� �����ϴ� �迭
	std::vector<Actor*> actors;
protected:
	//�߰� ��û�� ���͸� �����ϴ� �迭
	std::vector<Actor*> addRequestedActors;

	//���� ��û�� ���͸� �����ϴ� �迭
	std::vector<Actor*> destroyRequstedActors;

	//ŽŹġ ������ �������� ���̽�Ÿ�� ���� ���͹迭 �߰��ع�����.
	std::vector<Actor*> tempActor;
};