#include "SokobanLevel.h"
#include "Math/Vector2.h"
#include <iostream>
SokobanLevel::SokobanLevel()
{
}

bool SokobanLevel::CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition)
{
    return false;
}

void SokobanLevel::Render()
{
}

void SokobanLevel::ReadMapFile(const char* fileName)
{
}

bool SokobanLevel::CheckGameClear()
{
    return false;
}
