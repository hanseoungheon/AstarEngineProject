#include "Core.h"
#include "Node.h"
#include "AStar.h"
#include <Windows.h>
#include <iostream>

AStar::AStar()
{

}

AStar::~AStar()
{
    for (Node* node : openList)
    {
        SafeDelete(node);
    }
    openList.clear();

    for (Node* node : closedList)
    {
        SafeDelete(node);
    }
    closedList.clear();

}

void AStar::DisplayGridWithPath(std::vector<std::vector<Actor*>>& grid, const std::vector<Node*> path)
{
    //�ϴ� ����.
    //���� �ʿ��ҷ���?
    //Todo: �ϴ� �� �ڵ带 ���ӿ����� �������� ����� �׸��带 ��������? �ƴϸ� A��Ÿ�� Level��
    //�������� ����������? �����ڴ� ����?
}


std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, std::vector<std::vector<Actor*>>& grid)
{
    this->startNode = startNode;
    this->goalNode = goalNode;

    //���� ��带 ���� ��Ͽ� ����.
    openList.emplace_back(startNode);

    //Todo: ���⺤�͸� ������ ��� ���.
    std::vector<Direction> directions =
    {
        //�� �� �� �� ������ �̵�.
        {Vector2(0,1),1.0f}, {Vector2(0,-1),1.0f}, {Vector2(1,0),1.0f}, {Vector2(-1,0),1.0f},

        {Vector2(1,1), 1.414f}, {Vector2(1,-1), 1.414f},
        {Vector2(-1,1), 1.414f}, {Vector2(-1,-1), 1.414f},

    };
    

    while (!openList.empty()) //���� ��尡 ������� ������ ��� �湮
    {
        //���� ����� ���� ��� ����.
        Node* lowestNode = openList[0];

        for (Node* node : openList)
        {
            if (node->GetgCost() < lowestNode->GetfCost())
            {
                lowestNode = node;
            }
        }

        Node* currentNode = lowestNode;

        //���� ��尡 ��ǥ ������� Ȯ��.
        if (IsDestination(currentNode) == true)
        {
            //��ǥ ����� ���ݱ����� ��θ� ����ؼ� ��ȯ.
            return ConstructPath(currentNode);
        }

        //���� ��Ͽ� �߰�.
        for (int ix = 0; ix < (int)openList.size(); ++ix)
        {
            if (*openList[ix] == *currentNode)
            {
                //���ͷ����͸� ����ؼ� �迭���� ��� �������� ����.
                openList.erase(openList.begin() + ix);
                break;
            }
        }

        //���� ��带 ���� ��忡 �߰�.
        //���� �̹� �ִ������� Ȯ��.
        bool isNodeInList = false;

        for (Node* node : closedList)
        {
            if (*node == *currentNode)
            {
                isNodeInList = true;
                break;
            }
        }

        //�湮������ �Ʒ��ܰ� �ǳʶٱ�.
        if (isNodeInList == true)
        {
            continue;
        }

        closedList.emplace_back(currentNode);

        //�̿���� �湮�ϱ�
        //Todo: ������ �̴�� Vector2�� �ᵵ �Ǵ��� ���⺤�͸� ���� �ǽð����� ���ؾ��ϴ��� �ɻ����.
        for (const Direction& direction : directions)
        {
            int newX = currentNode->GetNodePosition().x + direction.position.x;
            int newY = currentNode->GetNodePosition().y + direction.position.y;
            Vector2 newVector = Vector2(newX, newY);

            //�׸��� ������ Ȯ��.
            if (IsInRange(newX,newY,grid) == false)
            {
                //�׸��� ���̸� ����.
                continue;
            }

            //�ɼ� ��ֹ����� Ȯ��.
            //���� #�̸� ��ֹ��̶�� ���.

            if (grid[newX][newY]->GetImage() == "#")
            {
                continue;
            }

            //�̹� �湮�߾ ����.
            //�̹� �湮�ߴ����� Ȯ���ϴ� �Լ� ȣ��.
            float gCost = currentNode->GetgCost() + direction.cost;
            if (HasVisited(newX,newY,gCost) == true)
            {
                continue;
            }

            //�湮�� ���� ��� ����.
            Node* neightborNode = new Node(newVector, currentNode);
            //��뵵 ���.
            //Getter�� const�� ������ �Ұ����� �׷��� �׳� Setter�� ����.
            //neightborNode->GetgCost() = currentNode->GetgCost() + direction.cost;
            neightborNode->SetgCost(currentNode->GetgCost() + direction.cost);

            //neightborNode->GethCost() = CalculateHeuistic();
            neightborNode->SethCost(CalculateHeuistic(neightborNode,goalNode));

            neightborNode->SetfCost(neightborNode->GetgCost() + neightborNode->GethCost());

            //�̿� ��尡 ���� ����Ʈ�� �ִ��� Ȯ��.
            Node* openListNode = nullptr;
            for (Node* node : openList)
            {
                if (*node == *neightborNode)
                {
                    openListNode = node;
                    break;
                }
            }

            //��尡 ��Ͽ� ���ų� Or ����� �θ�, �� ��带 �߰��մϴ�.
            if (openListNode == nullptr ||
                openListNode->GetgCost() > neightborNode->GetgCost() ||
                openListNode->GetfCost() > neightborNode->GetfCost())
            {
                openList.emplace_back(neightborNode);
            }
            else
            {
                SafeDelete(neightborNode);
            }
        }
    }
    return std::vector<Node*>();
}


