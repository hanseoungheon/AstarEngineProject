#pragma once
#include "Core.h"
#include <vector>
#include "RTTI.h"

class Actor; //���漱��.
class UI;

class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)
public:
	Level();
	virtual ~Level();

	// ������ ���͸� �߰��� �� ���
	void AddActor(Actor* newActor);
	void AddUI(UI* newUI);

	// ���� ���� �Լ�
	void DestroyActor(Actor* destroyedActor);
	void DestroyUI(UI* destroyedUI);

	// ���� �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	//�߰� �� ���� ��û�� ���͸� ó���ϴ� �Լ�
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
	// ������ ��ġ�� �����͸� �����ϴ� �迭
	std::vector<Actor*> actors;

	//������ ��ġ�� ��� UI�� �����ϴ� �迭
	std::vector<UI*> ui_inLevel;
protected:
	//�߰� ��û�� ���͸� �����ϴ� �迭
	std::vector<Actor*> addRequestedActors;

	//���� ��û�� ���͸� �����ϴ� �迭
	std::vector<Actor*> destroyRequstedActors;

	//ŽŹġ ������ �������� ���̽�Ÿ�� ���� ���͹迭 �߰��ع�����.
	std::vector<Actor*> tempActor;


	std::vector<UI*> addRequestedUI;
	std::vector<UI*> destroyRequestedUI;



};