#pragma once
#include "Math/Vector2.h"

//인터페이스
class ICanPlayerMove
{
public:
	virtual bool CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition) = 0;
};
