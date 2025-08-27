#include "SokobanLevel.h"
#include "Math/Vector2.h"
#include "Input.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Target.h"
#include "Actor/Ground.h"

#include <iostream>

SokobanLevel::SokobanLevel()
{
    ReadMapFile("Stage_Astar.txt");
    //Vector2 position = Vector2(0, 0);
    //AddActor(new Wall(position));


}

void SokobanLevel::BeginPlay()
{
    Super::BeginPlay();
    FindOriginalActor();
    FindStartAndGoal(&startNode, &goalNode);
}

void SokobanLevel::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Input::GetController().GetKeyDown(VK_SPACE))
    {
        std::vector<Node*> path = Astar.FindPath(startNode, goalNode, MapGrid);
       //Astar.FindPath_NonReturn(startNode,goalNode,MapGrid);
    }
}

void SokobanLevel::Render()
{
    Super::Render();
    //����Ŭ����� �ϴ� ����

    //for (Actor* actor : actors)
    //{
    //    if (actor->GetTrigger() == true)
    //    {
    //        actor->SetImage("+");
    //        actor->SetColor(Color::Green);
    //    }
    //}
}

void SokobanLevel::ReadMapFile(const char* fileName)
{
    char filePath[256] = { };
    sprintf_s(filePath, 256, "../Assets/%s", fileName);

    FILE* file = nullptr;
    fopen_s(&file, filePath, "rt");

    if (file == nullptr)
    {
        std::cout << "�� ���� �б� ����! : " << fileName << "\n";
        __debugbreak();
        return;
    }

    //�Ľ�.
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = new char[fileSize + 1];
    size_t readSize = fread(buffer, sizeof(char), fileSize, file);

    //�迭 ��ȸ�� ���� �ε��� ����.
    int index = 0;

    int size = (int)readSize;

    Vector2 position;

    while (index < size)
    {
        char mapCharcter = buffer[index++];

        if (mapCharcter == '\n')
        {
            MapGrid.emplace_back(GetActorBuffer());
            //MapBuffer.clear();
            ClearActorBuffer();
            ++position.y;
            position.x = 0;

            continue;
        }

        switch (mapCharcter)
        {
        case '#':
        case '1':
            AddActor(new Wall(position));
            break;

        case '0':
        case'.':
            AddActor(new Ground(position));
            break;

        case'P':
        case'p':
            AddActor(new Ground(position));
            AddActor(new Player(position));
            break;

        case 'b':

        case't':
        case'G':
            AddActor(new Target(position));
            break;
        }
        ++position.x;
    }

    delete[] buffer;

    fclose(file);
}



bool SokobanLevel::CheckGameClear()
{
    //�ϴ� ����.
    int currentScore = 0;
    return false;
}

void SokobanLevel::FindStartAndGoal(Node** outStartNode, Node** outGoalNode)
{
    //bool hasInitialized = false;

    for (int iterator = 0; iterator < MapGrid.size(); ++iterator)
    {
        for (Actor* actor : MapGrid[iterator])
        {
            //if (*outStartNode != nullptr && *outGoalNode != nullptr)
            //{
            //    hasInitialized = true;
            //    break;
            //}
            
            //Player* player = actor->As<Player>();
            //Target* target = actor->As<Target>();
            //if (player != nullptr)

            //{
            //    *outStartNode = new Node(player->GetActorPosition());
            //    continue;
            //}

            //if (target != nullptr)
            //{
            //    *outGoalNode = new Node(target->GetActorPosition());
            //    continue;
            //}
            //std::cout << "������׽�Ʈ������׽�Ʈ������׽�Ʈ������׽�Ʈ������׽�Ʈ������׽�Ʈ������׽�Ʈ";
            if (actor->GetOriginalActor()->GetNameTag() == 'P')
            {
                *outStartNode = new Node(actor->GetActorPosition());
                //actor->GetOriginalActor()->SetColor(Color::Green); ����׿�
                continue;
            }

            if (actor->GetOriginalActor()->GetNameTag() == 'G')
            {
                *outGoalNode = new Node(actor->GetActorPosition());
                //actor->GetOriginalActor()->SetColor(Color::Green); ����׿�
                continue;
            }

            //actor->GetOriginalActor()->SetColor(Color::Blue); ����׿�

        }
    }

}

void SokobanLevel::FindOriginalActor()
{
    for (int i = 0; i < MapGrid.size(); i++)
    {
        for (Actor* gridActor : MapGrid[i])
        {
            for (Actor* actor : actors)
            {
                if (actor->GetActorPosition() == gridActor->GetActorPosition())
                    gridActor->SetOriginalActor(actor);
            }
        }
    }
}

bool SokobanLevel::CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition)
{
    for (Actor* const actor : actors)
    {
        if (actor->GetActorPosition() == newPosition)
        {
            if (actor->As<Wall>())
            {
                return false;
            }

            return true;
        }
    }
    return false;
}
