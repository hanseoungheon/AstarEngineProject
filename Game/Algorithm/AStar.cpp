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
    //�ϴ� ����.
    //���� �ʿ��ҷ���?
    //Todo: �ϴ� �� �ڵ带 ���ӿ����� �������� ����� �׸��带 ��������? �ƴϸ� A��Ÿ�� Level��\n�������� ����������? �����ڴ� ����?
    //�������� ����������? �����ڴ� ����?

    //�ϴ� ��� ǥ�ô� �ϴ°� ������.
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
//    //Todo: �̰Ÿ� ��ƽ�� ���� �ɰ��ߵ�.->����.
//    this->startNode = startNode;
//    this->goalNode = goalNode;
//
//    //���� ��带 ���� ��Ͽ� ����.
//    openList.emplace_back(startNode);
//
//    //���⺤�͸� ������ ��� ���.->�Ϸ�
//    std::vector<Direction> directions =
//    {
//        //�� �� �� �� ������ �̵�.
//        {Vector2(0,1),1.0f}, {Vector2(0,-1),1.0f}, {Vector2(1,0),1.0f}, {Vector2(-1,0),1.0f},
//
//        {Vector2(1,1), 1.414f}, {Vector2(1,-1), 1.414f},
//        {Vector2(-1,1), 1.414f}, {Vector2(-1,-1), 1.414f},
//
//    };
//    
//
//    while (!openList.empty()) //���� ��尡 ������� ������ ��� �湮
//    {
//        //���� ����� ���� ��� ����.
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
//        //���� ��尡 ��ǥ ������� Ȯ��.
//        if (IsDestination(currentNode) == true)
//        {
//            //��ǥ ����� ���ݱ����� ��θ� ����ؼ� ��ȯ.
//            return ConstructPath(currentNode);
//        }
//
//        //���� ��Ͽ� �߰�.
//        for (int ix = 0; ix < (int)openList.size(); ++ix)
//        {
//            if (*openList[ix] == *currentNode)
//            {
//                //���ͷ����͸� ����ؼ� �迭���� ��� �������� ����.
//                openList.erase(openList.begin() + ix);
//                break;
//            }
//        }
//
//        //���� ��带 ���� ��忡 �߰�.
//        //���� �̹� �ִ������� Ȯ��.
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
//        //�湮������ �Ʒ��ܰ� �ǳʶٱ�.
//        if (isNodeInList == true)
//        {
//            continue;
//        }
//
//        closedList.emplace_back(currentNode);
//
//        //�̿���� �湮�ϱ�
//        //Todo: ������ �̴�� Vector2�� �ᵵ �Ǵ��� ���⺤�͸� ���� �ǽð����� ���ؾ��ϴ��� �ɻ����.->��⿹��?
//        for (const Direction& direction : directions)
//        {
//            int newX = currentNode->GetNodePosition().x + direction.position.x;
//            int newY = currentNode->GetNodePosition().y + direction.position.y;
//            Vector2 newVector = Vector2(newX, newY);
//
//            //�׸��� ������ Ȯ��.
//            if (IsInRange(newX,newY,grid) == false)
//            {
//                //�׸��� ���̸� ����.
//                continue;
//            }
//
//            //�ɼ� ��ֹ����� Ȯ��.
//            //���� #�̸� ��ֹ��̶�� ���.
//
//            if (grid[newY][newX]->GetOriginalActor()->GetImage() == "#")
//            {
//                continue;
//            }
//
//            //�̹� �湮�߾ ����.
//            //�̹� �湮�ߴ����� Ȯ���ϴ� �Լ� ȣ��.
//            float gCost = currentNode->gCost + direction.cost;
//            if (HasVisited(newX,newY,gCost) == true)
//            {
//                continue;
//            }
//
//            //�湮�� ���� ��� ����.
//            Node* neightborNode = new Node(newVector, currentNode);
//            //��뵵 ���.
//            //Getter�� const�� ������ �Ұ����� �׷��� �׳� Setter�� ����.
//            //neightborNode->GetgCost() = currentNode->GetgCost() + direction.cost;
//            neightborNode->gCost = currentNode->gCost + direction.cost;
//
//            //neightborNode->GethCost() = CalculateHeuistic();
//            neightborNode->hCost = CalculateHeuistic(neightborNode,goalNode);
//
//            neightborNode->fCost = neightborNode->gCost + neightborNode->hCost;
//
//            //�̿� ��尡 ���� ����Ʈ�� �ִ��� Ȯ��.
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
//            //��尡 ��Ͽ� ���ų� Or ����� �θ�, �� ��带 �߰��մϴ�.
//            if (openListNode == nullptr ||
//                openListNode->gCost > neightborNode->gCost ||
//                openListNode->fCost > neightborNode->fCost)
//            {
//                //Todo: ���� ���� ��� ����. ���� �׸��� ������ ���������� ���纻��. 
//                // �׸��带 �Ⱦ��� ���͸� ����غ��¹���� ����غ���.
//                Vector2 test = Vector2(newX, newY);
//                //���͹迭? 
//                 
//                
//                //���⼭ boolean ������ �ٲ�����°ɷ� ���� �׳�.
//                grid[newY][newX]->SetOriginalActorImage("+"); //SetOriginalActorImage?
//                grid[newY][newX]->SetOriginalActorColor(Color::Green); //SetOriginalActorColor?
//
//                grid[newY][newX]->GetOriginalActor()->SetTrigger(true);
//                 
//                
//                //��.. ��ġ�� ������ ���� ���ͷ� ���� �ع�����?
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
//    //���� ��带 ���� ��Ͽ� ����.
//    openList.emplace_back(this->startNode);
//
//    //Todo:���⺤�͸� ������ ��� ���.->�ִ� ��� ���� �Ƹ���?
//    std::vector<Direction> directions =
//    {
//        //�� �� �� �� ������ �̵�.
//        {Vector2(0,1),1.0f}, {Vector2(0,-1),1.0f}, {Vector2(1,0),1.0f}, {Vector2(-1,0),1.0f},
//
//        {Vector2(1,1), 1.414f}, {Vector2(1,-1), 1.414f},
//        {Vector2(-1,1), 1.414f}, {Vector2(-1,-1), 1.414f},
//
//    };
//
//
//    while (!openList.empty()) //���� ��尡 ������� ������ ��� �湮
//    {
//        //���� ����� ���� ��� ����.
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
//        //���� ��尡 ��ǥ ������� Ȯ��.
//        if (IsDestination(currentNode) == true)
//        {
//            ////��ǥ ����� ���ݱ����� ��θ� ����ؼ� ��ȯ.
//            //return ConstructPath(currentNode);
//            std::cout << "ã�ҽ��ϴ�.\n";
//        }
//
//        //���� ��Ͽ� �߰�.
//        for (int ix = 0; ix < (int)openList.size(); ++ix)
//        {
//            if (*openList[ix] == *currentNode)
//            {
//                //���ͷ����͸� ����ؼ� �迭���� ��� �������� ����.
//                openList.erase(openList.begin() + ix);
//                break;
//            }
//        }
//
//        //���� ��带 ���� ��忡 �߰�.
//        //���� �̹� �ִ������� Ȯ��.
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
//        //�湮������ �Ʒ��ܰ� �ǳʶٱ�.
//        if (isNodeInList == true)
//        {
//            continue;
//        }
//
//        closedList.emplace_back(currentNode);
//
//        //�̿���� �湮�ϱ�
//        //Todo: ������ �̴�� Vector2�� �ᵵ �Ǵ��� ���⺤�͸� ���� �ǽð����� ���ؾ��ϴ��� �ɻ����.->��⿹��?
//        for (const Direction& direction : directions)
//        {
//            int newX = currentNode->GetNodePosition().x + direction.position.x;
//            int newY = currentNode->GetNodePosition().y + direction.position.y;
//            Vector2 newVector = Vector2(newX, newY);
//
//            //�׸��� ������ Ȯ��.
//            if (IsInRange(newX, newY, grid) == false)
//            {
//                //�׸��� ���̸� ����.
//                continue;
//            }
//
//            //�ɼ� ��ֹ����� Ȯ��.
//            //���� #�̸� ��ֹ��̶�� ���.
//
//            if (grid[newY][newX]->GetImage() == "#")
//            {
//                continue;
//            }
//
//            //�̹� �湮�߾ ����.
//            //�̹� �湮�ߴ����� Ȯ���ϴ� �Լ� ȣ��.
//            float gCost = currentNode->gCost + direction.cost;
//            if (HasVisited(newX, newY, gCost) == true)
//            {
//                continue;
//            }
//
//            //�湮�� ���� ��� ����.
//            Node* neightborNode = new Node(newVector, currentNode);
//            //��뵵 ���.
//            //Getter�� const�� ������ �Ұ����� �׷��� �׳� Setter�� ����.
//            //neightborNode->GetgCost() = currentNode->GetgCost() + direction.cost;
//            neightborNode->gCost = currentNode->gCost + direction.cost;
//
//            //neightborNode->GethCost() = CalculateHeuistic();
//            neightborNode->hCost = CalculateHeuistic(neightborNode, goalNode);
//
//            neightborNode->fCost = neightborNode->gCost + neightborNode->hCost;
//
//            //�̿� ��尡 ���� ����Ʈ�� �ִ��� Ȯ��.
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
//            //��尡 ��Ͽ� ���ų� Or ����� �θ�, �� ��带 �߰��մϴ�.
//            if (openListNode == nullptr ||
//                openListNode->gCost > neightborNode->gCost ||
//                openListNode->fCost > neightborNode->fCost)
//            {
//                //Todo: ���� ���� ��� ����. ���� �׸��� ������ ���������� ���纻��. 
//                // �׸��带 �Ⱦ��� ���͸� ����غ��¹���� ����غ���.
//                Vector2 test = Vector2(newX, newY);
//                //���͹迭?
//                grid[newY][newX]->SetOriginalActorImage("+"); //SetOriginalActorImage?
//                grid[newY][newX]->SetOriginalActorColor(Color::Green); //SetOriginalActorColor?
//                //��.. ��ġ�� ������ ���� ���ͷ� ���� �ع�����?
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
    //�� �Լ� true�� ��ȯ.
    IsFindingPath = true;
    this->startNode = startNode;
    this->goalNode = goalNode;

    openList.emplace_back(this->startNode);
    
}

