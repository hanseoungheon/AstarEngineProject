#pragma once

enum class Color :int
{
	Blue = 1,
	Green = 2,
	Red = 4,
	Purple = 5,
	Yellow = 6,
	Gray = 7,

	LightRed = 12,
	LightBlue = 9,
	LightGreen = 10,
	LightYellow = 14,
	SkyBlue = 11,

	White = Blue | Green | Red,
	Idensity = 8,
};