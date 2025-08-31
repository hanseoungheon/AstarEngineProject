#include "Wall.h"

Wall::Wall(const Vector2& position)
	:Actor("#",Color::White,position,'W')
{
	SetSortingOrder(1);
}
