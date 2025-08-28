#include "Core.h"
#include "Node.h"
#include "AStar.h"
#include <Windows.h>
#include <iostream>

AStar::AStar()
    :IsFindingPath(false), IsFoundPath(false),HasRevertGround(false),x(0),y(0)
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
    //Todo: 일단 이 코드를 게임엔진에 붙혀야함 방법은 그리드를 가져오기? 아니면 A스타를 Level에\n가져가서 붙혀버리기? 생성자는 굳이?
    //가져가서 붙혀버리기? 생성자는 굳이?

    //일단 경로 표시는 하는게 좋을듯.
    if (HasRevertGround == false)
    {
        for (int y = 0; y < grid.size(); ++y)
        {
            for (int x = 0; x < grid[0].size(); ++x)
            {
                if (grid[y][x]->GetOriginalActor()->GetNameTag() == 'R' &&
                    grid[y][x]->GetOriginalActor()->GetTrigger() == true)
                {
                    grid[y][x]->SetOriginalActorImage("."); //SetOriginalActorImage?
                    grid[y][x]->SetOriginalActorColor(Color::White); //SetOriginalActorColor?
                }
            }
        }

        HasRevertGround = true;
    }


    for (const Node* node : path)
    {
        Vector2 PathVector = node->GetNodePosition();
        for (int y = 0; y < grid.size(); ++y)
        {
            for (int x = 0; x < grid[0].size(); ++x)
            {
                if (grid[y][x]->GetActorPosition() == PathVector)
                {
                    grid[y][x]->SetOriginalActorImage("*");
                    grid[y][x]->SetOriginalActorColor(Color::LightGreen);
                }
            }
        }
    }

    //Node* node = nullptr;

    //if (x < path.size())
    //{
    //    Vector2 PathVector = path[x++]->GetNodePosition();

    //    for (int y = 0; y < grid.size(); ++y)
    //    {
    //        for (int x = 0; x < grid[0].size(); ++x)
    //        {
    //            if (grid[y][x]->GetActorPosition() == PathVector)
    //            {
    //                grid[y][x]->SetOriginalActorImage("*");
    //                grid[y][x]->SetOriginalActorColor(Color::LightGreen);
    //            }
    //        }
    //    }

    //}
}


