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

    if (Astar.HasFindingPath() == true && JumpTick % 2 == 0)
    {
        //Todo: 여기서 계속 돌리게 만들어야함?
        std::vector<Node*> path = Astar.StepOfTheFindPath(MapGrid);
    }

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
            Color_UI* colorUI = actor->As<Color_UI>();
            //혹시 모르니 안전장치 해놓는게 편할듯?
            bool tempBool = false;

            if (player != nullptr)
            {
                player->SetTrigger(!player->GetTrigger());
                tempBool = !tempBool;
            }

            //트리거가 작동하지않은 상태 즉 false면 플레이어가이동하고, 작동한 상태 즉 true면 타겟이 이동.
            if (colorUI != nullptr)
            {
                colorUI->SetActiveColor(player->GetTrigger());
            }

        }
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
                //actor->GetOriginalActor()->SetColor(Color::Green); 디버그용
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
    AddActor(new Custom_UI("Enter: ChangeMoving", Color::Blue, Vector2(0, 10)));
    AddActor(new Custom_UI("(", Color::White, Vector2(19, 10)));
    AddActor(new Color_UI("Player", Color::Idensity, Vector2(20, 10), 'P'));
    AddActor(new Custom_UI("/", Color::White, Vector2(26, 10)));
    AddActor(new Color_UI("Target", Color::Idensity, Vector2(27, 10), 'T'));
    AddActor(new Custom_UI(")", Color::White, Vector2(33, 10)));
}

void SokobanLevel::HowToMovementAndOtherManualUI()
{
    //AddActor(new Custom_UI("ArrowKeys: Object Movement", Color::White, Vector2(0, 11)));
    AddActor(new Custom_UI("ArrowKeys: Object Movement", Color::Green, Vector2(0, 11)));
    AddActor(new Custom_UI("SpaceBar: FindTarget to using Astar", Color::Purple, Vector2(0, 12)));
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
