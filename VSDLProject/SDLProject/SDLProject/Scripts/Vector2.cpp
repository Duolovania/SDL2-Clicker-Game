#include "Headers/vector2.h"

Vector2::Vector2(int newX, int newY)
{
	x = newX;
	y = newY;
}

Vector2 Vector2::Uniform(float uniformValue)
{
	return Vector2(uniformValue, uniformValue);
}

Vector2 Vector2::Add(Vector2 a, Vector2 b)
{
	return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 Vector2::Subtract(Vector2 a, Vector2 b)
{
	return Vector2(a.x - b.x, a.y - b.y);
}

Vector2 Vector2::Multiply(Vector2 a, Vector2 b)
{
	return Vector2(a.x * b.x, a.y * b.y);
}

Vector2 Vector2::Divide(Vector2 a, Vector2 b)
{
	return Vector2(a.x / b.x, a.y / b.y);
}