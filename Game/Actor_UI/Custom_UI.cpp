#include "Custom_UI.h"
#include <iostream>
Custom_UI::Custom_UI(const char* text,Color color,const Vector2& position)
	:Actor(text,color,position,'U')
{
	SetSortingOrder(5);
}


