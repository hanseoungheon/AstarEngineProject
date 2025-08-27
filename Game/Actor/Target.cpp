#include "Target.h"

Target::Target(const Vector2& position)
	:Actor("G",Color::Blue, position,'G')
{
	SetSortingOrder(1);
}
