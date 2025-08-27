#pragma once
#include "Level/Level.h"
#include "Algorithm/Node.h"

#include <vector>

class SokobanLevel : public Level
{
	RTTI_DECLARATIONS(SokobanLevel, Level)

public:
	SokobanLevel();

private:
	virtual void BeginPlay() override;
	virtual void Render() override;
	void ReadMapFile(const char* fileName);

	bool CheckGameClear();

	void FindStartAndGoal(Node**outStartNode,Node**outGoalNode);

public:
	//Getter

private:
	int targetScore = 0;
	bool isGameClear = false;
	std::vector<std::vector<Actor*>> MapGrid;
	Node* startNode = nullptr;
	Node* goalNode = nullptr;
};