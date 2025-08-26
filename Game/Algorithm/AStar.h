#pragma once
#include <vector>
//���Ͱ� �ִµ� ���� ������? �ϴ� ����.
class Node;

class AStar
{
	//strcut Direction
public:
	AStar();
	~AStar();

	std::vector<Node*> FindPath(
		Node* startNode,
		Node* goalNode,
		std::vector<std::vector<char>>& grid
	);

	//�׸��� ��� �Լ�. �׸��带 ���ͷ� ����ؾ��ϳ�..? �ƴϸ�..?
	void DisplayGridWithPath(std::vector<std::vector<char>>& grid,
		const std::vector<Node*> path);

private:
	//Ž���� ��ģ �Ŀ� ��θ� ������ ��ȯ�ϴ� �Լ�.
	//��ǥ ��忡�� �θ� ��带 ������ ���۳����� ������ �ϸ鼭 ��θ� ���Ѵ�.
	std::vector<Node*> ConstructPath(Node* goalNode);

	//Ž���Ϸ��� ��尡 ��ǥ ������� Ȯ��.
	bool IsDestination(const Node* node);

	//�׸��� �ȿ� �ִ��� Ȯ���ϴ� �Լ�.
	bool IsInRange(int x, int y, const std::vector<std::vector<char>>& grid);

	//�̹� �湮�ߴ��� Ȯ���ϴ� �Լ�.
	bool HasVisited(int x, int y, float gCost);

	//���� �������� ��ǥ ���������� ���� ����� �Լ�.
	float CalilateHeuistic(Node* currentNode, Node* goalNode);

	void DisplayGrid(std::vector<std::vector<char>>& grid);

	void End(std::vector<std::vector<char>>& grid);

private:
	std::vector<Node*> openList;
	std::vector<Node*> closedList;
	Node* startNode = nullptr;
	Node* goalNode = nullptr;
};