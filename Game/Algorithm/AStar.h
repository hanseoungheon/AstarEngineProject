#pragma once
#include <vector>
#include "Math/Vector2.h"
#include "Actor/Actor.h"
//���Ͱ� �ִµ� ���� ������? �ϴ� ����.
//�׳� ��带 ���ͷ� ����ع�����? 
class Node;

class AStar
{
	//����ó���� ���� ����ü.
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

	//�׸��� ��� �Լ�. �׸��带 ���ͷ� ����ؾ��ϳ�..? �ƴϸ�..?
	void DisplayGridWithPath(std::vector<std::vector<Actor*>>& grid,
		const std::vector<Node*> path);

	//void FindStartAndGoal(Actor);

private:
	//Ž���� ��ģ �Ŀ� ��θ� ������ ��ȯ�ϴ� �Լ�.
	//��ǥ ��忡�� �θ� ��带 ������ ���۳����� ������ �ϸ鼭 ��θ� ���Ѵ�.
	std::vector<Node*> ConstructPath(Node* goalNode);

	//Ž���Ϸ��� ��尡 ��ǥ ������� Ȯ��.
	bool IsDestination(const Node* node);

	//�׸��� �ȿ� �ִ��� Ȯ���ϴ� �Լ�.
	bool IsInRange(int x, int y, const std::vector<std::vector<Actor*>>& grid);

	//�̹� �湮�ߴ��� Ȯ���ϴ� �Լ�.
	bool HasVisited(int x, int y, float gCost);

	//���� �������� ��ǥ ���������� ���� ����� �Լ�.
	float CalculateHeuistic(Node* currentNode, Node* goalNode);

	//void DisplayGrid(std::vector<std::vector<char>>& grid);

	//void End(std::vector<std::vector<char>>& grid);

private:
	std::vector<Node*> openList;
	std::vector<Node*> closedList;
	Node* startNode = nullptr;
	Node* goalNode = nullptr;
};