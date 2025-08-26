#pragma once
#include "Math/Vector2.h"
class Node
{
public:
	Node(int x, int y, Node* parentNode = nullptr)
		: NodeVector(x, y), parent(parentNode)
	{

	}

private:
	Vector2 NodeVector;

	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;

	Node* parent = nullptr;

};