std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
    //��� ��ȯ.

    //��¿� ��� �迭 ����.
    std::vector<Node*> path;
    Node* currentNode = goalNode;

    
    while (currentNode != nullptr)
    {
        path.emplace_back(currentNode);
        currentNode = currentNode->GetParent();
    }

    //���ݱ����� ��δ� ��ǥ->���� �������̹Ƿ� �� ������ ������߸���.
    std::reverse(path.begin(), path.end());
    
    return path;
}

bool AStar::IsDestination(const Node* node)
{
    return *node == *goalNode;
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<Actor*>>& grid)
{
    //���� �ȿ� �ִ��� üũ�ϱ�. �굵 ���� �ʿ��ұ� ����?
    if (x < 0 || y > 0 || x >= (int)grid[0].size() || y >= (int)grid.size())
    {
        return false;
    }

    return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
    //���� ����Ʈ�� ���� ����Ʈ�� �̹� �ش� ��尡 �ִٸ� �湮�Ѱ����� �Ǵ��մϴ�.
    for (int ix = 0; ix < (int)openList.size(); ++ix)
    {
        Node* node = openList[ix];

        if (node->GetNodePosition().x == x && node->GetNodePosition().y == y)
        {
            //��ġ�� ������ ��뵵 �� ũ�� �湮 X
            if (node->GetgCost() < gCost)
            {
                return true;
            }

            else if (node->GetgCost() > gCost)
            {
                openList.erase(openList.begin() + ix);
                SafeDelete(node);
            }
        }
    }

    for (int ix = 0; ix < (int)closedList.size(); ++ix)
    {
        Node* node = closedList[ix];

        if (node->GetNodePosition().x == x && node->GetNodePosition().y == y)
        {
            if (node->GetgCost() < gCost)
            {
                return true;
            }
            else if (node->GetgCost() > gCost)
            {
                closedList.erase(closedList.begin() + ix);
                SafeDelete(node);
            }
        }
    }

    return false;
}

float AStar::CalculateHeuistic(Node* currentNode, Node* goalNode)
{
    //�ܼ� ����������� �޸���ƽ ������� Ȱ��.
    Vector2 diff = *currentNode - *goalNode;

    //�밢�� ���� ���ϱ�.
    return (float)std::sqrt(diff.x ^ 2 + diff.y ^ 2);
}
