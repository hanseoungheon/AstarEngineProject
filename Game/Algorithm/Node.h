#pragma once
#include "Math/Vector2.h"
class Node
{
	//struct Position
	//{
	//	Vector2 NBoposition;
	//};
public:
	Node(const Vector2& position, Node* parentNode = nullptr)
		: NodePosition(position), parent(parentNode)
	{

	}

	Vector2 operator-(const Node& other)
	{
		return Vector2(
			NodePosition.x - other.NodePosition.x,
			NodePosition.y - other.NodePosition.y
		);
	}
	bool operator==(const Node& other) const
	{
		return NodePosition.x == other.NodePosition.x &&
			NodePosition.y == other.NodePosition.y;
	}

public:
	//Getter & Setter
	//일단 게터만 정정. 세터도 필요할듯?

	Node* GetParent() const
	{
		return parent;
	}
	Vector2 GetNodePosition() const
	{
		return NodePosition;
	}

	float GetgCost() const
	{
		return gCost;
	}

	void SetgCost(const float newgCost)
	{
		gCost = newgCost;
	}

	float GethCost() const
	{
		return hCost;
	}

	void SethCost(const float newhCost)
	{
		hCost = newhCost;
	}

	float GetfCost() const
	{
		return fCost;
	}

	void SetfCost(const float newfCost)
	{
		fCost = newfCost;
	}

public:
	Vector2 NodePosition;

	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;

	Node* parent = nullptr;

};