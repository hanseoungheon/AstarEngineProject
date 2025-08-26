#pragma once
#include "Core.h"
#include <Windows.h>

class Engine_API Vector2
{
public:
	Vector2(int x = 0, int y = 0);
	~Vector2();

	//������ �����ε�.
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	bool operator==(const Vector2& other) const;

	//����ȯ ������ �����ε�.
	operator COORD();
	operator COORD() const;

	//���ڿ��� ��ġ ���.
	const char* ToString();

public:
	static Vector2 Zero;
	static Vector2 One;
	static Vector2 Up;
	static Vector2 Right;
public:
	//�⺻ x y ��ǥ.
	int x = 0;
	int y = 0;

private:
	char* value = nullptr;
};