#pragma once
#include "Level/Level.h"
#include "Algorithm/Node.h"
#include "Algorithm/Astar.h"
#include "Interface/ICanPlayerMove.h"
#include <vector>

class SokobanLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)

public:
	SokobanLevel();
	~SokobanLevel();

	// ICanPlayerMove��(��) ���� ��ӵ�
	virtual bool CanPlayerMove(
		const Vector2& playerPosition,
		const Vector2& newPosition) override;


private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render() override;
	void ReadMapFile(const char* fileName);

	bool CheckGameClear();

	void FindStartAndGoal(Node** outStartNode,Node** outGoalNode);
	void FindStartAndGoal_Using_Vector(Vector2& startPos,Vector2& goalPos);

	void FindOriginalActor();

	void CreatePlayerAndTargetStatUI();
	void HowToMovementAndOtherManualUI();


public:
	//Getter

private:
	int targetScore = 0;
	bool isGameClear = false;

	//Tick ��� �� ������ȣ�⿡�� ������ �ǳʶٱ� ��
	int JumpTick = 0;


	std::vector<std::vector<Actor*>> MapGrid;


	AStar Astar;
	Node* startNode = nullptr;
	Node* goalNode = nullptr;
	Vector2 startPos;
	Vector2 goalPos;

	bool IsChageTheCharacter = false;

	int iterator = 0;
};