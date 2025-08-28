#include "SokobanLevel.h"
#include "Math/Vector2.h"
#include "Input.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Target.h"
#include "Actor/Ground.h"
#include "Actor_UI/Custom_UI.h"
#include "Actor_UI/Color_UI.h"
#include <iostream>

SokobanLevel::SokobanLevel()
    :IsChageTheCharacter(false)
{


    CreatePlayerAndTargetStatUI();
    HowToMovementAndOtherManualUI();

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
    
    ++JumpTick;
    std::vector<Node*> path;
    if (Astar.HasFindingPath() == true)
    {
        //���⼭ ��� ������ ��������?->�Ϸ�.
        path = Astar.StepOfTheFindPath(MapGrid);
    }

    if (Astar.HasFoundPath() == true)
    {
        Astar.DisplayGridWithPath(MapGrid, path);
    }


    //FindStartAndGoal(&startNode, &goalNode);
    if (Input::GetController().GetKeyDown(VK_SPACE))
    {
        Astar.StartFindPath(startNode, goalNode);
       //Astar.FindPath_NonReturn(startNode,goalNode,MapGrid);
    }

    if (Input::GetController().GetKeyDown(VK_RETURN))
    {

        for (Actor* actor : actors)
        {
            Player* player = actor->As<Player>();
            //Ȥ�� �𸣴� ������ġ �س��°� ���ҵ�?


            if (player != nullptr)
            {
                player->SetTrigger(!player->GetTrigger());
                IsChageTheCharacter = !IsChageTheCharacter;
            }
        }

        for (UI* UI_InLevel : ui_inLevel)
        {
            Color_UI* colorUI = UI_InLevel->As<Color_UI>();

            //Ʈ���Ű� �۵��������� ���� �� false�� �÷��̾�̵��ϰ�, �۵��� ���� �� true�� Ÿ���� �̵�.
            if (colorUI != nullptr)
            {
                colorUI->SetActiveColor(IsChageTheCharacter);
            }
        }
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

void SokobanLevel::CreatePlayerAndTargetStatUI()
{
    AddUI(new Custom_UI("Enter: ChangeMoving", Color::Blue, Vector2(0, 10)));
    AddUI(new Custom_UI("(", Color::White, Vector2(19, 10)));
    AddUI(new Color_UI("Player", Color::Idensity, Vector2(20, 10), 'P'));
    AddUI(new Custom_UI("/", Color::White, Vector2(26, 10)));
    AddUI(new Color_UI("Target", Color::Idensity, Vector2(27, 10), 'T'));
    AddUI(new Custom_UI(")", Color::White, Vector2(33, 10)));
}

void SokobanLevel::HowToMovementAndOtherManualUI()
{
    //AddActor(new Custom_UI("ArrowKeys: Object Movement", Color::White, Vector2(0, 11)));
    AddUI(new Custom_UI("ArrowKeys: Object Movement", Color::Green, Vector2(0, 11)));
    AddUI(new Custom_UI("SpaceBar: FindTarget to using Astar", Color::Purple, Vector2(0, 12)));
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
