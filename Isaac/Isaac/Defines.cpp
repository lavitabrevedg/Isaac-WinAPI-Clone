#include "pch.h"
#include "Defines.h"

float RadianToDegree(float radian)
{
	float degree = radian * (180.0f / std::numbers::pi_v<float>);

	degree = fmodf(degree, 360.0f);
	if (degree < 0.0f)
		degree += 360.0f;

	return degree;
}

float DegreeToRadian(float degree)
{
	float radian = degree * (std::numbers::pi_v<float> / 180.0f);

	radian = fmodf(radian, std::numbers::pi_v<float> *2);
	if (radian < 0.0f)
		radian += std::numbers::pi_v<float> *2;

	return radian;
}

bool IsInPoint(RECT rect, POINT pos)
{
	if (pos.x < rect.left)
		return false;

	if (pos.x > rect.right)
		return false;

	if (pos.y < rect.top)
		return false;

	if (pos.y > rect.bottom)
		return false;
	return true;
}

bool AABBIntersect(const RECT& a, const RECT& b)
{
	return (a.right > b.left) &&
		(a.left < b.right) &&
		(a.bottom > b.top) &&
		(a.top < b.bottom);
}
