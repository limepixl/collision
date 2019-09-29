#include "circle.hpp"
#include "utils.hpp"

Circle::Circle(float r, const sf::Vector2f& c) : radius(r), center(c)
{
	color = sf::Vector3i(rand() % 200 + 56, rand() % 200 + 56, rand() % 200 + 56);
}

bool CheckOverlap(Circle& first, Circle& second)
{
	float dist = Length(first.center - second.center);
	if(dist < first.radius + second.radius)
		return true;

	return false;
}
