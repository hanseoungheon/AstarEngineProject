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
    //게임클리어는 일단 보류
}

void SokobanLevel::ReadMapFile(const char* fileName)
{
    char filePath[256] = { };
    sprintf_s(filePath, 256, "../Assets/%s", fileName);

    FILE* file = nullptr;
    fopen_s(&file, filePath, "rt");

    if (file == nullptr)
    {
        std::cout << "맵 파일 읽기 실패! : " << fileName << "\n";
        __debugbreak();
        return;
    }

    //파싱.
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = new char[fileSize + 1];
    size_t readSize = fread(buffer, sizeof(char), fileSize, file);

    //배열 순회를 위한 인덱스 변수.
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
    //일단 보류.
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

