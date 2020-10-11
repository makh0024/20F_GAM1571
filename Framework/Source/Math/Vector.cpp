#include "Vector.h"

using namespace fw;

fw::vec2::vec2()
{
	x = 0;
	y = 0;
}

fw::vec2::vec2(float ax, float ay)
{
	x = ax; 
	y = ay;
}

fw::vec2::~vec2()
{
}

bool fw::vec2::operator==(vec2 o)
{
	if (x == o.x && y == o.y)
		return true;
	else
		return false;
}

bool fw::vec2::operator!=(vec2 o)
{
	if (x != o.x && y != o.y)
		return true;
	else
		return false;
}

bool fw::vec2::operator>(vec2 o)
{
	if (x > o.x && y > o.y)
		return true;
	else
		return false;
}

bool fw::vec2::operator<(vec2 o)
{
	if (x < o.x && y < o.y)
		return true;
	else
		return false;
}

bool fw::vec2::operator>=(vec2 o)
{
	if (x >= o.x && y >= o.y)
		return true;
	else
		return false;
}

bool fw::vec2::operator<=(vec2 o)
{
	if (x <= o.x && y <= o.y)
		return true;
	else
		return false;
}

float fw::vec2::Magnitude()
{
	return sqrtf((x*x) + (y*y)) ;
}

float fw::vec2::Distance(vec2 o)
{
	return sqrt((y*y - o.y*o.y) + (x*x - o.x*o.x));
}

void fw::vec2::Normalize()
{
	*this /= Magnitude();
}

vec2 fw::vec2::Normalized()
{
	vec2 v = *this;
	v / Magnitude();
	return v;
}

float fw::vec2::DotProduct(vec2 o)
{
	return (x * o.x + y * o.y);
}

void fw::vec2::SetValues(float o, float o2)
{
	x = o;
	y = o2;	
}
