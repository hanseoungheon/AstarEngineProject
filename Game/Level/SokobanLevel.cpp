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
{


    CreatePlayerAndTargetStatUI();
    HowToMovementAndOtherManualUI();

    ReadMapFile("Stage_Astar.txt");
    //Vector2 position = Vector2(0, 0);
    //AddActor(new Wall(position));

    //FindStartAndGoal(&startNode, &goalNode);
}

SokobanLevel::~SokobanLevel()
{
    //for (int i = 0; i < MapGrid.size() - 1; ++i)
    //{
    //    //MapGrid[0]
    //    for (Actor* actor : MapGrid[i])
    //    {
    //        SafeDelete(actor);
    //    }
    //}
    //MapGrid.clear();

    //for (Actor* actor : MapGrid[0])
    //    SafeDelete(actor);
    
    //SafeDelete(MapGrid[0][0]);

    for (int i = 0; i < MapGrid.size(); ++i)
    {
        MapGrid[i].clear();
    }
    MapGrid.clear();

    if (startNode != nullptr)
    {
        delete startNode;
    }

    if (goalNode != nullptr)
    {
        delete goalNode;
    }

}

void SokobanLevel::BeginPlay()
{
    Super::BeginPlay();
    FindOriginalActor();
    //FindStartAndGoal(&startNode, &goalNode);
    FindStartAndGoal_Using_Vector(startPos, goalPos);


}

void SokobanLevel::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    ++JumpTick;

    if (Astar.HasFindingPath() == true)
    {
        //���⼭ ��� ������ ��������?->�Ϸ�.
        path = Astar.StepOfTheFindPath(MapGrid);
    }

    //ã�µ� �����ϸ� ���� +�� ���� ����� ��θ� ���.
    if (Astar.HasFoundPath() == true && Astar.HasFinishedPrint() == false)
    {
        //�ѷ� �ɰ��� ���Ӽ� �ο� ���.
        //���ɰ��� �ϳ��� ������ �����ؼ� �غ��°�?
        Astar.DisplayGridWithPath(MapGrid, path);
    }
    else if (Astar.HasFoundPath() == true && Astar.HasFinishedPrint() == true)
    {
        //���� �� ã���� �÷��̾�� Ÿ�� �ٽ� �����뵵 ���󺹱ͽ�Ű��.
        for (Actor* actor : actors)
        {
            Player* player = actor->As<Player>();
            Target* target = actor->As<Target>();

            if (player != nullptr)
            {
                player->SetImage("P");
                player->SetColor(Color::Red);
            }

            if (target != nullptr)
            {

                target->SetImage("T");
                target->SetColor(Color::Blue);
            }
        }

        //���� ���� �� ã������ �ʱ�ȭ?
        if (Astar.CheckEndFindPath() == true)
        {
            Astar.ClearAstarSetting();
        }
    }



    //�Է� ����
    
    //A*�� �̿��� ��� ã�� ����.
    if (Input::GetController().GetKeyDown(VK_SPACE))
    {
        Astar.ClearGridAndPath(MapGrid,path);
        //Astar.StartFindPath(startNode, goalNode);
        Astar.StartFindPath_Using_Vector(startPos, goalPos);
       //Astar.FindPath_NonReturn(startNode,goalNode,MapGrid);
    }

    //�÷��̾�<->Ÿ�� ��Ʈ�ѷ� ��ȯ.
    if (Input::GetController().GetKeyDown(VK_RETURN))
    {
        //for (Actor* actor : actors)
        //{
        //    Player* player = actor->As<Player>();
        //    //Ȥ�� �𸣴� ������ġ �س��°� ���ҵ�?

        //    if (player != nullptr)
        //    {
        //        player->SetTrigger(!player->GetTrigger());
        //        IsChageTheCharacter = !IsChageTheCharacter;
        //    }
        //}


        IsLevelTrigged = !IsLevelTrigged;

        for (UI* UI_InLevel : ui_inLevel)
        {
            Color_UI* colorUI = UI_InLevel->As<Color_UI>();

            //Ʈ���Ű� �۵��������� ���� �� false�� �÷��̾�̵��ϰ�,
            //�۵��� ���� �� true�� Ÿ���� �̵�.
            if (colorUI != nullptr)
            {
                colorUI->SetActiveColor(IsLevelTrigged);
            }
        }
    }

    if (Input::GetController().GetKeyDown(VK_TAB))
    {
        Astar.ClearGridAndPath(MapGrid, path);
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



        switch (mapCharcter)
        {
        case '#':
            AddActor(new Wall(position));
            break;

        case '0':
            AddActor(new Ground(position));
            break;

        case'P':
            AddActor(new Ground(position));
            AddActor(new Player(position));
            break;

        case'G':
            AddActor(new Ground(position));
            AddActor(new Target(position));
            break;
        }
        ++position.x;

        if (mapCharcter == '\n')
        {
            MapGrid.emplace_back(GetActorBuffer());
            //MapBuffer.clear();
            ClearActorBuffer();
            ++position.y;
            position.x = 0;

            continue;
        }
    }

    delete[] buffer;
    fclose(file);

    //delete[] fileName;
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
                //actor->GetOriginalActor()->SetColor(Color::Green); //����׿�
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

void SokobanLevel::FindStartAndGoal_Using_Vector(Vector2& outstartPos, Vector2& outgoalPos)
{
    bool foundStart = false;
    bool foundGoal = false;

    for (int iterator = 0; iterator < MapGrid.size(); ++iterator)
    {

        for (Actor* actor : MapGrid[iterator])
        {
            if (actor->GetOriginalActor()->GetNameTag() == 'P')
            {
                outstartPos = actor->GetActorPosition();
                foundStart = true;
            }

            if (actor->GetOriginalActor()->GetNameTag() == 'G')
            {
                outgoalPos = actor->GetActorPosition();
                foundGoal = true;
            }

            if (foundStart == true && foundGoal == true)
            {
                return;
            }

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
    AddUI(new Custom_UI("Clear: Clear Astar Route", Color::Yellow, Vector2(0, 13)));
    AddUI(new Custom_UI("ESC: ShutDown This Simulation\n", Color::Gray, Vector2(0, 14)));
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

