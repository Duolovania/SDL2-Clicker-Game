#include <iostream>
#include "Headers/transform.h"

Transform::Transform(Vector2 newPos, Vector2 newScale)
{
	position = newPos;
	scale = newScale;
}

double Transform::DistanceTo(Vector2 target)
{
	return sqrt(pow((position.x + scale.x / 2) - target.x, 2) + pow((position.y + scale.y / 2) - target.y, 2));
}
