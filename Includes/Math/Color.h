#pragma once

enum class Color :int
{
	Blue = 1,
	Green = 2,
	Red = 4,
	White = Blue | Green | Red,
	Idensity = 8,
};