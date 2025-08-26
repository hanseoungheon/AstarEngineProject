#include "Target.h"

Target::Target(const Vector2& position)
	:Actor("G",Color::Blue, position)
{
	SetSortingOrder(1);
}
