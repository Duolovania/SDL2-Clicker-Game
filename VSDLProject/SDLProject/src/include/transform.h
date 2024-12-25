#pragma once
#include "vector2.h"

class Transform
{
	public:
		Vector2 position, scale;

		Transform(Vector2 newPos, Vector2 newScale);
		double DistanceTo(Vector2 target);
};