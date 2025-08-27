#pragma once
#include <vector>
#include "Math/Vector2.h"
#include "Actor/Actor.h"
//벡터가 있는데 굳이 방향을? 일단 보류.
//그냥 노드를 액터로 사용해버리기? 
class Node;

class AStar
{
	//방향처리를 위한 구조체.
	struct Direction
	{
		Vector2 position = Vector2::Zero;

		float cost;
		float dir;
	};

public:
	AStar();
	~AStar();
	

	std::vector<Node*> FindPath(
		Node* startNode,
		Node* goalNode,
		std::vector<std::vector<Actor*>>& grid
	);

	void FindPath_NonReturn(
		Node* startNode,
		Node* goalNode,
		std::vector<std::vector<Actor*>>& grid
	);

	//그리드 출력 함수. 그리드를 액터로 출력해야하나..? 아니면..?
	void DisplayGridWithPath(std::vector<std::vector<Actor*>>& grid,
		const std::vector<Node*> path);

	//void FindStartAndGoal(Actor);

private:
	//탐색을 마친 후에 경로를 조립해 반환하는 함수.
	//목표 노드에서 부모 노드를 참조해 시작노드까지 역추적 하면서 경로를 구한다.
	std::vector<Node*> ConstructPath(Node* goalNode);

	//탐색하려는 노드가 목표 노드인지 확인.
	bool IsDestination(const Node* node);

	//그리드 안에 있는지 확인하는 함수.
	bool IsInRange(int x, int y, const std::vector<std::vector<Actor*>>& grid);

	//이미 방문했는지 확인하는 함수.
	bool HasVisited(int x, int y, float gCost);

	//현재 지점에서 목표 지점까지의 추정 비용계산 함수.
	float CalculateHeuistic(Node* currentNode, Node* goalNode);

	//void DisplayGrid(std::vector<std::vector<char>>& grid);

	//void End(std::vector<std::vector<char>>& grid);

private:
	std::vector<Node*> openList;
	std::vector<Node*> closedList;
	Node* startNode = nullptr;
	Node* goalNode = nullptr;
};