std::vector<Node*> AStar::StepOfTheFindPath(std::vector<std::vector<Actor*>>& grid)
{
    std::vector<Direction> directions =
    {
        //�� �� �� �� ������ �̵�.
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

        //��ǥ��带 ã��!
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
            //Todo: �� continueó�� �����ϰ� �ϱ�?->����.

            //�ϴ� continue�� ������ ��� �����ϰ� �ٽ� �����Ű�°�.. �׷��ٸ� ����Լ��ΰ�?
            //����Լ� �ẽ �ϴ�?
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

            //��尡 ��Ͽ� ���ų� ����� �θ� �� ��带 �߰�.
            if (openListNode == nullptr ||
                openListNode->gCost > neightborNode->gCost ||
                openListNode->fCost > neightborNode->fCost)
            {
                Vector2 test = Vector2(newX, newY);
                //���͹迭? 


                //���⼭ boolean ������ �ٲ�����°ɷ� ���� �׳�.
                grid[newY][newX]->SetOriginalActorImage("+"); //SetOriginalActorImage?
                grid[newY][newX]->SetOriginalActorColor(Color::Green); //SetOriginalActorColor?

                grid[newY][newX]->GetOriginalActor()->SetTrigger(true);


                //��.. ��ġ�� ������ ���� ���ͷ� ���� �ع�����?
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
    if (x < 0 || y < 0 || x >= (int)grid[0].size() || y >= (int)grid.size())
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
