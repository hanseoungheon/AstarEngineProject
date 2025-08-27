#include "SokobanLevel.h"
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Target.h"
#include "Actor/Ground.h"

#include <iostream>

SokobanLevel::SokobanLevel()
{
    ReadMapFile("Stage_Astar.txt");
    Vector2 position = Vector2(0, 0);
    AddActor(new Wall(position));

}

void SokobanLevel::BeginPlay()
{
    Super::BeginPlay();
}

void SokobanLevel::Render()
{
    Super::Render();
    //����Ŭ����� �ϴ� ����
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
            MapGrid.push_back(GetActorBuffer());
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
    bool hasInitialized = false;

    for (Actor* actor : actors)
    {
        if (*outStartNode != nullptr && *outGoalNode != nullptr)
        {
            hasInitialized = true;
            break;
        }

        if (actor != nullptr && actor->GetImage() == "P")
        {
            *outStartNode = new Node(actor->GetActorPosition());
            continue;
        }

        if (actor != nullptr && actor->GetImage() == "G")
        {
            *outGoalNode = new Node(actor->GetActorPosition());
            continue;
        }
    }
}

