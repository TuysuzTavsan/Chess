#pragma once
#include <Types/vector.h>


bool IsInside(const Vec2& boxPos, const Vec2& boxSize, const Vec2& position)
{
	if (position.x >= boxPos.x && position.x <= (boxPos.x + boxSize.x)
		&& position.y >= boxPos.y && position.y <= (boxPos.y + boxSize.y))
	{
		return true;
	}
		
	return false;
}