//std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, std::vector<std::vector<Actor*>>& grid)
//{
//    //Todo: 이거를 한틱씩 가게 쪼개야됨.->성공.
//    this->startNode = startNode;
//    this->goalNode = goalNode;
//
//    //시작 노드를 열린 목록에 저장.
//    openList.emplace_back(startNode);
//
//    //방향벡터를 만들어보는 방법 고려.->완료
//    std::vector<Direction> directions =
//    {
//        //하 상 우 좌 순서로 이동.
//        {Vector2(0,1),1.0f}, {Vector2(0,-1),1.0f}, {Vector2(1,0),1.0f}, {Vector2(-1,0),1.0f},
//
//        {Vector2(1,1), 1.414f}, {Vector2(1,-1), 1.414f},
//        {Vector2(-1,1), 1.414f}, {Vector2(-1,-1), 1.414f},
//
//    };
//    
//
//    while (!openList.empty()) //열린 노드가 비어있지 않으면 계속 방문
//    {
//        //가장 비용이 적은 노드 선택.
//        Node* lowestNode = openList[0];
//
//        for (Node* node : openList)
//        {
//            if (node->fCost < lowestNode->fCost)
//            {
//                lowestNode = node;
//            }
//        }
//
//        Node* currentNode = lowestNode;
//
//        //현재 노드가 목표 노드인지 확인.
//        if (IsDestination(currentNode) == true)
//        {
//            //목표 노드라면 지금까지의 경로를 계산해서 반환.
//            return ConstructPath(currentNode);
//        }
//
//        //닫힌 목록에 추가.
//        for (int ix = 0; ix < (int)openList.size(); ++ix)
//        {
//            if (*openList[ix] == *currentNode)
//            {
//                //이터레이터를 사용해서 배열에서 노드 동적으로 제거.
//                openList.erase(openList.begin() + ix);
//                break;
//            }
//        }
//
//        //현재 노드를 닫힌 노드에 추가.
//        //먼저 이미 있는지부터 확인.
//        bool isNodeInList = false;
//
//        for (Node* node : closedList)
//        {
//            if (*node == *currentNode)
//            {
//                isNodeInList = true;
//                break;
//            }
//        }
//
//        //방문했으면 아래단계 건너뛰기.
//        if (isNodeInList == true)
//        {
//            continue;
//        }
//
//        closedList.emplace_back(currentNode);
//
//        //이웃노드 방문하기
//        //Todo: 방향을 이대로 Vector2를 써도 되는지 방향벡터를 따로 실시간으로 구해야하는지 심사숙고.->페기예정?
//        for (const Direction& direction : directions)
//        {
//            int newX = currentNode->GetNodePosition().x + direction.position.x;
//            int newY = currentNode->GetNodePosition().y + direction.position.y;
//            Vector2 newVector = Vector2(newX, newY);
//
//            //그리드 밖인지 확인.
//            if (IsInRange(newX,newY,grid) == false)
//            {
//                //그리드 밖이면 무시.
//                continue;
//            }
//
//            //옵션 장애물인지 확인.
//            //값이 #이면 장애물이라고 약속.
//
//            if (grid[newY][newX]->GetOriginalActor()->GetImage() == "#")
//            {
//                continue;
//            }
//
//            //이미 방문했어도 무시.
//            //이미 방문했는지는 확인하는 함수 호출.
//            float gCost = currentNode->gCost + direction.cost;
//            if (HasVisited(newX,newY,gCost) == true)
//            {
//                continue;
//            }
//
//            //방문을 위한 노드 생성.
//            Node* neightborNode = new Node(newVector, currentNode);
//            //비용도 계산.
//            //Getter는 const라 대입이 불가했음 그래서 그냥 Setter를 대입.
//            //neightborNode->GetgCost() = currentNode->GetgCost() + direction.cost;
//            neightborNode->gCost = currentNode->gCost + direction.cost;
//
//            //neightborNode->GethCost() = CalculateHeuistic();
//            neightborNode->hCost = CalculateHeuistic(neightborNode,goalNode);
//
//            neightborNode->fCost = neightborNode->gCost + neightborNode->hCost;
//
//            //이웃 노드가 열린 리스트에 있는지 확인.
//            Node* openListNode = nullptr;
//            for (Node* node : openList)
//            {
//                if (*node == *neightborNode)
//                {
//                    openListNode = node;
//                    break;
//                }
//            }
//
//            //노드가 목록에 없거나 Or 비용이 싸면, 새 노드를 추가합니다.
//            if (openListNode == nullptr ||
//                openListNode->gCost > neightborNode->gCost ||
//                openListNode->fCost > neightborNode->fCost)
//            {
//                //Todo: 현재 중점 고민 과제. 현재 그리는 레벨의 액터집합의 복사본임. 
//                // 그리드를 안쓰고 벡터를 사용해보는방법도 고려해보기.
//                Vector2 test = Vector2(newX, newY);
//                //액터배열? 
//                 
//                
//                //여기서 boolean 변수를 바꿔버리는걸로 하자 그냥.
//                grid[newY][newX]->SetOriginalActorImage("+"); //SetOriginalActorImage?
//                grid[newY][newX]->SetOriginalActorColor(Color::Green); //SetOriginalActorColor?
//
//                grid[newY][newX]->GetOriginalActor()->SetTrigger(true);
//                 
//                
//                //음.. 위치가 같으면 같은 액터로 판정 해버리기?
//                openList.emplace_back(neightborNode);
//            }
//            else
//            {
//                //grid[newX][newY]->SetOriginalActorImage("#");
//                //grid[newX][newY]->SetOriginalActorColor(Color::Green);
//                SafeDelete(neightborNode);
//            }
//
//            int delay = (int)(0.1f * 1000);
//            //Sleep(5);
//        }
//    }
//    return std::vector<Node*>();
//}

