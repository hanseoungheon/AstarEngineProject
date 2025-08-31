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

	//struct HitResult
	//{
	//	bool bBlockingHit = false;
	//	Actor* HitActor = nullptr;
	//	Vector2 ImpacePoint = Vector2::Zero;
	//	Vector2 ImpaceNormal = Vector2::Zero;
	//	float Distance = 0.0f;
	//};


	//bool LineTraceSingleByChannel(HitResult& hitResult, Vector2& Start = Vector2::Zero, Vector2& End = Vector2::Zero, 
	//	const char ActorTag = ' ');
	/*const std::vector<Actor*>IgnoreActorType*/
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

	void SetLevelTrigger(bool Trigging);
	bool GetLevelTrigget();

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

	static bool IsLevelTrigged;

};