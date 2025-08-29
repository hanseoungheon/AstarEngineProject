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
        //여기서 계속 돌리게 만들어야함?->완료.
        path = Astar.StepOfTheFindPath(MapGrid);
    }

    //찾는데 성공하면 기존 +를 전부 지우고 경로를 출력.
    if (Astar.HasFoundPath() == true && Astar.HasFinishedPrint() == false)
    {
        //둘로 쪼개서 연속성 부여 고려.
        //안쪼개고 하나에 변수를 대입해서 해보는건?
        Astar.DisplayGridWithPath(MapGrid, path);
    }
    else if (Astar.HasFoundPath() == true && Astar.HasFinishedPrint() == true)
    {
        //길을 다 찾으면 플레이어와 타겟 다시 원래대도 원상복귀시키기.
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

        //만약 길을 다 찾았으면 초기화?
        if (Astar.CheckEndFindPath() == true)
        {
            Astar.ClearAstarSetting();
        }
    }



    //입력 매핑
    
    //A*를 이용한 경로 찾기 실행.
    if (Input::GetController().GetKeyDown(VK_SPACE))
    {
        Astar.ClearGridAndPath(MapGrid,path);
        //Astar.StartFindPath(startNode, goalNode);
        Astar.StartFindPath_Using_Vector(startPos, goalPos);
       //Astar.FindPath_NonReturn(startNode,goalNode,MapGrid);
    }

    //플레이어<->타겟 컨트롤러 전환.
    if (Input::GetController().GetKeyDown(VK_RETURN))
    {
        //for (Actor* actor : actors)
        //{
        //    Player* player = actor->As<Player>();
        //    //혹시 모르니 안전장치 해놓는게 편할듯?

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

            //트리거가 작동하지않은 상태 즉 false면 플레이어가이동하고,
            //작동한 상태 즉 true면 타겟이 이동.
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
    //게임클리어는 일단 보류

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
    //일단 보류.
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
            //std::cout << "디버그테스트디버그테스트디버그테스트디버그테스트디버그테스트디버그테스트디버그테스트";
            if (actor->GetOriginalActor()->GetNameTag() == 'P')
            {
                *outStartNode = new Node(actor->GetActorPosition());
                //actor->GetOriginalActor()->SetColor(Color::Green); //디버그용
                continue;
            }

            if (actor->GetOriginalActor()->GetNameTag() == 'G')
            {
                *outGoalNode = new Node(actor->GetActorPosition());
                //actor->GetOriginalActor()->SetColor(Color::Green); 디버그용
                continue;
            }

            //actor->GetOriginalActor()->SetColor(Color::Blue); 디버그용

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

