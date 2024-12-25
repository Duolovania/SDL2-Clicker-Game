#pragma once

class Vector2
{
	public:
		int x, y;

		Vector2(int newX = 0, int newY = 0);
		
		/// <summary>Returns a Vector2 where x == y. <para> Example Vector2::Uniform(10) is the same as Vector2(10, 10). </para></summary>
		static Vector2 Uniform(float uniformValue);

		static Vector2 Add(Vector2 a, Vector2 b);
		static Vector2 Subtract(Vector2 a, Vector2 b);

		static Vector2 Multiply(Vector2 a, Vector2 b);
		static Vector2 Divide(Vector2 a, Vector2 b);
};