//void AStar::FindPath_NonReturn(Node* startNode, Node* goalNode, std::vector<std::vector<Actor*>>& grid)
//{
//    this->startNode = startNode;
//    this->goalNode = goalNode;
//
//    //시작 노드를 열린 목록에 저장.
//    openList.emplace_back(this->startNode);
//
//    //Todo:방향벡터를 만들어보는 방법 고려.->애는 폐기 예정 아마도?
//    std::vector<Direction> directions =
//    {
//        //하 상 우 좌 순서로 이동.
//        {Vector2(0,1),1.0f}, {Vector2(0,-1),1.0f}, {Vector2(1,0),1.0f}, {Vector2(-1,0),1.0f},
//
//        {Vector2(1,1), 1.414f}, {Vector2(1,-1), 1.414f},
//        {Vector2(-1,1), 1.414f}, {Vector2(-1,-1), 1.414f},
//
//    };
//
//
//    while (!openList.empty()) //열린 노드가 비어있지 않으면 계속 방문
//    {
//        //가장 비용이 적은 노드 선택.
//        Node* lowestNode = openList[0];
//
//        for (Node* node : openList)
//        {
//            if (node->fCost < lowestNode->fCost)
//            {
//                lowestNode = node;
//            }
//        }
//
//        Node* currentNode = lowestNode;
//
//        //현재 노드가 목표 노드인지 확인.
//        if (IsDestination(currentNode) == true)
//        {
//            ////목표 노드라면 지금까지의 경로를 계산해서 반환.
//            //return ConstructPath(currentNode);
//            std::cout << "찾았습니다.\n";
//        }
//
//        //닫힌 목록에 추가.
//        for (int ix = 0; ix < (int)openList.size(); ++ix)
//        {
//            if (*openList[ix] == *currentNode)
//            {
//                //이터레이터를 사용해서 배열에서 노드 동적으로 제거.
//                openList.erase(openList.begin() + ix);
//                break;
//            }
//        }
//
//        //현재 노드를 닫힌 노드에 추가.
//        //먼저 이미 있는지부터 확인.
//        bool isNodeInList = false;
//
//        for (Node* node : closedList)
//        {
//            if (*node == *currentNode)
//            {
//                isNodeInList = true;
//                break;
//            }
//        }
//
//        //방문했으면 아래단계 건너뛰기.
//        if (isNodeInList == true)
//        {
//            continue;
//        }
//
//        closedList.emplace_back(currentNode);
//
//        //이웃노드 방문하기
//        //Todo: 방향을 이대로 Vector2를 써도 되는지 방향벡터를 따로 실시간으로 구해야하는지 심사숙고.->폐기예정?
//        for (const Direction& direction : directions)
//        {
//            int newX = currentNode->GetNodePosition().x + direction.position.x;
//            int newY = currentNode->GetNodePosition().y + direction.position.y;
//            Vector2 newVector = Vector2(newX, newY);
//
//            //그리드 밖인지 확인.
//            if (IsInRange(newX, newY, grid) == false)
//            {
//                //그리드 밖이면 무시.
//                continue;
//            }
//
//            //옵션 장애물인지 확인.
//            //값이 #이면 장애물이라고 약속.
//
//            if (grid[newY][newX]->GetImage() == "#")
//            {
//                continue;
//            }
//
//            //이미 방문했어도 무시.
//            //이미 방문했는지는 확인하는 함수 호출.
//            float gCost = currentNode->gCost + direction.cost;
//            if (HasVisited(newX, newY, gCost) == true)
//            {
//                continue;
//            }
//
//            //방문을 위한 노드 생성.
//            Node* neightborNode = new Node(newVector, currentNode);
//            //비용도 계산.
//            //Getter는 const라 대입이 불가했음 그래서 그냥 Setter를 대입.
//            //neightborNode->GetgCost() = currentNode->GetgCost() + direction.cost;
//            neightborNode->gCost = currentNode->gCost + direction.cost;
//
//            //neightborNode->GethCost() = CalculateHeuistic();
//            neightborNode->hCost = CalculateHeuistic(neightborNode, goalNode);
//
//            neightborNode->fCost = neightborNode->gCost + neightborNode->hCost;
//
//            //이웃 노드가 열린 리스트에 있는지 확인.
//            Node* openListNode = nullptr;
//            for (Node* node : openList)
//            {
//                if (*node == *neightborNode)
//                {
//                    openListNode = node;
//                    break;
//                }
//            }
//
//            //노드가 목록에 없거나 Or 비용이 싸면, 새 노드를 추가합니다.
//            if (openListNode == nullptr ||
//                openListNode->gCost > neightborNode->gCost ||
//                openListNode->fCost > neightborNode->fCost)
//            {
//                //Todo: 현재 중점 고민 과제. 현재 그리는 레벨의 액터집합의 복사본임. 
//                // 그리드를 안쓰고 벡터를 사용해보는방법도 고려해보기.
//                Vector2 test = Vector2(newX, newY);
//                //액터배열?
//                grid[newY][newX]->SetOriginalActorImage("+"); //SetOriginalActorImage?
//                grid[newY][newX]->SetOriginalActorColor(Color::Green); //SetOriginalActorColor?
//                //음.. 위치가 같으면 같은 액터로 판정 해버리기?
//                openList.emplace_back(neightborNode);
//            }
//            else
//            {
//                //grid[newX][newY]->SetOriginalActorImage("#");
//                //grid[newX][newY]->SetOriginalActorColor(Color::Green);
//                SafeDelete(neightborNode);
//            }
//
//            int delay = (int)(0.1f * 1000);
//            Sleep(delay);
//        }
//    }
//    //return std::vector<Node*>();
//}

