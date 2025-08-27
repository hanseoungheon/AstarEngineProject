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
    //일단 보류.
    //굳이 필요할려나?
    //Todo: 일단 이 코드를 게임엔진에 붙혀야함 방법은 그리드를 가져오기? 아니면 A스타를 Level에
    //가져가서 붙혀버리기? 생성자는 굳이?
}


std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, std::vector<std::vector<Actor*>>& grid)
{
    this->startNode = startNode;
    this->goalNode = goalNode;

    //시작 노드를 열린 목록에 저장.
    openList.emplace_back(startNode);

    //Todo: 방향벡터를 만들어보는 방법 고려.
    std::vector<Direction> directions =
    {
        //하 상 우 좌 순서로 이동.
        {Vector2(0,1),1.0f}, {Vector2(0,-1),1.0f}, {Vector2(1,0),1.0f}, {Vector2(-1,0),1.0f},

        {Vector2(1,1), 1.414f}, {Vector2(1,-1), 1.414f},
        {Vector2(-1,1), 1.414f}, {Vector2(-1,-1), 1.414f},

    };
    

    while (!openList.empty()) //열린 노드가 비어있지 않으면 계속 방문
    {
        //가장 비용이 적은 노드 선택.
        Node* lowestNode = openList[0];

        for (Node* node : openList)
        {
            if (node->GetgCost() < lowestNode->GetfCost())
            {
                lowestNode = node;
            }
        }

        Node* currentNode = lowestNode;

        //현재 노드가 목표 노드인지 확인.
        if (IsDestination(currentNode) == true)
        {
            //목표 노드라면 지금까지의 경로를 계산해서 반환.
            return ConstructPath(currentNode);
        }

        //닫힌 목록에 추가.
        for (int ix = 0; ix < (int)openList.size(); ++ix)
        {
            if (*openList[ix] == *currentNode)
            {
                //이터레이터를 사용해서 배열에서 노드 동적으로 제거.
                openList.erase(openList.begin() + ix);
                break;
            }
        }

        //현재 노드를 닫힌 노드에 추가.
        //먼저 이미 있는지부터 확인.
        bool isNodeInList = false;

        for (Node* node : closedList)
        {
            if (*node == *currentNode)
            {
                isNodeInList = true;
                break;
            }
        }

        //방문했으면 아래단계 건너뛰기.
        if (isNodeInList == true)
        {
            continue;
        }

        closedList.emplace_back(currentNode);

        //이웃노드 방문하기
        //Todo: 방향을 이대로 Vector2를 써도 되는지 방향벡터를 따로 실시간으로 구해야하는지 심사숙고.
        for (const Direction& direction : directions)
        {
            int newX = currentNode->GetNodePosition().x + direction.position.x;
            int newY = currentNode->GetNodePosition().y + direction.position.y;
            Vector2 newVector = Vector2(newX, newY);

            //그리드 밖인지 확인.
            if (IsInRange(newX,newY,grid) == false)
            {
                //그리드 밖이면 무시.
                continue;
            }

            //옵션 장애물인지 확인.
            //값이 #이면 장애물이라고 약속.

            if (grid[newX][newY]->GetImage() == "#")
            {
                continue;
            }

            //이미 방문했어도 무시.
            //이미 방문했는지는 확인하는 함수 호출.
            float gCost = currentNode->GetgCost() + direction.cost;
            if (HasVisited(newX,newY,gCost) == true)
            {
                continue;
            }

            //방문을 위한 노드 생성.
            Node* neightborNode = new Node(newVector, currentNode);
            //비용도 계산.
            //Getter는 const라 대입이 불가했음 그래서 그냥 Setter를 대입.
            //neightborNode->GetgCost() = currentNode->GetgCost() + direction.cost;
            neightborNode->SetgCost(currentNode->GetgCost() + direction.cost);

            //neightborNode->GethCost() = CalculateHeuistic();
            neightborNode->SethCost(CalculateHeuistic(neightborNode,goalNode));

            neightborNode->SetfCost(neightborNode->GetgCost() + neightborNode->GethCost());

            //이웃 노드가 열린 리스트에 있는지 확인.
            Node* openListNode = nullptr;
            for (Node* node : openList)
            {
                if (*node == *neightborNode)
                {
                    openListNode = node;
                    break;
                }
            }

            //노드가 목록에 없거나 Or 비용이 싸면, 새 노드를 추가합니다.
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
    //경로 반환.

    //출력용 경로 배열 선언.
    std::vector<Node*> path;
    Node* currentNode = goalNode;

    
    while (currentNode != nullptr)
    {
        path.emplace_back(currentNode);
        currentNode = currentNode->GetParent();
    }

    //지금까지의 경로는 목표->시작 노드방향이므로 이 순서를 뒤집어야만함.
    std::reverse(path.begin(), path.end());
    
    return path;
}

bool AStar::IsDestination(const Node* node)
{
    return *node == *goalNode;
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<Actor*>>& grid)
{
    //범위 안에 있는지 체크하기. 얘도 굳이 필요할까 굳이?
    if (x < 0 || y > 0 || x >= (int)grid[0].size() || y >= (int)grid.size())
    {
        return false;
    }

    return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
    //열린 리스트나 닫힌 리스트에 이미 해당 노드가 있다면 방문한것으로 판단합니다.
    for (int ix = 0; ix < (int)openList.size(); ++ix)
    {
        Node* node = openList[ix];

        if (node->GetNodePosition().x == x && node->GetNodePosition().y == y)
        {
            //위치가 같은데 비용도 더 크면 방문 X
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
    //단순 서리계산으로 휴리스틱 비용으로 활용.
    Vector2 diff = *currentNode - *goalNode;

    //대각선 길이 구하기.
    return (float)std::sqrt(diff.x ^ 2 + diff.y ^ 2);
}