void AStar::StartFindPath(Node* startNode, Node* goalNode)
    /*std::vector<std::vector<Actor*>>& grid)*/
{
    //불 함수 true로 전환.
    IsFindingPath = true;
    this->startNode = startNode;
    this->goalNode = goalNode;

    openList.emplace_back(this->startNode);
    
}

std::vector<Node*> AStar::StepOfTheFindPath(std::vector<std::vector<Actor*>>& grid)
{
    std::vector<Direction> directions =
    {
        //하 상 우 좌 순서로 이동.
        {Vector2(0,1),1.0f}, {Vector2(0,-1),1.0f}, {Vector2(1,0),1.0f}, {Vector2(-1,0),1.0f},

        {Vector2(1,1), 1.414f}, {Vector2(1,-1), 1.414f},
        {Vector2(-1,1), 1.414f}, {Vector2(-1,-1), 1.414f},

    };

    //if (openList.empty() == true)
    //{
    //    return std::vector<Node*>();
    //}

    if (openList.empty() == false)
    {
        Node* lowestNode = openList[0];

        for (Node* node : openList)
        {
            if (node->fCost < lowestNode->fCost)
            {
                lowestNode = node;
            }
        }

        Node* currentNode = lowestNode;

        //목표노드를 찾음!
        if (IsDestination(currentNode) == true)
        {
            IsFinshedFindPath();
            return ConstructPath(currentNode);
        }

        for (int ix = 0; ix < (int)openList.size(); ++ix)
        {
            if (*openList[ix] == *currentNode)
            {
                openList.erase(openList.begin() + ix);
                break;
            }
        }

        bool isNodeInList = false;

        for (Node* node : closedList)
        {
            if (*node == *currentNode)
            {
                isNodeInList = true;
                break;
            }
        }

        if (isNodeInList == true)
        {
            //Todo: 이 continue처럼 동작하게 하기?->성공.

            //일단 continue는 루프를 즉시 종료하고 다시 실행시키는것.. 그렇다면 재귀함수인가?
            //재귀함수 써봄 일단?
            StepOfTheFindPath(grid);
            //return std::vector<Node*>();
        }

        closedList.emplace_back(currentNode);

        for (const Direction& direction : directions)
        {
            int newX = currentNode->NodePosition.x + direction.position.x;
            int newY = currentNode->NodePosition.y + direction.position.y;

            Vector2 newVector = Vector2(newX, newY);

            if (IsInRange(newX, newY, grid) == false)
            {
                continue;
            }

            if (grid[newY][newX]->GetOriginalActor()->GetNameTag() == 'W')
            {
                continue;
            }

            float gCost = currentNode->gCost + direction.cost;

            if (HasVisited(newX, newY, gCost) == true)
            {
                continue;
            }

            Node* neightborNode = new Node(newVector, currentNode);

            neightborNode->gCost = currentNode->gCost + direction.cost;

            neightborNode->hCost = CalculateHeuistic(neightborNode, goalNode);

            neightborNode->fCost = neightborNode->gCost + neightborNode->hCost;

            Node* openListNode = nullptr;

            for (Node* node : openList)
            {
                if (*node == *neightborNode)
                {
                    openListNode = node;
                    break;
                }
            }

            //노드가 목록에 없거나 비용이 싸면 새 노드를 추가.
            if (openListNode == nullptr ||
                openListNode->gCost > neightborNode->gCost ||
                openListNode->fCost > neightborNode->fCost)
            {
                Vector2 test = Vector2(newX, newY);
                //액터배열? 


                //여기서 boolean 변수를 바꿔버리는걸로 하자 그냥.
                grid[newY][newX]->SetOriginalActorImage("+"); //SetOriginalActorImage?
                grid[newY][newX]->SetOriginalActorColor(Color::Green); //SetOriginalActorColor?

                grid[newY][newX]->GetOriginalActor()->SetTrigger(true);


                //음.. 위치가 같으면 같은 액터로 판정 해버리기?
                openList.emplace_back(neightborNode);
            }
            else
            {
                //grid[newY][newX]->SetOriginalActorImage("#");
                //grid[newY][newX]->SetOriginalActorColor(Color::Green);
                SafeDelete(neightborNode);
            }
        }

    }
   
    return std::vector<Node*>();
}

bool AStar::HasFindingPath()
{
    return IsFindingPath;
}

bool AStar::HasFoundPath()
{
    return IsFoundPath;
}

void AStar::IsFinshedFindPath()
{
    IsFindingPath = false;
    IsFoundPath = true;
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
    if (x < 0 || y < 0 || x >= (int)grid[0].size() || y >= (int)grid.size())
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
